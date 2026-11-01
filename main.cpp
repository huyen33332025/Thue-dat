#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
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
    string ChuSoHuu;
    int loaiDat;
    double mienGiamTheoDoiTuong;
public:
    HinhHoc(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1)
        : soToSoThua(_soToSoThua), khuVuc(_khuVuc), loaiDat(_loaiDat), viTriMatTien(_viTriMatTien) {}
    virtual ~HinhHoc() {}

    string getSoToSoThua() const { return soToSoThua; }
    bool getDaCoChu() const { return daCoChu; }
    string getChuSoHuu() const { return ChuSoHuu; }
    double getMienGiamTheoDoiTuong() const { return mienGiamTheoDoiTuong; }
    int getLoaiDat() const { return loaiDat; }
    string getKhuVuc() const {
        if (khuVuc == 1) return "Trung tâm";
        else if (khuVuc == 2) return "Ngoại ô";
        else if (khuVuc == 3) return "Nông thôn";
        else return "Không xác định";
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
        else if (loaiDat == 3) return S * tienGoc * thueDatLatChiem;

        double hm = getHanMuc();
        if (S <= hm){
            return S * tienGoc * thueSuatTrongHanMuc_DatO;
        }
        else if (S <= 3 * hm){
            double thueTrongHanMuc = hm * thueSuatTrongHanMuc_DatO;
            double thueVuotHanMuc = (S - hm) * thueSuatVuot3LanHanMuc_DatO
            return tienGoc * (thueTrongHanMuc + thueVuotHanMuc);
        }

     }

     //Đa hình
     virtual double tinhDienTich() const = 0;
     virtual double tinhChuVi() const = 0;
     virtual string getTenHinh() const = 0;

     double thuePhaiNop() const {
        if (daSoHuu == True) return 0;
        return tinhThue() * (1.0 - mienGiamTheoDoiTuong / 100.0);
     }

     void keKhaiChuSoHuu(){
        cin.ignore();
        cout << CYAN << endl << "--- KÊ KHAI HỒ SƠ CHO LÔ ĐẤT [" << soToSoThua << " - " << getTenHinh() << "] ---" << endl << RESET;
        cout << "Thông tin lô đất: " << endl
        cout << "1. Diện tích: " << fixed << setprecision(2) << tinhDienTich() << " m2" << endl;
        cout << "2. Khu vực: " << getKhuVuc() << endl;
        cout << "3. Vị trí mặt tiền: " << getViTriMatTien() << endl;

        cout << "Nhập họ và tên chủ sở hữu: ";
        getline(cin, ChuSoHuu);
        while (1){
            cout << "Chọn mục đích sử dụng đất (1: Đất ở, 2: Đất kinh doanh, 3: Đất lấn chiếm): ";
            cin >> loaiDat;
            if (loaiDat >= 1 && loaiDat <= 3) break;
            cout << RED << "Lựa chọn không hợp lệ! Vui lòng thử lại."
        }
        daSoHuu = true;
     }

     virtual void themLoDatMoi(){
        cin.ignore();
        cout << "Nhập mã số tờ và số thửa mới (VD: T001-01): ";
        getline(cin, soToSoThua);
        cin >> khuVuc;
        while (khuVuc < 1 || khuVuc > 3){
            cout << "Nhập khu vực (1: Trung tâm, 2: Ngoại ô, 3: Nông thôn): ";
            cin >> khuVuc;
        }
        cin >> viTriMatTien;
        while (viTriMatTien < 1 || viTriMatTien > 3){
            cout << "Nhập vị trí mặt tiền (1: Mặt tiền lớn, 2: Hẻm ô tô, 3: Hẻm nhỏ): ";
            cin >> viTriMatTien;
        }
     }
     if (khuVuc == 1) giDatNhaNuoc = giaDatNhaNuoc_TrungTam;
     else if (khuVuc == 2) giaDatNhaNuoc = giaDatNhaNuoc_NgoaiO;
     else giaDatNhaNuoc = giaDatNhaNuoc_NongThon;
     cout << "-> Hệ thống tự động áp Bảng giá đất Nhà nước theo khu vực " << RED << khuVuc << RESET << ": " << fixed << setprecision(0) << giaDatNhaNuoc << " VND/m2" << endl;  
};

class HinhChuNhat : public HinhHoc {
protected:
    double dai, rong;
public:
    HinhChuNhat(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _dai = 0, double _rong = 0)
        : HinhHoc(_soToSoThua, _khuVuc, _loaiDat, _viTriMatTien), dai(_dai), rong(_rong) {}

    double tinhDienTich() const override {
        return dai * rong;
    }

    double tinhChuVi() const override {
        return 2 * (dai + rong);
    }

    string getTenHinh() const override {
        return "Hình chữ nhật";
    }
};

class HinhVuong : public HinhHoc {
private:
    double canh;
public:
    HinhVuong(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _canh = 0)
        : HinhHoc(_soToSoThua, _khuVuc, _loaiDat, _viTriMatTien), canh(_canh) {}

    double tinhDienTich() const override {
        return canh * canh;
    }

    double tinhChuVi() const override {
        return 4.0 * canh;
    }

    string getTenHinh() const override {
        return "Hình vuông";
    }
};

class TamGiac : public HinhHoc {
private:
    double a, b, c;
public:
    TamGiac(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _a = 0, double _b = 0, double _c = 0)
        : HinhHoc(_soToSoThua, _khuVuc, _loaiDat, _viTriMatTien), a(_a), b(_b), c(_c) {}

    double tinhDienTich() const override {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    double tinhChuVi() const override {
        return a + b + c;
    }

    string getTenHinh() const override {
        return "Tam giác";
    }
};

class HinhTron : public HinhHoc {
private:
    double banKinh;
public:
    HinhTron(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1, double _banKinh = 0)
        : HinhHoc(_soToSoThua, _khuVuc, _loaiDat, _viTriMatTien), banKinh(_banKinh) {}
    double tinhDienTich() const override {
        return PI * banKinh * banKinh;
    }

    double tinhChuVi() const override {
        return 2.0 * PI * banKinh;
    }

    string getTenHinh() const override {
        return "Hình tròn";
    }
};

void khaiThue(hinhHoc *a[], int n){
    int stt;
    cout << "Nhập số thứ tự ô đất muốn khai thuế (1 -" << n << ", nhập 0 để huỷ): ";
    cin >> stt;
    if (stt < 0 || stt > n){
        cout << RED << "Số thứ tự không hợp lệ! Vui lòng thử lại." << RESET << endl;
        KhaiThue(a, n);
    }
    if (ds[stt - 1]->)
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HinhHoc *ds[100];
    int n = 0, choice;
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
                break;
            case 2:
                break;
            case 3:
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
                n++;
                cout << GREEN << "Thêm ô đất mới thành công! (Trạng thái: Chưa có chủ)" << RESET << endl;
                break;
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
