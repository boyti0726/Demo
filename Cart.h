#pragma once
#include <vector>
#include "CartItem.h"
using namespace std;

class Cart
{
private:
    vector<CartItem> danhSachItem;

public:
    bool rong();
    void xoaGioHang();
    bool themSanPham(int productId, int soLuong);
    void hienThi();
    double tinhTongTien();
    vector<CartItem>& getDanhSachItem();
};