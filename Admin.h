#pragma once
#include "User.h"
#pragma once
class Admin : public User {
public:
    Admin();
    Admin(int id, string userCode, string userName, string passWord,
             string hoTen, Position chucVu,
             string soDienThoai, string diaChi)
    : User(id, userCode, userName, passWord, Role::ADMIN,
           hoTen, chucVu, soDienThoai, diaChi) {}

    void themNguoiDung();
    void xemDanhSachNguoiDung();
    void suaNguoiDung();
    void xoaNguoiDung();
    void xemDanhSachDonHang();
    void xemDanhSachSanPham();
};