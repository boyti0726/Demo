#pragma once
#include "User.h"
#include "Cart.h"

class Customer : public User
{
private:
    Cart gioHang;

public:
    Customer();
    Customer(int id, string userCode, string userName, string passWord,
             string hoTen, string soDienThoai, string diaChi);

    static void dangKy();
    static void khachVangLai();

    void xemDanhSachSanPham();
    void themVaoGioHang();
    void xemGioHang();
    void datMua();
    void xemDonHangCuaToi();
};