// ============================================================================
// FILE BỔ SUNG: XỬ LÝ ĐƠN GIÁ, HÌNH DÁNG KHU ĐẤT & THUẾ ĐẤT PHI NÔNG NGHIỆP
// Chỉ sử dụng các thư viện đã khai báo trong file chính.
// ============================================================================

// 1. CÁC HẰNG SỐ CĂN CỨ THEO PHÁP LUẬT VÀ YÊU CẦU BÀI TOÁN
const double DON_GIA_MAC_DINH = 1000000.0; // 1.000.000 VNĐ/m2

// Thuế suất lũy tiến từng phần đất ở (Điều 7 Luật Thuế SD đất phi nông nghiệp số 48/2010/QH12)
const double THUE_SUAT_TRONG_HAN_MUC = 0.0003;     // Bậc 1: Diện tích <= 100% hạn mức (0.03%)
const double THUE_SUAT_VUOT_3_LAN     = 0.0007;     // Bậc 2: Vượt <= 3 lần hạn mức (0.07%)
const double THUE_SUAT_VUOT_TREN_3_LAN = 0.0015;   // Bậc 3: Vượt trên 3 lần hạn mức (0.15%)

// Ngưỡng 100% hạn mức giao đất ở theo quy định (mặc định đô thị loại 1/đặc biệt là 160m2)
const double HAN_MUC_DAT_O_MAC_DINH = 160.0;

// Phân nhóm đối tượng nộp thuế (Điều 9 và Điều 10 Luật số 48/2010/QH12)
enum DoiTuongMienGiam {
    DOI_TUONG_THONG_THUONG = 0,    // Không thuộc diện ưu tiên -> Nộp 100%
    MIEN_THUE_HOAN_TOAN = 1,       // Thương binh 1/4, 2/4; Mẹ VNAH; Hộ nghèo -> Miễn 100%
    GIAM_THUE_50_PHAN_TRAM = 2     // Thương binh 3/4, 4/4; Bệnh binh; Hộ cận nghèo -> Giảm 50%
};

// ============================================================================
// 2. HÀM TRA CỨU ĐƠN GIÁ CƠ SỞ THEO KHU VỰC VÀ VỊ TRÍ MẶT TIỀN
// ============================================================================
/**
 * Đơn giá cơ sở được tính bằng Đơn giá mặc định (1.000.000 đ) nhân với
 * Hệ số khu vực (Trung tâm: 2.0, Ngoại ô: 1.5, Nông thôn: 1.0) và
 * Hệ số mặt tiền (Mặt tiền lớn: 1.2, Hẻm ô tô: 1.0, Hẻm nhỏ: 0.8) đã có sẵn trong HinhHoc.
 */
double traCuuDonGiaCoSo(const HinhHoc* h, double donGiaGoc = DON_GIA_MAC_DINH) {
    if (h == NULL) return donGiaGoc;
    return donGiaGoc * h->getHeSoKhuVuc() * h->getHeSoMatTien();
}

// ============================================================================
// 3. HÀM ĐIỀU CHỈNH GIÁ PHỤ THUỘC VÀO HÌNH DÁNG KHU ĐẤT
// ============================================================================
/**
 * Tính hệ số điều chỉnh theo khuôn đất:
 * - Khuôn hình vuông: Tăng 15% (hệ số 1.15) do hình đẹp.
 * - Đất hình chữ nhật:
 *   + Chiều rộng < 3m: Giảm 10% (hệ số 0.90) do hẹp bề ngang khó bố trí.
 *   + Chiều rộng >= 40% chiều dài: Tăng 10% (hệ số 1.10) do khuôn đất chuẩn dễ xây dựng.
 *   + Còn lại: Giữ nguyên (hệ số 1.00).
 * - Các hình khác (Tam giác, Hình tròn): Giữ nguyên (hệ số 1.00).
 */
double tinhHeSoHinhDang(string tenHinh, double dai = 0.0, double rong = 0.0) {
    if (tenHinh == "Hình vuông") {
        return 1.15; // Tăng 15%
    }
    if (tenHinh == "Hình chữ nhật") {
        if (rong < 3.0 && rong > 0.0) {
            return 0.90; // Giảm 10%
        }
        if (dai > 0.0 && rong >= 0.40 * dai) {
            return 1.10; // Tăng 10%
        }
    }
    return 1.00;
}

