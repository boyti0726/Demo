#include "Cart.h"
#include "Product.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool Cart::rong()
{
    if (danhSachItem.size() == 0)
    {
        return true;
    }

    return false;
}

void Cart::xoaGioHang()
{
    danhSachItem.clear();
}

bool Cart::themSanPham(int productId, int soLuong)
{
    Product* product = Product::timTheoId(productId);

    if (product == NULL)
    {
        cout << "Khong tim thay san pham!" << endl;
        return false;
    }

    if (soLuong <= 0)
    {
        cout << "So luong phai lon hon 0!" << endl;
        return false;
    }

    if (soLuong > product->getSoLuong())
    {
        cout << "So luong trong kho khong du!" << endl;
        return false;
    }

    for (int i = 0; i < danhSachItem.size(); i++)
    {
        if (danhSachItem[i].getProductId() == productId)
        {
            int soLuongMoi = danhSachItem[i].getSoLuong() + soLuong;

            if (soLuongMoi > product->getSoLuong())
            {
                cout << "So luong trong gio vuot qua so luong trong kho!" << endl;
                return false;
            }

            danhSachItem[i].setSoLuong(soLuongMoi);
            return true;
        }
    }

    CartItem item(productId,
                  product->getTenSanPham(),
                  soLuong,
                  product->getDonGia());

    danhSachItem.push_back(item);

    return true;
}

void Cart::hienThi()
{
    if (rong())
    {
        cout << "Gio hang dang rong!" << endl;
        return;
    }

    double tongTien = 0;

    cout << "\n========== GIO HANG ==========" << endl;

    for (int i = 0; i < danhSachItem.size(); i++)
    {
        cout << "STT: " << i + 1 << endl;
        cout << "Ma san pham: " << danhSachItem[i].getProductId() << endl;
        cout << "Ten san pham: " << danhSachItem[i].getTenSanPham() << endl;
        cout << "So luong: " << danhSachItem[i].getSoLuong() << endl;
        cout << "Don gia: " << fixed << setprecision(2)
             << danhSachItem[i].getDonGia() << endl;
        cout << "Thanh tien: " << fixed << setprecision(2)
             << danhSachItem[i].getThanhTien() << endl;
        cout << "--------------------------" << endl;

        tongTien += danhSachItem[i].getThanhTien();
    }

    cout << "Tong tien: " << fixed << setprecision(2) << tongTien << endl;
}

double Cart::tinhTongTien()
{
    double tongTien = 0;

    for (int i = 0; i < danhSachItem.size(); i++)
    {
        tongTien += danhSachItem[i].getThanhTien();
    }

    return tongTien;
}

vector<CartItem>& Cart::getDanhSachItem()
{
    return danhSachItem;
}
