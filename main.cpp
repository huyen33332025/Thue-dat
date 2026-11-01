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
const double thueSuatTrongHanMuc_DatO = 0.03/100.0;
const double thueSuatTrong3LanHanMuc_DatO = 0.07/100.0;
const double thueSuatVuot3LanHanMuc_DatO = 0.15/100.0;
const double thueSuatDatXSKD = 0.03/100.0;
const double thueDatLanChiem = 0.2/100.0;
const int giaDatNhaNuoc_TrungTam = 10000000;
const int giaDatNhaNuoc_NgoaiO = 5000000;
const int giaDatNhaNuoc_NongThon = 2000000;

#define RESET  "\033[0m"
#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN   "\033[1;36m"

class HinhHoc {
protected:
    string soToSoThua;
    int khuVuc;
    int viTriMatTien;
    double giaDatNhaNuoc;

    bool daCoChu;
    string chuSuDung;
    int loaiDat;
    double mienGiamTheoDoiTuong;
public:
    HinhHoc(string _soToSoThua = "", bool _daCoChu = 0, string _chuSuDung = "Chưa có", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _mienGiamTheoDoiTuong = 0.0)
        : soToSoThua(_soToSoThua), khuVuc(_khuVuc), viTriMatTien(_viTriMatTien), daCoChu(_daCoChu), chuSuDung(_chuSuDung), loaiDat(_loaiDat), mienGiamTheoDoiTuong(_mienGiamTheoDoiTuong) {
        if (khuVuc == 1) giaDatNhaNuoc = giaDatNhaNuoc_TrungTam;
        else if (khuVuc == 2) giaDatNhaNuoc = giaDatNhaNuoc_NgoaiO;
        else giaDatNhaNuoc = giaDatNhaNuoc_NongThon;
    }
    virtual ~HinhHoc() {}

    string getSoToSoThua() const { return soToSoThua; }
    bool getDaCoChu() const { return daCoChu; }
    string getChuSuDung() const { return chuSuDung; }
    double getMienGiamTheoDoiTuong() const { return mienGiamTheoDoiTuong; }
    int getLoaiDat() const { return loaiDat; }
    string getKhuVuc() const {
        if (khuVuc == 1) return "Trung tâm";
        else if (khuVuc == 2) return "Ngoại ô";
        else if (khuVuc == 3) return "Nông thôn";
        return "Không xác định";
    }
    string getViTriMatTien() const {
        if (viTriMatTien == 1) return "Mặt tiền lớn";
        else if (viTriMatTien == 2) return "Hẻm ô tô";
        else return "Hẻm nhỏ";
     }

     double getHanMuc() const {
        if (khuVuc == 1) return 150.0;
        else if (khuVuc == 2) return 200.0;
        return 300.0;
     }

     double getHeSoKhuVuc() const {
        if (khuVuc == 1) return 2.0;
        else if (khuVuc == 2) return 1.5;
        else return 1.0;
     }

     double getHeSoMatTien() const {
        if (viTriMatTien == 1) return 1.2;
        else if (viTriMatTien == 2) return 1.0;
        else return 0.8;
     }

     double tinhThueLuyTien() const {
        double S = tinhDienTich();
        double tienGoc = giaDatNhaNuoc * getHeSoKhuVuc() * getHeSoMatTien();
        if (loaiDat == 2) return S * tienGoc * thueSuatDatXSKD;
        if (loaiDat == 3) return S * tienGoc * thueDatLanChiem;

        double hm = getHanMuc();
        if (S <= hm){
            return S * tienGoc * thueSuatTrongHanMuc_DatO;
        }
        else if (S <= 3 * hm){
            double thueTrongHanMuc = hm * thueSuatTrongHanMuc_DatO;
            double thueVuotHanMuc = (S - hm) * thueSuatTrong3LanHanMuc_DatO;
            return tienGoc * (thueTrongHanMuc + thueVuotHanMuc);
        }
        else {
            double thueTrongHanMuc = hm * thueSuatTrongHanMuc_DatO;
            double thueTrong3Lan = (2 * hm) * thueSuatTrong3LanHanMuc_DatO;
            double thueVuot3Lan = (S - 3*hm) * thueSuatVuot3LanHanMuc_DatO;
            return tienGoc * (thueTrongHanMuc + thueTrong3Lan + thueVuot3Lan);
        }
     }