// Đơn giá áp dụng cuối cùng sau khi xét cả vị trí đường và hình dáng đất
double tinhDonGiaSauDieuChinh(const HinhHoc* h, double dai = 0.0, double rong = 0.0, double donGiaGoc = DON_GIA_MAC_DINH) {
    double donGiaCoSo = traCuuDonGiaCoSo(h, donGiaGoc);
    double heSoHinh = tinhHeSoHinhDang(h->getTenHinh(), dai, rong);
    return donGiaCoSo * heSoHinh;
}

// ============================================================================
// 4. HÀM MIỄN GIẢM THUẾ THEO ĐỐI TƯỢNG (QUY ĐỊNH PHÁP LUẬT)
// ============================================================================
/**
 * Căn cứ Điều 9 & Điều 10 Luật Thuế SD đất phi nông nghiệp số 48/2010/QH12
 * @return Tỷ lệ được miễn giảm (1.0 = miễn 100%, 0.5 = giảm 50%, 0.0 = không giảm)
 */
double tinhTyLeMienGiam(int loaiDoiTuong) {
    switch (loaiDoiTuong) {
        case MIEN_THUE_HOAN_TOAN:
            return 1.0;
        case GIAM_THUE_50_PHAN_TRAM:
            return 0.5;
        case DOI_TUONG_THONG_THUONG:
        default:
            return 0.0;
    }
}

string getTenDoiTuongMienGiam(int loaiDoiTuong) {
    if (loaiDoiTuong == MIEN_THUE_HOAN_TOAN) {
        return "Miễn thuế 100% (Thương binh 1/4-2/4, Mẹ VNAH, Hộ nghèo)";
    }
    if (loaiDoiTuong == GIAM_THUE_50_PHAN_TRAM) {
        return "Giảm thuế 50% (Thương binh 3/4-4/4, Hộ cận nghèo)";
    }
    return "Đối tượng thông thường (Không miễn giảm)";
}

// ============================================================================
// 5. HÀM TÍNH THUẾ ĐẤT THEO BIỂU THUẾ LŨY TIẾN TỪNG PHẦN
// ============================================================================
/**
 * Tính số thuế đất phát sinh trước khi xét miễn giảm.
 * Ngưỡng 100% căn cứ theo hạn mức giao đất ở (hanMuc):
 * - Bậc 1: Phần diện tích <= hanMuc tính thuế suất 0.03%
 * - Bậc 2: Phần diện tích vượt hanMuc đến 3 * hanMuc tính thuế suất 0.07%
 * - Bậc 3: Phần diện tích vượt trên 3 * hanMuc tính thuế suất 0.15%
 */
double tinhThueDatPhatSinh(double dienTich, double donGiaApDung, double hanMuc = HAN_MUC_DAT_O_MAC_DINH) {
    if (dienTich <= 0.0 || donGiaApDung <= 0.0 || hanMuc <= 0.0) return 0.0;

    double sTrongHanMuc = min(dienTich, hanMuc);
    double sVuotDuoi3Lan = 0.0;
    double sVuotTren3Lan = 0.0;

    if (dienTich > hanMuc) {
        sVuotDuoi3Lan = min(dienTich - hanMuc, 2.0 * hanMuc);
    }
    if (dienTich > 3.0 * hanMuc) {
        sVuotTren3Lan = dienTich - 3.0 * hanMuc;
    }

    double thueBac1 = sTrongHanMuc * donGiaApDung * THUE_SUAT_TRONG_HAN_MUC;
    double thueBac2 = sVuotDuoi3Lan * donGiaApDung * THUE_SUAT_VUOT_3_LAN;
    double thueBac3 = sVuotTren3Lan * donGiaApDung * THUE_SUAT_VUOT_TREN_3_LAN;

    return thueBac1 + thueBac2 + thueBac3;
}

/**
 * Số tiền thuế đất thực nộp sau khi trừ mức miễn giảm chính sách
 */
