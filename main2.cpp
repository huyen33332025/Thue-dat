#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <cstdlib>

using namespace std;

const double PI = acos(-1.0);
const int soDatMoiTrang = 10;

#define RESET  "\033[0m"
#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN   "\033[1;36m"

string matKhauCanBo;
// ================= HÀM TIỆN ÍCH NHẬP LIỆU & IN BẢNG =================

// Hàm in một ô chữ để các cột trong bảng thẳng hàng (bỏ qua byte dấu tiếng Việt)
void inO(string s, int doRong) {
    cout << s;
    int soKyTu = 0;
    for (char c : s) {
        if ((c & 0xc0) != 0x80) soKyTu++;
    }
    for (int i = 0; i < doRong - soKyTu; i++) {
        cout << " ";
    }
}

string vietHoa(string s){
    for (char &c : s) {
        c = toupper(c);
    }
    return s;
}

// Nhập số nguyên an toàn trong đoạn [minVal, maxVal]
int getValidInteger(int minVal, int maxVal) {
    int value;
    while (true) {
        if (cin >> value && value >= minVal && value <= maxVal) {
            return value;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << RED << "Giá trị phải từ " << minVal << " đến " << maxVal << "! Vui lòng thử lại: " << RESET;
    }
}

// Nhập số thực an toàn > minVal
double getValidDouble(double minVal = 0.0) {
    double value;
    while (true) {
        if (cin >> value && value > minVal) {
            return value;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << RED << "Giá trị phải lớn hơn " << minVal << "! Vui lòng thử lại: " << RESET;
    }
}

// ================= QUẢN LÝ MẬT KHẨU CÁN BỘ =================

void docMatKhau() {
    ifstream file("MatKhau.txt");
    if (file >> matKhauCanBo) {
        file.close();
    }
}

bool xacThucCanBo() {
    string mk;
    cout << YELLOW << "Vui lòng nhập mật khẩu cán bộ: " << RESET;
    cin >> mk;
    if (mk == matKhauCanBo) {
        cout << GREEN << "Xác thực thành công!" << RESET << endl;
        return true;
    }
    cout << RED << "Mật khẩu không chính xác!" << RESET << endl;
    return false;
}

void doiMatKhau() {
    string mkCu, mkMoi;
    cout << "Nhập mật khẩu hiện tại: ";
    cin >> mkCu;
    if (mkCu != matKhauCanBo) {
        cout << RED << "Mật khẩu hiện tại không đúng!" << RESET << endl;
        return;
    }
    cout << "Nhập mật khẩu mới: ";
    cin >> mkMoi;
    matKhauCanBo = mkMoi;
    ofstream file("MatKhau.txt");
    if (file) {
        file << matKhauCanBo;
        file.close();
    }
    cout << GREEN << "Đổi mật khẩu thành công và đã lưu lại vào hệ thống!" << RESET << endl;
}

// ================= LỚP CƠ SỞ HÌNH HỌC (Ô ĐẤT) =================

class HinhHoc {
protected:
    string soToSoThua;
    int khuVuc;
    int viTriMatTien;
    int loaiDat;
    bool daCoChu;
    string chuSuDung;
    double mienGiamTheoDoiTuong;

public:
    HinhHoc(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1) {
        soToSoThua = _soToSoThua;
        khuVuc = _khuVuc;
        loaiDat = _loaiDat;
        viTriMatTien = _viTriMatTien;
        daCoChu = false;
        chuSuDung = "Chưa có";
        mienGiamTheoDoiTuong = 0.0;
    }
    virtual ~HinhHoc() {}

    string getSoToSoThua() const { return soToSoThua; }
    bool getDaCoChu() const { return daCoChu; }
    string getChuSuDung() const { return chuSuDung; }
    double getMienGiam() const { return mienGiamTheoDoiTuong; }
    int getLoaiDat() const { return loaiDat; }

    void setChuSuDung(bool _daCoChu, string _chuSuDung, double _mienGiam) {
        daCoChu = _daCoChu;
        chuSuDung = _chuSuDung;
        mienGiamTheoDoiTuong = _mienGiam;
    }

    string getTenKhuVuc() const {
        if (khuVuc == 1) return "Trung tâm";
        if (khuVuc == 2) return "Ngoại ô";
        return "Nông thôn";
    }

    string getTenViTri() const {
        if (viTriMatTien == 1) return "Mặt tiền lớn";
        if (viTriMatTien == 2) return "Hẻm ô tô";
        return "Hẻm nhỏ";
    }

    string getTenLoaiDat() const {
        if (loaiDat == 1) return "Đất ở";
        if (loaiDat == 2) return "Đất kinh doanh";
        return "Đất lấn chiếm";
    }

    string getTenTrangThai() const {
        if (daCoChu) return "Đã có chủ (" + chuSuDung + ")";
        return "Chưa có";
    }

    double tinhThueLuyTien() const {
        double S = tinhDienTich();
        double giaDat = 2000000.0;
        if (khuVuc == 1) giaDat = 10000000.0;
        else if (khuVuc == 2) giaDat = 5000000.0;

        double hsKhuVuc = 1.0;
        if (khuVuc == 1) hsKhuVuc = 2.0;
        else if (khuVuc == 2) hsKhuVuc = 1.5;

        double hsMatTien = 0.8;
        if (viTriMatTien == 1) hsMatTien = 1.2;
        else if (viTriMatTien == 2) hsMatTien = 1.0;

        double tienGoc = giaDat * hsKhuVuc * hsMatTien;

        if (loaiDat == 2) return S * tienGoc * (0.03 / 100.0);
        if (loaiDat == 3) return S * tienGoc * (0.20 / 100.0);

        double hanMuc = 300.0;
        if (khuVuc == 1) hanMuc = 150.0;
        else if (khuVuc == 2) hanMuc = 200.0;

        double thue = min(S, hanMuc) * tienGoc * (0.03 / 100.0);
        if (S > hanMuc) {
            thue += min(S - hanMuc, 2.0 * hanMuc) * tienGoc * (0.07 / 100.0);
        }
        if (S > 3.0 * hanMuc) {
            thue += (S - 3.0 * hanMuc) * tienGoc * (0.15 / 100.0);
        }
        return thue;
    }

    virtual double tinhDienTich() const = 0;
    virtual string getTenHinh() const = 0;
    virtual double getHeSoHinhDang() const = 0;
    virtual void nhapKichThuoc() = 0;
    virtual void ghiVaoFile(ofstream& f) const = 0;

    double tinhThue() const {
        return tinhThueLuyTien() * getHeSoHinhDang();
    }

    double thuePhaiNop() const {
        if (!daCoChu) return 0.0;
        return tinhThue() * (1.0 - mienGiamTheoDoiTuong / 100.0);
    }

    void keKhaiChuSuDung() {
        cout << CYAN << endl << "--- KÊ KHAI HỒ SƠ CHO LÔ ĐẤT [" << soToSoThua << " - " << getTenHinh() << "] ---" << endl << RESET;
        cout << "1. Diện tích: " << fixed << setprecision(2) << tinhDienTich() << " m2" << endl;
        cout << "2. Khu vực: " << getTenKhuVuc() << endl;
        cout << "3. Vị trí mặt tiền: " << getTenViTri() << endl;
        cout << "4. Mục đích quy hoạch: " << getTenLoaiDat() << endl;

        cout << "Nhập họ và tên chủ sở hữu: ";
        getline(cin >> ws, chuSuDung);

        cout << "Xác nhận mục đích sử dụng đất (1: Đất ở, 2: Đất kinh doanh, 3: Đất lấn chiếm): ";
        int chonLoai = getValidInteger(1, 3);
        if (chonLoai != loaiDat) {
            cout << RED << "LỖI: Mục đích sử dụng bạn chọn không khớp với quy hoạch (" << getTenLoaiDat() << ")! Huỷ kê khai." << RESET << endl;
            daCoChu = false;
            return;
        }

        cout << "Chọn đối tượng miễn giảm thuế (1: Không [0%] | 2: Cận nghèo [50%] | 3: Hộ nghèo [100%]): ";
        int doiTuong = getValidInteger(1, 3);
        if (doiTuong == 1) mienGiamTheoDoiTuong = 0.0;
        else if (doiTuong == 2) mienGiamTheoDoiTuong = 50.0;
        else if (doiTuong == 3) mienGiamTheoDoiTuong = 100.0;

        daCoChu = true;
        cout << GREEN << "Khai thuế thành công!" << RESET << endl;
    }

    void themLoDatMoi() {
        cout << "Nhập mã số tờ và số thửa mới (VD: V001-01): ";
        cin >> soToSoThua;
        cout << "Nhập khu vực (1: Trung tâm, 2: Ngoại ô, 3: Nông thôn): ";
        khuVuc = getValidInteger(1, 3);
        cout << "Nhập mục đích quy hoạch (1: Đất ở, 2: Đất kinh doanh, 3: Đất lấn chiếm): ";
        loaiDat = getValidInteger(1, 3);
        cout << "Nhập vị trí mặt tiền (1: Mặt tiền lớn, 2: Hẻm ô tô, 3: Hẻm nhỏ): ";
        viTriMatTien = getValidInteger(1, 3);
        daCoChu = false;
        chuSuDung = "Chưa có";
        mienGiamTheoDoiTuong = 0.0;
        nhapKichThuoc();
    }

    void suaThongTin() {
        while (true) {
            cout << CYAN << endl << "--- CHỈNH SỬA THÔNG TIN Ô ĐẤT [" << soToSoThua << "] ---" << endl << RESET;
            cout << "1. Sửa khu vực (Hiện tại: " << getTenKhuVuc() << ")" << endl;
            cout << "2. Sửa mục đích quy hoạch (Hiện tại: " << getTenLoaiDat() << ")" << endl;
            cout << "3. Sửa vị trí mặt tiền (Hiện tại: " << getTenViTri() << ")" << endl;
            cout << "4. Sửa lại kích thước ô đất" << endl;
            cout << "0. Hoàn tất chỉnh sửa ô đất này" << endl;
            cout << "Chọn mục bạn muốn sửa (0 - 4): ";
            int luaChon = getValidInteger(0, 4);

            if (luaChon == 0) break;
            if (luaChon == 1) {
                cout << "Chọn khu vực mới (1: Trung tâm, 2: Ngoại ô, 3: Nông thôn): ";
                khuVuc = getValidInteger(1, 3);
            }
            else if (luaChon == 2) {
                cout << "Chọn mục đích mới (1: Đất ở, 2: Đất kinh doanh, 3: Đất lấn chiếm): ";
                loaiDat = getValidInteger(1, 3);
            }
            else if (luaChon == 3) {
                cout << "Chọn vị trí mới (1: Mặt tiền lớn, 2: Hẻm ô tô, 3: Hẻm nhỏ): ";
                viTriMatTien = getValidInteger(1, 3);
            }
            else if (luaChon == 4) {
                nhapKichThuoc();
            }
            cout << GREEN << "Cập nhật thành công!" << RESET << endl;
        }
    }
};

// ================= CÁC LỚP HÌNH HỌC CỤ THỂ =================

class HinhChuNhat : public HinhHoc {
    double dai, rong;
public:
    HinhChuNhat(string st = "", int kv = 1, int ld = 1, int vt = 1, double d = 0, double r = 0)
        : HinhHoc(st, kv, ld, vt), dai(d), rong(r) {}

    double tinhDienTich() const override { return dai * rong; }
    string getTenHinh() const override { return "Hình chữ nhật"; }

    double getHeSoHinhDang() const override {
        double mn = min(dai, rong);
        double mx = max(dai, rong);
        if (mn < 3.0) return 0.9;
        if (mn >= 0.4 * mx) return 1.1;
        return 1.0;
    }

    void nhapKichThuoc() override {
        cout << "Nhập chiều dài (m): ";
        dai = getValidDouble();
        cout << "Nhập chiều rộng (m): ";
        rong = getValidDouble();
    }

    void ghiVaoFile(ofstream& f) const override {
        f << "\nHCN " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << dai << " " << rong;
    }
};

class HinhVuong : public HinhHoc {
    double canh;
public:
    HinhVuong(string st = "", int kv = 1, int ld = 1, int vt = 1, double c = 0)
        : HinhHoc(st, kv, ld, vt), canh(c) {}

    double tinhDienTich() const override { return canh * canh; }
    string getTenHinh() const override { return "Hình vuông"; }

    double getHeSoHinhDang() const override {
        if (canh < 3.0) return 0.9;
        return 1.15;
    }

    void nhapKichThuoc() override {
        cout << "Nhập chiều dài cạnh (m): ";
        canh = getValidDouble();
    }

    void ghiVaoFile(ofstream& f) const override {
        f << "\nHV " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << canh;
    }
};

class TamGiac : public HinhHoc {
    double a, b, c;
public:
    TamGiac(string st = "", int kv = 1, int ld = 1, int vt = 1, double _a = 0, double _b = 0, double _c = 0)
        : HinhHoc(st, kv, ld, vt), a(_a), b(_b), c(_c) {}

    double tinhDienTich() const override {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    string getTenHinh() const override { return "Tam giác"; }

    double getHeSoHinhDang() const override {
        double s[3] = { a, b, c };
        sort(s, s + 3);
        if (fabs(s[0] * s[0] + s[1] * s[1] - s[2] * s[2]) < 1e-3) return 0.85;
        return 0.8;
    }

    void nhapKichThuoc() override {
        while (true) {
            cout << "Nhập độ dài ba cạnh a, b, c (m): ";
            a = getValidDouble();
            b = getValidDouble();
            c = getValidDouble();
            if (a + b > c && a + c > b && b + c > a) break;
            cout << RED << "Tổng hai cạnh phải lớn hơn cạnh còn lại! Vui lòng thử lại." << RESET << endl;
        }
    }

    void ghiVaoFile(ofstream& f) const override {
        f << "\nTG " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << a << " " << b << " " << c;
    }
};

class HinhTron : public HinhHoc {
    double banKinh;
public:
    HinhTron(string st = "", int kv = 1, int ld = 1, int vt = 1, double r = 0)
        : HinhHoc(st, kv, ld, vt), banKinh(r) {}

    double tinhDienTich() const override { return PI * banKinh * banKinh; }
    string getTenHinh() const override { return "Hình tròn"; }
    double getHeSoHinhDang() const override { return 0.95; }

    void nhapKichThuoc() override {
        cout << "Nhập bán kính ô đất (m): ";
        banKinh = getValidDouble();
    }

    void ghiVaoFile(ofstream& f) const override {
        f << "\nHT " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << banKinh;
    }
};

// ================= QUẢN LÝ DỮ LIỆU FILE =================

void luuTatCaVaoFile(HinhHoc* ds[], int n) {
    ofstream f("DuLieuBanDo.txt");
    if (!f) return;
    for (int i = 0; i < n; i++) {
        ds[i]->ghiVaoFile(f);
    }
    for (int i = 0; i < n; i++) {
        if (ds[i]->getDaCoChu()) {
            f << "\nKHAI_THUE " << ds[i]->getSoToSoThua() << " " << ds[i]->getMienGiam() << " " << ds[i]->getChuSuDung();
        }
    }
    f.close();
}

void docBanDo(HinhHoc* ds[], int& n) {
    ifstream f("DuLieuBanDo.txt");
    if (!f) return;
    n = 0;
    string loaiHinh, soThua;
    int kv, ld, vt;
    while (f >> loaiHinh && n < 100) {
        if (loaiHinh == "KHAI_THUE") {
            string st;
            double mg;
            string ten;
            f >> st >> mg;
            getline(f >> ws, ten);
            for (int i = 0; i < n; i++) {
                if (ds[i]->getSoToSoThua() == st) {
                    ds[i]->setChuSuDung(true, ten, mg);
                    break;
                }
            }
            continue;
        }
        if (loaiHinh[0] == '[') {
            string rac;
            getline(f, rac);
            continue;
        }
        if (!(f >> soThua >> kv >> ld >> vt)) break;

        if (loaiHinh == "HCN") {
            double d, r; f >> d >> r;
            ds[n++] = new HinhChuNhat(soThua, kv, ld, vt, d, r);
        }
        else if (loaiHinh == "HV") {
            double c; f >> c;
            ds[n++] = new HinhVuong(soThua, kv, ld, vt, c);
        }
        else if (loaiHinh == "TG") {
            double a, b, c; f >> a >> b >> c;
            ds[n++] = new TamGiac(soThua, kv, ld, vt, a, b, c);
        }
        else if (loaiHinh == "HT") {
            double r; f >> r;
            ds[n++] = new HinhTron(soThua, kv, ld, vt, r);
        }
    }
    f.close();
}

// ================= CÁC CHỨC NĂNG HIỂN THỊ & THAO TÁC =================

void inMotTrang(HinhHoc* ds[], int n, int trang){
    int dau = trang * soDatMoiTrang;
    int cuoi = min(dau + soDatMoiTrang, n);
    int tongSoTrang = (n + soDatMoiTrang - 1) / soDatMoiTrang;

    cout << CYAN << endl << string(122, '=') << endl;
    cout << "--- BẢN ĐỒ QUY HOẠCH CÁC Ô ĐẤT CÓ SẴN TRÊN ĐỊA BÀN (Trang " << (trang + 1) << "/" << tongSoTrang << ") ---" << endl;
    cout << string(122, '=') << endl << RESET;

    cout << YELLOW;
    inO("STT", 6);
    inO("Mã số tờ/thửa", 16);
    inO("Hình dáng", 16);
    inO("Diện tích (m2)", 18);
    inO("Khu vực", 14);
    inO("Vị trí mặt tiền", 18);
    inO("Mục đích sử dụng", 18);
    inO("Trạng thái", 25);
    cout << RESET << endl;
    cout << CYAN << string(122, '-') << endl;

    for (int i = dau; i < cuoi; i++) {
        inO("#" + to_string(i + 1), 6);
        inO(ds[i]->getSoToSoThua(), 16);
        inO(ds[i]->getTenHinh(), 16);

        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%.2f", ds[i]->tinhDienTich());
        inO(buffer, 18);

        inO(ds[i]->getTenKhuVuc(), 14);
        inO(ds[i]->getTenViTri(), 18);
        inO(ds[i]->getTenLoaiDat(), 18);
        inO(ds[i]->getTenTrangThai(), 25);
        cout << endl;
    }
    cout << CYAN << string(122, '-') << endl << RESET;
}

void xemBanDo(HinhHoc* ds[], int n) {
    if (n == 0) {
        cout << RED << "Bản đồ quy hoạch hiện đang trống!" << RESET << endl;
        return;
    }

    int trang = 0;
    int tongSoTrang = (n + soDatMoiTrang - 1) / soDatMoiTrang;

while (true) {
        inMotTrang(ds, n, trang);
        if (tongSoTrang <= 1) break;

        if (trang == 0) {
            cout << CYAN << "Điều hướng trang [1: Trang sau | 0: Đóng danh sách]: " << RESET;
            int chon = getValidInteger(0, 1);
            if (chon == 0) break;
            else if (chon == 1) trang++;
        }
        else if (trang == tongSoTrang - 1) {
            cout << CYAN << "Điều hướng trang [1: Trang trước | 0: Đóng danh sách]: " << RESET;
            int chon = getValidInteger(0, 1);
            if (chon == 0) break;
            else if (chon == 1) trang--;
        }
        else {
            cout << CYAN << "Điều hướng trang [1: Trang sau | 2: Trang trước | 0: Đóng danh sách]: " << RESET;
            int chon = getValidInteger(0, 2);
            if (chon == 0) break;
            else if (chon == 1) trang++;
            else if (chon == 2) trang--;
        }
    }
}

int chonLoDat(HinhHoc* ds[], int n, string tenChucNang) {
    if (n == 0) {
        cout << RED << "Bản đồ hiện đang trống, không có ô đất để " << tenChucNang << "!" << RESET << endl;
        return -1;
    }

    while (1){
        cout << endl << "Nhập " << YELLOW << "Mã số tờ - số thửa (VD: V001-01)" << RESET << " hoặc " << YELLOW << "#STT" << RESET << " (1 - " << n << ") (VD: #1) của ô đất muốn " << tenChucNang << " (nhập " << CYAN << "?" << RESET << " để xem danh sách, " << RED << "0" << RESET << " để huỷ): ";
        string choice;
        cin >> choice;

        if (choice == "0") return -1;
        if (choice == "?") {
            xemBanDo(ds, n);
            continue;
        }
        if (choice[0] == '#') {
            int stt = stoi(choice.substr(1));
            if (stt >= 1 && stt <= n) return stt - 1;
            cout << RED << "STT không hợp lệ! Vui lòng thử lại." << RESET << endl;
            continue;
        }

        string maSo = vietHoa(choice);
        for (int i = 0;i < n;i++){
            if (vietHoa(ds[i]->getSoToSoThua()) == maSo) {
                return i;
            }
        }
        cout << RED << "Không tìm thấy ô đất với mã số [" << maSo << "]! Vui lòng thử lại." << RESET << endl;
    }
}

void timKiemLoDat(HinhHoc* ds[], int n) {
    int viTri = chonLoDat(ds, n, "tra cứu");
    if (viTri < 0) return;

    HinhHoc* dat = ds[viTri];
    cout << GREEN << endl << "✓ TÌM THẤY THÔNG TIN Ô ĐẤT [#" << (viTri + 1) << " | " << dat->getSoToSoThua() << " - " << dat->getTenHinh() << "]:" << RESET << endl;
    cout << "1. Diện tích         : " << fixed << setprecision(2) << dat->tinhDienTich() << " m2" << endl;
    cout << "2. Khu vực           : " << dat->getTenKhuVuc() << endl;
    cout << "3. Vị trí mặt tiền   : " << dat->getTenViTri() << endl;
    cout << "4. Mục đích quy hoạch: " << dat->getTenLoaiDat() << endl;
    cout << "5. Trạng thái        : " << dat->getTenTrangThai() << endl;
    if (dat->getDaCoChu()) {
        cout << "6. Thuế phát sinh    : " << fixed << setprecision(0) << dat->tinhThue() << " VND (Miễn giảm: " << dat->getMienGiam() << "%)" << endl;
        cout << "=> THUẾ PHẢI NỘP     : " << YELLOW << fixed << setprecision(0) << dat->thuePhaiNop() << " VND" << RESET << endl;
    }
}

void thongKeBaoCao(HinhHoc* ds[], int n) {
    int coChu = 0;
    double tongThue = 0.0;
    for (int i = 0; i < n; i++) {
        if (ds[i]->getDaCoChu()) {
            coChu++;
            tongThue += ds[i]->thuePhaiNop();
        }
    }
    cout << CYAN << endl << string(60, '=') << endl;
    cout << "             BÁO CÁO THỐNG KÊ QUẢN LÝ ĐỊA BÀN" << endl;
    cout << string(60, '=') << endl << RESET;
    cout << "1. Tổng số ô đất trên địa bàn : " << n << " ô đất" << endl;
    cout << "2. Số ô đất đã kê khai thuế   : " << GREEN << coChu << " ô đất" << RESET << endl;
    cout << "3. Số ô đất còn trống         : " << YELLOW << (n - coChu) << " ô đất" << RESET << endl;
    cout << "4. Tổng số tiền thuế đã thu   : " << CYAN << fixed << setprecision(0) << tongThue << " VND" << RESET << endl;
    cout << CYAN << string(60, '-') << endl << RESET;
}

void khaiThue(HinhHoc* a[], int n) {
    int idx = chonLoDat(a, n, "khai thuế");
    if (idx < 0) return;

    HinhHoc* dat = a[idx];
    if (dat->getDaCoChu()) {
        cout << RED << "Ô đất này đã có chủ (" << dat->getChuSuDung() << ")! Không thể khai thuế tiếp." << RESET << endl;
        return;
    }

    dat->keKhaiChuSuDung();
    if (!dat->getDaCoChu()) return;

    luuTatCaVaoFile(a, n);
    cout << GREEN << "Đã lưu thông tin kê khai thuế!" << RESET << endl;

    cout << GREEN << endl << "--- BIÊN LAI THUẾ LÔ ĐẤT [" << dat->getSoToSoThua() << "] ---" << RESET << endl;
    cout << "1. Chủ sử dụng         : " << dat->getChuSuDung() << endl;
    cout << "2. Diện tích           : " << fixed << setprecision(2) << dat->tinhDienTich() << " m2" << endl;
    cout << "3. Khu vực             : " << dat->getTenKhuVuc() << endl;
    cout << "4. Vị trí mặt tiền     : " << dat->getTenViTri() << endl;
    cout << "5. Mục đích sử dụng    : " << dat->getTenLoaiDat() << endl;
    cout << "6. Thuế phát sinh      : " << fixed << setprecision(0) << dat->tinhThue() << " VND" << endl;
    cout << "7. Miễn giảm           : " << dat->getMienGiam() << " %" << endl;
    cout << "=> THUẾ PHẢI NỘP       : " << YELLOW << fixed << setprecision(0) << dat->thuePhaiNop() << " VND" << RESET << endl;
}

// ================= CÁC TÁC VỤ CỦA CÁN BỘ =================

void themLoDat(HinhHoc* ds[], int& n) {
    if (n >= 100) {
        cout << RED << "Bản đồ đã đầy (tối đa 100 ô đất)! Không thể thêm tiếp." << RESET << endl;
        return;
    }

    string maMoi;
    while (true) {
        cout << endl << "Nhập mã số tờ và số thửa mới (VD: V001-01 | nhập " << CYAN << "?" << RESET << " để xem DS, " << RED << "0" << RESET << " để huỷ): ";
        cin >> maMoi;
        if (maMoi == "0") return;
        if (maMoi == "?") {
            xemBanDo(ds, n);
            continue;
        }
        if (maMoi[0] == '#') {
            cout << RED << "Mã số tờ/thửa không được bắt đầu bằng dấu '#'!" << RESET << endl;
            continue;
        }
        bool biTrung = false;
        for (int i = 0; i < n; i++) {
            if (vietHoa(ds[i]->getSoToSoThua()) == vietHoa(maMoi)) {
                cout << RED << "Lỗi: Mã số thửa [" << maMoi << "] đã tồn tại ở STT #" << (i + 1) << "! Hãy nhập mã khác." << RESET << endl;
                biTrung = true;
                break;
            }
        }
        if (!biTrung) break;
    }

    cout << "Chọn hình dáng ô đất mới (1: Hình chữ nhật | 2: Hình vuông | 3: Tam giác | 4: Hình tròn): ";
    int loaiHinh = getValidInteger(1, 4);
    if (loaiHinh == 0) return;
    HinhHoc* datMoi = NULL;
    if (loaiHinh == 1) datMoi = new HinhChuNhat();
    else if (loaiHinh == 2) datMoi = new HinhVuong();
    else if (loaiHinh == 3) datMoi = new TamGiac();
    else if (loaiHinh == 4) datMoi = new HinhTron();

    datMoi->themLoDatMoi();
    ds[n++] = datMoi;
    luuTatCaVaoFile(ds, n);
    cout << GREEN << "Thêm ô đất mới thành công!" << RESET << endl;
}

void suaLoDat(HinhHoc* ds[], int n) {
    int idx = chonLoDat(ds, n, "chỉnh sửa");
    if (idx < 0) return;
    ds[idx]->suaThongTin();
    luuTatCaVaoFile(ds, n);
    cout << GREEN << "Đã cập nhật thành công!" << RESET << endl;
}

void xoaLoDat(HinhHoc* ds[], int& n) {
    int idx = chonLoDat(ds, n, "xoá");
    if (idx < 0) return;

    cout << YELLOW << "Bạn có chắc chắn muốn xoá ô đất [" << ds[idx]->getSoToSoThua() << "]? (1: Có | 0: Huỷ): " << RESET;
    if (getValidInteger(0, 1) == 1) {
        delete ds[idx];
        for (int i = idx; i < n - 1; i++) {
            ds[i] = ds[i + 1];
        }
        n--;
        luuTatCaVaoFile(ds, n);
        cout << GREEN << "Xoá ô đất thành công!" << RESET << endl;
    }
    else {
        cout << "Đã huỷ thao tác xoá." << endl;
    }
}

void xoaKhaiThue(HinhHoc* ds[], int n) {
    int idx = chonLoDat(ds, n, "xoá kê khai thuế");
    if (idx < 0) return;

    HinhHoc* dat = ds[idx];
    if (!dat->getDaCoChu()) {
        cout << RED << "Ô đất này hiện chưa có chủ để xoá kê khai!" << RESET << endl;
        return;
    }

    cout << YELLOW << "Xác nhận xoá kê khai của chủ sở hữu [" << dat->getChuSuDung()
        << "] cho ô đất [" << dat->getSoToSoThua() << "]? (1: Đồng ý | 0: Huỷ): " << RESET;
    if (getValidInteger(0, 1) == 1) {
        dat->setChuSuDung(false, "Chưa có", 0.0);
        luuTatCaVaoFile(ds, n);
        cout << GREEN << "Đã xoá kê khai thành công! Ô đất đã trở về trạng thái 'Chưa có chủ'." << RESET << endl;
    }
    else {
        cout << "Đã huỷ thao tác." << endl;
    }
}

void menuCanBo(HinhHoc* ds[], int& n) {
    if (!xacThucCanBo()) return;

    while (true) {
        cout << CYAN << endl << string(60, '=') << endl << RESET;
        cout << CYAN << "             KHU VỰC DÀNH CHO CÁN BỘ QUẢN LÝ" << endl << RESET;
        cout << CYAN << string(60, '=') << endl << RESET;
        cout << "1. Thêm ô đất mới vào bản đồ quy hoạch" << endl;
        cout << "2. Chỉnh sửa thông tin ô đất" << endl;
        cout << "3. Xoá ô đất khỏi bản đồ quy hoạch" << endl;
        cout << "4. Hủy kê khai của người dân (reset ô đất)" << endl;
        cout << "5. Xem báo cáo thống kê đất đai và thuế" << endl;
        cout << "6. Thay đổi mật khẩu cán bộ" << endl;
        cout << "0. Quay lại menu chính" << endl;
        cout << CYAN << string(60, '-') << endl << RESET;
        cout << "Nhập lựa chọn của bạn: ";

        int sub = getValidInteger(0, 6);
        if (sub == 0) break;

        if (sub == 1) themLoDat(ds, n);
        else if (sub == 2) suaLoDat(ds, n);
        else if (sub == 3) xoaLoDat(ds, n);
        else if (sub == 4) xoaKhaiThue(ds, n);
        else if (sub == 5) thongKeBaoCao(ds, n);
        else if (sub == 6) doiMatKhau();
    }
}

// ======================= CHƯƠNG TRÌNH CHÍNH =======================

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    docMatKhau();
    HinhHoc* ds[100];
    int n = 0;
    docBanDo(ds, n);

    while (true) {
        system("cls");
        cout << CYAN << endl << string(85, '=') << endl << RESET;
        cout << CYAN << "HỆ THỐNG QUẢN LÝ QUY HOẠCH & THUẾ ĐẤT" << endl << RESET;
        cout << CYAN << string(85, '=') << endl << RESET;
        cout << "1. Xem bản đồ quy hoạch (Danh sách các ô đất có sẵn trên địa bàn)" << endl;
        cout << "2. Tra cứu thông tin ô đất theo mã số tờ/thửa" << endl;
        cout << "3. [Người dân] Chọn ô đất có sẵn trên bản đồ để đăng ký & tính thuế" << endl;
        cout << "4. [Cán bộ] Khu vực quản lý của cán bộ (Cần mật khẩu)" << endl;
        cout << "0. Thoát chương trình" << endl;
        cout << CYAN << string(85, '-') << endl << RESET;
        cout << "Nhập lựa chọn của bạn: ";

        int choice = getValidInteger(0, 4);
        if (choice == 0) {
            cout << YELLOW << "Cảm ơn bạn đã sử dụng hệ thống!" << RESET << endl;
            break;
        }

        if (choice == 1) xemBanDo(ds, n);
        else if (choice == 2) timKiemLoDat(ds, n);
        else if (choice == 3) khaiThue(ds, n);
        else if (choice == 4) menuCanBo(ds, n);

        cout << endl << "Nhấn Enter để tiếp tục...";
        cin.ignore(1000, '\n');
        cin.get();
    }

    for (int i = 0; i < n; i++) {
        delete ds[i];
    }
    return 0;
}