     //Đa hình
     virtual double tinhDienTich() const = 0;
     virtual double tinhChuVi() const = 0;
     virtual string getTenHinh() const = 0;
     virtual double getHeSoHinhDang() const = 0;
     virtual double tinhThue() const = 0;
     virtual void ghiVaoFile(ofstream &f) const = 0;

     double thuePhaiNop() const {
        if (daCoChu == false) return 0;
        return tinhThue() * (1.0 - mienGiamTheoDoiTuong / 100.0);
     }

     void keKhaiChuSuDung(){
        cin.ignore();
        cout << CYAN << endl << "--- KÊ KHAI HỒ SƠ CHO LÔ ĐẤT [" << soToSoThua << " - " << getTenHinh() << "] ---" << endl << RESET;
        cout << "Thông tin lô đất: " << endl;
        cout << "1. Diện tích: " << fixed << setprecision(2) << tinhDienTich() << " m2" << endl;
        cout << "2. Khu vực: " << getKhuVuc() << endl;
        cout << "3. Vị trí mặt tiền: " << getViTriMatTien() << endl;

        cout << "Nhập họ và tên chủ sở hữu: ";
        getline(cin, chuSuDung);
        while (1){
            cout << "Chọn mục đích sử dụng đất (1: Đất ở, 2: Đất kinh doanh, 3: Đất lấn chiếm): ";
            cin >> loaiDat;
            if (loaiDat >= 1 && loaiDat <= 3) break;
            cout << RED << "Lựa chọn không hợp lệ! Vui lòng thử lại.";
        }

        int doiTuong;
        while (1){
            cout << "Chọn đối tượng được miễn giảm thuế (1: Không [0%] | 2: Hộ cận nghèo/Thương binh [50%] | 3: Hộ nghèo/Mẹ Việt Nam anh hùng [100%]): ";
            cin >> doiTuong;
            if (doiTuong == 1) {
                mienGiamTheoDoiTuong = 0.0;
                break;
            }
            else if (doiTuong == 2) {
                mienGiamTheoDoiTuong = 50.0;
                break;
            }
            else if (doiTuong == 3) {
                mienGiamTheoDoiTuong = 100.0;
                break;
            }
            cout << RED << "Lựa chọn không hợp lệ! Vui lòng thử lại." << RESET << endl;
        }
        daCoChu = true;
     }

     virtual void themLoDatMoi(){
        cin.ignore(1000, '\n');
        cout << "Nhập mã số tờ và số thửa mới (VD: T001-01): ";
        getline(cin, soToSoThua);
        while (soToSoThua.empty() || soToSoThua.back() == '\r') {
            cout << "Vui lòng không nhập khoảng trắng! Mời bạn nhập lại mã số tờ và số thửa mới: " << endl;
            getline(cin, soToSoThua);
        }
        khuVuc = 0;
        while (khuVuc < 1 || khuVuc > 3){
            cout << "Nhập khu vực (1: Trung tâm, 2: Ngoại ô, 3: Nông thôn): ";
            cin >> khuVuc;
            if (khuVuc < 1 || khuVuc > 3) cout << RED << "Khu vực không hợp lệ! Vui lòng nhập 1-3." << RESET << endl;
        }
        loaiDat = 0;
        while (loaiDat < 1 || loaiDat > 3) {
            cout << "Nhập mục đích quy hoạch (1: Đất ở, 2: Đất kinh doanh, 3: Đất lấn chiếm): ";
            cin >> loaiDat;
            if (loaiDat < 1 || loaiDat > 3) cout << RED << "Loại đất không hợp lệ! Vui lòng nhập 1-3." << RESET << endl;
        }
        viTriMatTien = 0;
        while (viTriMatTien < 1 || viTriMatTien > 3){
            cout << "Nhập vị trí mặt tiền (1: Mặt tiền lớn, 2: Hẻm ô tô, 3: Hẻm nhỏ): ";
            cin >> viTriMatTien;
            if (viTriMatTien < 1 || viTriMatTien > 3) cout << RED << "Vị trí không hợp lệ! Vui lòng nhập 1-3." << RESET << endl;
        }
        if (khuVuc == 1) giaDatNhaNuoc = giaDatNhaNuoc_TrungTam;
        else if (khuVuc == 2) giaDatNhaNuoc = giaDatNhaNuoc_NgoaiO;
        else giaDatNhaNuoc = giaDatNhaNuoc_NongThon;

        daCoChu = false;
        chuSuDung = "Chưa có";
        mienGiamTheoDoiTuong = 0.0;
        cout << "-> Hệ thống tự động áp Bảng giá đất Nhà nước theo khu vực " << YELLOW << getKhuVuc() << RESET << ": " << fixed << setprecision(0) << giaDatNhaNuoc << " VND/m2" << endl;
     }

};

