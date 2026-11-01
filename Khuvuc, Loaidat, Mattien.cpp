#include <iostream>
#include <string>
using namespace std;

class HinhHoc {
protected:
    int KhuVuc;

    int SoTo = 0;
    int SoThua = 0;
    int loaiDat = 1;
    int matTien = 1;
public:
    void NhapKhuVuc(){
        do{
            cout << "\n1. Nong thon";
            cout << "\n2. Do thi";
            cout << "\n3. Thanh pho";
            cout << "\nNhap khu vuc: ";
            cin >> KhuVuc;
            if (KhuVuc < 1 || KhuVuc > 3)
                cout << "Khu vuc khong hop le! Nhap lai. \n";
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
                cout << "So to khong hop le! Nhap lai. \n";
        }while(SoTo <= 0);
    }

    void NhapSoThua(){
        do {
            cout << "Nhap so thua: ";
            cin >> SoThua;

            if (SoThua <= 0)
                cout << "So thua khong hop le! Nhap lai. \n";
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
                cout << "Loai dat khong hop le! Nhap lai.\n";
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
       do{
        cout << "\n1. Mat tien lon - Tang 20% ";
        cout << "\n2. Hem oto - Gia binh thuong";
        cout << "\n3. Hem nho - Giam 20%";
        cout << "\n Chon loai mat tien: ";
        cin >> matTien;

        if(matTien < 1 || matTien > 3)
            cout << "Loai mat tien khong hop le! Nhap lai. \n";
       }while(matTien < 1 || matTien > 3);
    }
    string LayTenMatTien()const{
        switch(matTien){
            case 1: return "Mat tien lon";
            case 2: return "Hem oto";
            case 3: return "Hem nho";
            default: return "Chua xac dinh";

        }
    }
//Hệ số điều chỉnh theo vị trí mặt tiền
double HeSoMatTien ()const{
    switch(matTien){
        case 1: return 1.2;
        case 2: return 1.0;
        case 3: return 0.8;
        default: return 1.0;
    }
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
        cout << "\n Mat tien: " << LayTenMatTien();
    }
};

int main(){
    HinhHoc dat;
    dat.NhapThongTin();
    cout << "\n =========THÔNG TIN THỬA ĐẤT===========";
    dat.XuatThongTin();
    return 0;
}