double tinhThueDatPhaiNop(const HinhHoc* h, int loaiDoiTuong, double dai = 0.0, double rong = 0.0, 
                         double hanMuc = HAN_MUC_DAT_O_MAC_DINH, double donGiaGoc = DON_GIA_MAC_DINH) {
    if (h == NULL) return 0.0;
    double donGiaApDung = tinhDonGiaSauDieuChinh(h, dai, rong, donGiaGoc);
    double thuePhatSinh = tinhThueDatPhatSinh(h->tinhDienTich(), donGiaApDung, hanMuc);
    double tyLeGiam = tinhTyLeMienGiam(loaiDoiTuong);
    return thuePhatSinh * (1.0 - tyLeGiam);
}

// ============================================================================
// 6. HÀM IN BẢNG THÔNG TIN KÊ KHAI & TÍNH THUẾ CHI TIẾT
// ============================================================================
void inThongTinThueChiTiet(const HinhHoc* h, int loaiDoiTuong, double dai = 0.0, double rong = 0.0, 
                          double hanMuc = HAN_MUC_DAT_O_MAC_DINH, double donGiaGoc = DON_GIA_MAC_DINH) {
    if (h == NULL) return;

    double s = h->tinhDienTich();
    double donGiaCoSo = traCuuDonGiaCoSo(h, donGiaGoc);
    double heSoHinh = tinhHeSoHinhDang(h->getTenHinh(), dai, rong);
    double donGiaSauDieuChinh = donGiaCoSo * heSoHinh;
    double thuePhatSinh = tinhThueDatPhatSinh(s, donGiaSauDieuChinh, hanMuc);
    double tyLeGiam = tinhTyLeMienGiam(loaiDoiTuong);
    double tienMienGiam = thuePhatSinh * tyLeGiam;
    double thuePhaiNop = thuePhatSinh - tienMienGiam;

    cout << CYAN << "\n================ BẢNG KÊ KHAI THUẾ ĐẤT CHI TIẾT ================" << RESET << "\n";
    cout << left << setw(28) << "Số tờ / Số thửa:" << YELLOW << h->getSoToSoThua() << RESET << "\n";
    cout << left << setw(28) << "Hình dáng khuôn đất:" << h->getTenHinh() << "\n";
    cout << left << setw(28) << "Khu vực địa lý:" << h->getKhuVuc() << " (Hệ số: " << h->getHeSoKhuVuc() << ")\n";
    cout << left << setw(28) << "Vị trí tiếp giáp:" << h->getViTriMatTien() << " (Hệ số: " << h->getHeSoMatTien() << ")\n";
    cout << fixed << setprecision(2);
    cout << left << setw(28) << "Diện tích thửa đất:" << s << " m2\n";
    cout << left << setw(28) << "Hạn mức đất ở (100%):" << hanMuc << " m2\n";
    cout << fixed << setprecision(0);
    cout << left << setw(28) << "Đơn giá cơ sở gốc:" << donGiaGoc << " VNĐ/m2\n";
    cout << left << setw(28) << "Đơn giá theo vị trí:" << donGiaCoSo << " VNĐ/m2\n";
    cout << fixed << setprecision(2);
    cout << left << setw(28) << "Hệ số hình dáng khuôn:" << heSoHinh;
    if (heSoHinh > 1.0) cout << GREEN << " (Tăng " << (heSoHinh - 1.0) * 100 << "% giá)" << RESET;
    else if (heSoHinh < 1.0) cout << RED << " (Giảm " << (1.0 - heSoHinh) * 100 << "% giá)" << RESET;
    else cout << " (Giữ nguyên)";
    cout << "\n";
    cout << fixed << setprecision(0);
    cout << left << setw(28) << "Đơn giá tính thuế áp dụng:" << donGiaSauDieuChinh << " VNĐ/m2\n";
    cout << left << setw(28) << "Thuế đất phát sinh:" << thuePhatSinh << " VNĐ\n";
    cout << left << setw(28) << "Chính sách miễn giảm:" << getTenDoiTuongMienGiam(loaiDoiTuong) << "\n";
    cout << left << setw(28) << "Số tiền được miễn giảm:" << tienMienGiam << " VNĐ\n";
    cout << CYAN << string(64, '-') << RESET << "\n";
    cout << left << setw(28) << "THUẾ THỰC TẾ PHẢI NỘP:" << GREEN << thuePhaiNop << " VNĐ" << RESET << "\n";
    cout << CYAN << string(64, '=') << RESET << "\n";
}