class HinhChuNhat : public HinhHoc {
protected:
    double dai, rong;
public:
    HinhChuNhat(string _soToSoThua = "", bool _daCoChu = 0, string _chuSuDung = "Chưa có", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _mienGiamTheoDoiTuong = 0.0, double _dai = 0, double _rong = 0)
        : HinhHoc(_soToSoThua, _daCoChu, _chuSuDung, _khuVuc, _loaiDat, _viTriMatTien, _mienGiamTheoDoiTuong), dai(_dai), rong(_rong) {}

    double tinhDienTich() const override {
        return dai * rong;
    }

    double tinhChuVi() const override {
        return 2 * (dai + rong);
    }

    string getTenHinh() const override {
        return "Hình chữ nhật";
    }

    double getHeSoHinhDang() const override{
        double MIN = min(dai, rong);
        double MAX = max(dai, rong);
        if (MIN < 3.0) return 0.9;
        if (MIN >= 0.4 * MAX) return 1.1;
        return 1.0;
    }

    double tinhThue() const override {
        return tinhThueLuyTien() * getHeSoHinhDang();
    }

    void themLoDatMoi() override {
        HinhHoc::themLoDatMoi();
        while (dai <= 0 || rong <= 0){
            cout << "Nhập chiều dài và chiều rộng ô đất(m): ";
            cin >> dai >> rong;
            if (dai <= 0 || rong <= 0) cout << RED << "Chiều dài và chiều rộng phải lớn hơn 0! Vui lòng thử lại." << RESET << endl;
        }
    }

    void ghiVaoFile(ofstream &f) const override {
        f << "\nHCN " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << dai << " " << rong;
    }

};

class HinhVuong : public HinhHoc {
private:
    double canh;
public:
    HinhVuong(string _soToSoThua = "", bool _daCoChu = 0, string _chuSuDung = "Chưa có", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _mienGiamTheoDoiTuong = 0.0, double _canh = 0)
        : HinhHoc(_soToSoThua, _daCoChu, _chuSuDung, _khuVuc, _loaiDat, _viTriMatTien, _mienGiamTheoDoiTuong), canh(_canh) {}

    double tinhDienTich() const override {
        return canh * canh;
    }

    double tinhChuVi() const override {
        return 4.0 * canh;
    }

    string getTenHinh() const override {
        return "Hình vuông";
    }

    double getHeSoHinhDang() const override {
        if (canh < 3.0) return 0.9;
        return 1.15;
    }

    double tinhThue() const override {
        return tinhThueLuyTien() * getHeSoHinhDang();
    }

    void themLoDatMoi() override {
        HinhHoc::themLoDatMoi();
        while (canh <= 0){
            cout << "Nhập chiều dài cạnh ô đất(m): ";
            cin >> canh;
            if (canh <= 0) cout << RED << "Chiều dài cạnh phải lớn hơn 0! Vui lòng thử lại." << RESET << endl;
        }
    }

