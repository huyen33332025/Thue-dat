#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.141592653589793;

class HinhHoc {
private:
public:
    HinhHoc(const char* ten = "Hinh Hoc") : tenHinh(ten) {}
    virtual ~HinhHoc() {}

    const char* getTenHinh() const { return tenHinh; }
    virtual double tinhChuVi() const = 0;
    virtual double tinhDienTich() const = 0;
    virtual void xuat() const = 0;
};

class HinhTron : public HinhHoc {
private:
    double banKinh;

public:
    HinhTron(double r = 1.0) : HinhHoc("Hinh Tron") {
        setBanKinh(r);
    }

    double getBanKinh() const { return banKinh; }
    void setBanKinh(double r) {
        banKinh = (r > 0) ? r : 1.0;
    }

    double tinhChuVi() const override {
        return 2 * PI * banKinh;
    }

    double tinhDienTich() const override {
        return PI * banKinh * banKinh;
    }

    void xuat() const override {
        std::cout << "[" << tenHinh << "] Ban kinh: " << banKinh
                  << " | Chu vi: " << tinhChuVi()
                  << " | Dien tich: " << tinhDienTich() << "\n";
    }
};


class HinhChuNhat : public HinhHoc {
protected:
    double chieuDai;
    double chieuRong;

public:
    HinhChuNhat(double dai = 1.0, double rong = 1.0, const char* ten = "Hinh Chu Nhat")
        : HinhHoc(ten) {
        setKichThuoc(dai, rong);
    }

    double getChieuDai() const { return chieuDai; }
    double getChieuRong() const { return chieuRong; }

    void setKichThuoc(double dai, double rong) {
        chieuDai = (dai > 0) ? dai : 1.0;
        chieuRong = (rong > 0) ? rong : 1.0;
    }

    double tinhChuVi() const override {
        return (chieuDai + chieuRong) * 2;
    }

    double tinhDienTich() const override {
        return chieuDai * chieuRong;
    }

    void xuat() const override {
        std::cout << "[" << tenHinh << "] Dai: " << chieuDai << ", Rong: " << chieuRong
                  << " | Chu vi: " << tinhChuVi()
                  << " | Dien tich: " << tinhDienTich() << "\n";
    }
};

class HinhVuong : public HinhChuNhat {
private:

public:
    HinhVuong(double canh = 1.0) : HinhChuNhat(canh, canh, "Hinh Vuong") {}

    double getCanh() const { return chieuDai; }
    void setCanh(double canh) {
        setKichThuoc(canh, canh);
    }

    void xuat() const override {
        std::cout << "[" << tenHinh << "] Canh: " << chieuDai
                  << " | Chu vi: " << tinhChuVi()
                  << " | Dien tich: " << tinhDienTich() << "\n";
    }
};


class TamGiac : public HinhHoc {
private:
    double a, b, c;

    bool kiemTraHopLe(double x, double y, double z) const {
        return (x > 0 && y > 0 && z > 0 && (x + y > z) && (x + z > y) && (y + z > x));
    }

public:
    TamGiac(double c1 = 3.0, double c2 = 4.0, double c3 = 5.0) : HinhHoc("Tam Giac") {
        setCanh(c1, c2, c3);
    }

    void setCanh(double c1, double c2, double c3) {
        if (kiemTraHopLe(c1, c2, c3)) {
            a = c1; b = c2; c = c3;
        } else {
            a = 3.0; b = 4.0; c = 5.0; // Gán mặc định bộ 3 số Pytago nếu không thỏa bất đẳng thức tam giác
        }
    }

    double tinhChuVi() const override {
        return a + b + c;
    }

    double tinhDienTich() const override {
        double p = tinhChuVi() / 2.0;
        return canBacHai(p * (p - a) * (p - b) * (p - c)); // Công thức Heron
    }

    void xuat() const override {
        std::cout << "[" << tenHinh << "] 3 canh: (" << a << ", " << b << ", " << c << ")"
                  << " | Chu vi: " << tinhChuVi()
                  << " | Dien tich: " << tinhDienTich() << "\n";
    }
};
