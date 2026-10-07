#pragma once
#include "User.h"
#pragma once
class Staff : public User {
public:
    Staff();
    Staff(int id, string maNguoiDung, string userName, string passWord,
             string hoTen, Position chucVu,
             string soDienThoai, string diaChi)
    : User(id, maNguoiDung, userName, passWord, Role::STAFF,
           hoTen, chucVu, soDienThoai, diaChi){}
    void themSanPham();
    void xemDanhSachSanPham();
    void suaSanPham();
    void xoaSanPham();
};