    void ghiVaoFile(ofstream &f) const override {
        f << "\nHV " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << canh;
    }

};

class TamGiac : public HinhHoc {
private:
    double a, b, c;
public:
    TamGiac(string _soToSoThua = "", bool _daCoChu = 0, string _chuSuDung = "Chưa có", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _mienGiamTheoDoiTuong = 0.0, double _a = 0, double _b = 0, double _c = 0)
        : HinhHoc(_soToSoThua, _daCoChu, _chuSuDung, _khuVuc, _loaiDat, _viTriMatTien, _mienGiamTheoDoiTuong), a(_a), b(_b), c(_c) {}

    double tinhDienTich() const override {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    double tinhChuVi() const override {
        return a + b + c;
    }

    double getHeSoHinhDang() const override {
        double s[3] = {a, b, c};
        sort(s, s + 3);
        if (abs(s[0] * s[0] + s[1] * s[1] - s[2] * s[2]) < 1e-3) return 0.85;
        return 0.8;
    }

    string getTenHinh() const override {
        return "Tam giác";
    }

    double tinhThue() const override {
        return tinhThueLuyTien() * getHeSoHinhDang();
    }

    void themLoDatMoi() override {
        HinhHoc::themLoDatMoi();
        while (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a){
            cout << "Nhập độ dài ba cạnh a, b, c của ô đất(m): ";
            cin >> a >> b >> c;
            if (a <= 0 || b <= 0 || c <= 0) cout << RED << "Độ dài các cạnh phải lớn hơn 0! Vui lòng thử lại." << RESET << endl;
            else if (a + b <= c || a + c <= b || b + c <= a) cout << RED << "Tổng hai cạnh phải lớn hơn cạnh còn lại! Vui lòng thử lại." << RESET << endl;
        }
    }
    void ghiVaoFile(ofstream &f) const override {
        f << "\nTG " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << a << " " << b << " " << c;
    }
};

class HinhTron : public HinhHoc {
private:
    double banKinh;
public:
    HinhTron(string _soToSoThua = "", bool _daCoChu = 0, string _chuSuDung = "Chưa có", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _mienGiamTheoDoiTuong = 0.0, double _banKinh = 0)
        : HinhHoc(_soToSoThua, _daCoChu, _chuSuDung, _khuVuc, _loaiDat, _viTriMatTien, _mienGiamTheoDoiTuong), banKinh(_banKinh) {}
    double tinhDienTich() const override {
        return PI * banKinh * banKinh;
    }

    double tinhChuVi() const override {
        return 2.0 * PI * banKinh;
    }

    string getTenHinh() const override {
        return "Hình tròn";
    }

    double getHeSoHinhDang() const override {
        return 0.95;
    }

    double tinhThue() const override {
        return tinhThueLuyTien() * getHeSoHinhDang();
    }

