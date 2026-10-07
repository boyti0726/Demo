#pragma once

#include <string>
#include <vector>
using namespace std;

class Product
{
private:
    int id;
    string tenSanPham;
    int soLuong;
    double donGia;

    static vector<Product*> danhSachSanPham;
    static int nextId;

public:
    Product();
    Product(int id, string tenSanPham, int soLuong, double donGia);


    int getId();
    string getTenSanPham();
    int getSoLuong();
    double getDonGia();

    void setId(int id);
    void setTenSanPham(string tenSanPham);
    void setSoLuong(int soLuong);
    void setDonGia(double donGia);

    

    void hienThi();

    static vector<Product*>& getDanhSachSanPham();
    static Product* timTheoId(int id);
    static int capIdMoi();

    static void themSanPham(Product* product);
    static bool xoaSanPham(int id);

    static void docFile();
    static void ghiFile();


};
    bool validProductName(string tenSanPham);
    bool validSoLuong(string soLuong);
    bool validDonGia(string donGia);

