
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "CartItem.h"
using namespace std;

class Order
{
private:
    int id;
    string ngayDat;
    string taiKhoanKhach;
    string nguoiNhan;
    string soDienThoai;
    string diaChi;
    double tongTien;
    vector<CartItem> danhSachSanPham;

    static vector<Order*> danhSachDonHang;
    static int nextId;

public:
    Order();
    Order(int id, string ngayDat, string taiKhoanKhach,
          string nguoiNhan, string soDienThoai,
          string diaChi, double tongTien);
    ~Order();

    int getId();
    string getNgayDat();
    string getTaiKhoanKhach();
    string getNguoiNhan();
    string getSoDienThoai();
    string getDiaChi();
    double getTongTien();
    vector<CartItem>& getDanhSachSanPham();

    void themSanPham(CartItem item);
    void hienThi();

    static vector<Order*>& getDanhSachDonHang();
    static int capIdMoi();
    static void themDonHang(Order* order);
    static void docFile();
    static void ghiFile();
};

#endif // ORDER_H