    void themLoDatMoi() override {
        HinhHoc::themLoDatMoi();
        while (banKinh <= 0){
            cout << "Nhập bán kính ô đất(m): ";
            cin >> banKinh;
            if (banKinh <= 0) cout << RED << "Bán kính phải lớn hơn 0! Vui lòng thử lại." << RESET << endl;
        }
    }
    void ghiVaoFile(ofstream &f) const override {
        f << "\nHT " << soToSoThua << " " << khuVuc << " " << loaiDat << " " << viTriMatTien << " " << banKinh;
    }
};

void khaiThue(HinhHoc *a[], int n){
    int stt;
    while (1){
        cout << "Nhập số thứ tự ô đất muốn khai thuế (1 -" << n << ", nhập 0 để huỷ): ";
        cin >> stt;
        if (stt == 0) return;
        if (stt < 0 || stt > n){
            cout << RED << "Số thứ tự không hợp lệ! Vui lòng thử lại." << RESET << endl;
        } else {
            break;
        }
    }
    if (a[stt - 1]->getDaCoChu() == true){
        cout << RED << "Ô đất này đã có chủ! Không thể khai thuế." << RESET << endl;
        return;
    }
    a[stt - 1]->keKhaiChuSuDung();

    cout << GREEN << "Khai thuế thành công! Biên lai thuế của lô đất [" << a[stt - 1]->getSoToSoThua() << "]:" << RESET << endl;
    cout << "1. Chủ sử dụng              : " << a[stt - 1]->getChuSuDung() << endl;
    cout << "2. Diện tích                : " << fixed << setprecision(2) << a[stt - 1]->tinhDienTich() << " m2" << endl;
    cout << "3. Khu vực                  : " << a[stt - 1]->getKhuVuc() << endl;
    cout << "4. Vị trí mặt tiền          : " << a[stt - 1]->getViTriMatTien() << endl;
    cout << "5. Mục đích sử dụng         : " << a[stt - 1]->getLoaiDat() << endl;
    cout << "6. Thuế phát sinh           : " << fixed << setprecision(2) << a[stt - 1]->tinhThue() << " VND" << endl;
    cout << "7. Miễn giảm theo đối tượng : " << fixed << setprecision(2) << a[stt - 1]->getMienGiamTheoDoiTuong() << " %" << endl;
    cout << "=> THUẾ PHẢI NỘP            : " << fixed << setprecision(2) << a[stt - 1]->thuePhaiNop() << " VND" << endl;
}

void docBanDo(HinhHoc *ds[], int& n) {
    ifstream fileIn("DuLieuBanDo.txt");
    if (!fileIn) {
        cout << RED << "Không thể mở file DuLieuBanDo.txt!" << RESET << endl;
        return;
    }
    n = 0;
    string loaiHinh, soThua;
    int _khuVuc, _loaiDat, _viTriMatTien;
    while (fileIn >> loaiHinh >> soThua >> _khuVuc >> _loaiDat >> _viTriMatTien) {
        if (loaiHinh == "HCN") {
            double dai, rong;
            fileIn >> dai >> rong;
            ds[n++] = new HinhChuNhat(soThua, false, "Chưa có", _khuVuc, _loaiDat, _viTriMatTien, 0.0, dai, rong);
        }
        else if (loaiHinh == "HV") {
            double canh;
            fileIn >> canh;
            ds[n++] = new HinhVuong(soThua, false, "Chưa có", _khuVuc, _loaiDat, _viTriMatTien, 0.0, canh);
        } else if (loaiHinh == "TG") {
            double a, b, c;
            fileIn >> a >> b >> c;
            ds[n++] = new TamGiac(soThua, false, "Chưa có", _khuVuc, _loaiDat, _viTriMatTien, 0.0, a, b, c);
        } else if (loaiHinh == "HT") {
            double r;
            fileIn >> r;
            ds[n++] = new HinhTron(soThua, false, "Chưa có", _khuVuc, _loaiDat, _viTriMatTien, 0.0, r);
        }
    }
    fileIn.close();
}

void xemBanDo(HinhHoc *ds[], int n) {
    if (n == 0) {
        cout << RED << "Bản đồ quy hoạch hiện đang trống! Vui lòng thêm ô đất mới!" << RESET << endl;
        return;
    }
    cout << CYAN << endl << string(122, '=') << endl;
    cout << "--- BẢN ĐỒ QUY HOẠCH CÁC Ô ĐẤT CÓ SẴN TRÊN ĐỊA BÀN ---" << endl;
    cout << string(122, '=') << endl << RESET;

    cout << YELLOW << left << setw(5) << "STT" << setw(15) << "Mã số tờ/thửa" << setw(20) << "Hình dáng"
         << setw(15) << "Diện tích (m2)" << setw(15) << "Khu vực" << setw(20) << "Vị trí mặt tiền"
         << setw(15) << "Mục đích sử dụng" << setw(15) << "Trạng thái" << RESET << endl;

    for (int i = 0; i < n; ++i) {
        cout << left << setw(5) << (i + 1) << setw(15) << ds[i]->getSoToSoThua() << setw(20) << ds[i]->getTenHinh()
             << setw(15) << fixed << setprecision(2) << ds[i]->tinhDienTich() << setw(15) << ds[i]->getKhuVuc()
             << setw(20) << ds[i]->getViTriMatTien() << setw(15) << ds[i]->getLoaiDat()
             << setw(15) << (ds[i]->getDaCoChu() ? "Đã có chủ" : "Chưa có chủ") << endl;
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HinhHoc *ds[100];
    int n = 0, choice;
    docBanDo(ds, n);
    while (1){
        system("cls");
        cout << CYAN << endl << string(85, '=') << endl << RESET;
        cout << CYAN << "HỆ THỐNG QUẢN LÝ QUY HOẠCH & THUẾ ĐẤT" << endl << RESET;
        cout << CYAN << string(85, '=') << endl << RESET;
        cout << "1. Xem bản đồ quy hoạch (Danh sách các ô đất có sẵn trên địa bàn)" << endl;
        cout << "2. [Người dân] Chọn ô đất có sẵn trên bản đồ để đăng ký & tính thuế" << endl;
        cout << "3. [Cán bộ] Thêm ô đất mới vào bản đồ quy hoạch" << endl;
        cout << "0. Thoát chương trình" << endl;
        cout << CYAN << string(85, '-') << endl << RESET;
        cout << "Nhập lựa chọn của bạn: ";
        cin >> choice;

        if (choice == 0){
            cout << YELLOW << "Cảm ơn bạn đã sử dụng hệ thống!" << RESET << endl;
            break;
        }
        switch (choice){
            case 1:
                xemBanDo(ds, n);
                break;
            case 2:
                khaiThue(ds, n);
                break;
            case 3: {
                cout << CYAN << endl << "--- ĐO ĐẠC VÀ THÊM Ô ĐẤT MỚI VÀO BẢN ĐỒ ---" << RESET << endl;
                if (n >= 100){
                    cout << RED << "Bản đồ đã đầy! Không thể thêm ô đất mới!" << RESET << endl;
                    break;
                }
                int loaiHinh;
                cout << "Chọn hình dáng ô đất mới (1. Hình chữ nhật | 2. Hình vuông | 3. Tam giác | 4. Hình tròn): ";
                cin >> loaiHinh;
                if (loaiHinh == 1) ds[n] = new HinhChuNhat();
                else if (loaiHinh == 2) ds[n] = new HinhVuong();
                else if (loaiHinh == 3) ds[n] = new TamGiac();
                else if (loaiHinh == 4) ds[n] = new HinhTron();
                else {
                    cout << RED << "Lựa chọn không hợp lệ! Vui lòng thử lại." << RESET << endl;
                    break;
                }
                ds[n]->themLoDatMoi();
                bool biTrung = false;
                for (int i = 0;i < n;i++){
                    if (ds[i]->getSoToSoThua() == ds[n]->getSoToSoThua()) {
                        cout << RED << "Lỗi: Mã số tờ/thửa [" << ds[n]->getSoToSoThua() << "] đã tồn tại trên bản đồ! Huỷ thêm." << RESET << endl;
                        delete ds[n];
                        biTrung = true;
                        break;
                    }
                }
                if(biTrung == true) break;
                ofstream fileOut("DuLieuBanDo.txt", ios::app);
                if (fileOut.is_open()) {
                    ds[n]->ghiVaoFile(fileOut);
                    fileOut.close();
                }
                n++;
                cout << GREEN << "Thêm ô đất mới thành công! (Trạng thái: Chưa có chủ)" << RESET << endl;
                break;
            }
            default:
                cout << RED << "Lựa chọn không hợp lệ! Vui lòng thử lại." << RESET << endl;
        }
        cout << endl << "Nhấn Enter để tiếp tục...";
        cin.ignore();
        cin.get();
    }

    for (int i = 0; i < n; ++i){
        delete ds[i];
    }
    return 0;
}
