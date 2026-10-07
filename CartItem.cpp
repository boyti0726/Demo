#include "CartItem.h"

CartItem::CartItem()
{
    productId = 0;
    tenSanPham = "";
    soLuong = 0;
    donGia = 0;
}

CartItem::CartItem(int productId, string tenSanPham, int soLuong, double donGia)
{
    this->productId = productId;
    this->tenSanPham = tenSanPham;
    this->soLuong = soLuong;
    this->donGia = donGia;
}

int CartItem::getProductId()
{
    return productId;
}

string CartItem::getTenSanPham()
{
    return tenSanPham;
}

int CartItem::getSoLuong()
{
    return soLuong;
}

double CartItem::getDonGia()
{
    return donGia;
}

double CartItem::getThanhTien()
{
    return soLuong * donGia;
}

void CartItem::setSoLuong(int soLuong)
{
    this->soLuong = soLuong;
}
