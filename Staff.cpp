#include "Staff.h"
#include "Product.h"
#include "User.h"
#include <iostream>

using namespace std;

void Staff::themSanPham()
{
    string tenSanPham;
    string soLuongText;
    string donGiaText;

    cout << "\n===== THEM SAN PHAM =====" << endl;

    cin.ignore();

    cout << "Ten san pham: ";
    do
    {
        getline(cin, tenSanPham);
    }
    while (!validProductName(tenSanPham));

    cout << "So luong: ";

    do
    {
        cin >> soLuongText;

        if (!validSoLuong(soLuongText))
        {
            cout << "So luong phai la so nguyen khong am! Nhap lai: ";
        }
    }
    while (!validSoLuong(soLuongText));

    cout << "Don gia: ";

    do
    {
        cin >> donGiaText;

        if (!validDonGia(donGiaText))
        {
            cout << "Don gia phai la so thuc khong am! Nhap lai: ";
        }
    }
    while (!validDonGia(donGiaText));

    int id = Product::capIdMoi();
    int soLuong = stoi(soLuongText);
    double donGia = stod(donGiaText);

    Product* product = new Product(id, tenSanPham, soLuong, donGia);

    Product::themSanPham(product);
    Product::ghiFile();

    cout << "Them san pham thanh cong!" << endl;
    cout << "Ma san pham: " << id << endl;
}

void Staff::xemDanhSachSanPham()
{
    vector<Product*>& danhSach = Product::getDanhSachSanPham();

    if (danhSach.size() == 0)
    {
        cout << "Danh sach san pham dang rong!" << endl;
        return;
    }

    cout << "\n========== DANH SACH SAN PHAM ==========" << endl;

    for (int i = 0; i < danhSach.size(); i++)
    {
        cout << "\n-----------------------------" << endl;
        danhSach[i]->hienThi();
    }
}

void Staff::suaSanPham()
{
    int id;

    cout << "Nhap ID san pham can sua: ";
    cin >> id;

    Product* product = Product::timTheoId(id);

    if (product == NULL)
    {
        cout << "Khong tim thay san pham!" << endl;
        return;
    }

    string tenSanPham;
    string soLuongText;
    string donGiaText;

    cin.ignore();

    cout << "Ten san pham moi: ";
    do
    {
        getline(cin, tenSanPham);
    }
    while (!validProductName(tenSanPham));

    cout << "So luong moi: ";
    do
    {
        cin >> soLuongText;

        if (!validSoLuong(soLuongText))
        {
            cout << "So luong phai la so nguyen khong am! Nhap lai: ";
        }
    }
    while (!validSoLuong(soLuongText));

    cout << "Don gia moi: ";
    do
    {
        cin >> donGiaText;

        if (!validDonGia(donGiaText))
        {
            cout << "Don gia phai la so thuc khong am! Nhap lai: ";
        }
    }
    while (!validDonGia(donGiaText));

    product->setTenSanPham(tenSanPham);
    product->setSoLuong(stoi(soLuongText));
    product->setDonGia(stod(donGiaText));

    Product::ghiFile();

    cout << "Sua san pham thanh cong!" << endl;
}

void Staff::xoaSanPham()
{
    int id;

    cout << "Nhap ID san pham can xoa: ";
    cin >> id;

    Product* product = Product::timTheoId(id);

    if (product == NULL)
    {
        cout << "Khong tim thay san pham!" << endl;
        return;
    }

    cout << "Ban co chac chan muon xoa?" << endl;
    cout << "1. Co" << endl;
    cout << "2. Khong" << endl;
    cout << "Nhap lua chon: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        Product::xoaSanPham(id);
        cout << "Xoa san pham thanh cong!" << endl;
    }
    else
    {
        cout << "Da huy xoa!" << endl;
    }
}
