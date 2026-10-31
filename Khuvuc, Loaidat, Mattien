#include <iostream>
#include <string>
using namespace std;

class HinhHoc {
protected:
    int KhuVuc;

    int SoTo = 0;
    int SoThua = 0;
    int loaiDat = 1;
    bool matTien = false;
public:
    void NhapKhuVuc(){
        do{
            cout << "\n1. Nong thon";
            cout << "\n2. Do thi";
            cout << "\n3. Thanh pho";
            cout << "\nNhap khu vuc: ";
            cin >> KhuVuc;
            if (KhuVuc < 1 || KhuVuc > 3)
                cout << "Khu vuc khong hop le!\n";
        }while(KhuVuc < 1 || KhuVuc > 3);
    }
    string LayTenKhuVuc()const{
        switch (KhuVuc){
            case 1: return "Nong thon";
            case 2: return "Do thi";
            case 3: return "Thanh pho";
            default: return "Chua xac dinh";
        }
    }

    void NhapSoTo(){
        do{
            cout << "Nhap so to: ";
            cin >> SoTo;

            if (SoTo <= 0)
                cout << "So to khong hop le!\n";
        }while(SoTo <= 0);
    }

    void NhapSoThua(){
        do {
            cout << "Nhap so thua: ";
            cin >> SoThua;

            if (SoThua <= 0)
                cout << "So thua khong hop le!\n";
        }while(SoThua <= 0);
    }

    void NhapLoaiDat(){
        do{
            cout << "\n1. Dat o";
            cout << "\n2. Dat san xuat kinh doanh";
            cout << "\n3. Dat lan chiem";
            cout << "\n Nhap loai dat: ";
            cin >> loaiDat;
            
            if (loaiDat < 1 || loaiDat > 3)
                cout << "Loai dat khong hop le!\n";
        }while (loaiDat < 1 || loaiDat > 3);
    }
    string LayTenLoaiDat() const{
        switch (loaiDat){
            case 1: return "Dat o";
            case 2: return "Dat san xuat kinh doanh";
            case 3: return "Dat lan chiem";
            default: return "Chua xac dinh";
        }
    }

    void NhapMatTien(){
        int chon;

        do{
            cout << "\n Dat co mat tien khong?";
            cout << "\n1. Co";
            cout << "\n0. Khong";
            cout << "\n Lua chon: ";
            cin >> chon;

            if(chon != 0 && chon != 1)
                cout << "Lua chon khong hop le! Nhap lai\n";
        }while(chon != 0 && chon != 1);

        matTien = (chon == 1);
    }

    bool CoMatTien()const{
        return matTien;
    }

    //Nhập xuất thông tin
    void NhapThongTin(){
        NhapKhuVuc();
        NhapSoTo();
        NhapSoThua();
        NhapLoaiDat();
        NhapMatTien();
    }

    void XuatThongTin() const{
        cout << "\n So to: " << SoTo;
        cout << "\n So thua: " << SoThua;
        cout << "\n Khu vuc: " << LayTenKhuVuc();
        cout << "\n Loai dat: " << LayTenLoaiDat();
        cout << "\n Mat tien: " << (matTien ? "Co" : "Khong");
    }
};

int main(){
    HinhHoc dat;
    dat.NhapThongTin();
    cout << "\n =========THÔNG TIN THỬA ĐẤT===========";
    dat.XuatThongTin();
    return 0;
}
