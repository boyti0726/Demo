#ifndef CARTITEM_H
#define CARTITEM_H

#include <string>
using namespace std;

class CartItem
{
private:
    int productId;
    string tenSanPham;
    int soLuong;
    double donGia;

public:
    CartItem();
    CartItem(int productId, string tenSanPham, int soLuong, double donGia);

    int getProductId();
    string getTenSanPham();
    int getSoLuong();
    double getDonGia();
    double getThanhTien();

    void setSoLuong(int soLuong);
};

#endif
