#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);

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

    int loaiDat;
public:
    HinhHoc(string _soToSoThua = "", int _khuVuc = 1, int _loaiDat = 1, int _viTriMatTien = 1)
        : soToSoThua(_soToSoThua), khuVuc(_khuVuc), loaiDat(_loaiDat), viTriMatTien(_viTriMatTien) {}
    virtual ~HinhHoc() {}
    
    string getSoToSoThua() const { return soToSoThua; }
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

     //Đa hình
     virtual double tinhDienTich() const = 0;
     virtual double tinhChuVi() const = 0;
     virtual string getTenHinh() const = 0;
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

int main(){
    HinhHoc *ds[100];
    int n = 0, choice;
    while (1){
        cout << CYAN << endl << string(85, '=') << endl << RESET;
        cout << CYAN < "HỆ THỐNG QUẢN LÝ QUY HOẠCH & THUẾ ĐẤT" << endl << RESET;
        cout << CYAN << string(85, '=') << endl << RESET;
        cout << "1. Xem bản đồ quy hoạch (Danh sách các ô đất có sẵn trên địa bàn)" << endl;
        cout << "2. [Người dân] Chọn ô đất có sẵn trên bản đồ để đăng ký & tính thuế" << endl;
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