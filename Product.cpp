#include "Product.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

vector<Product*> Product::danhSachSanPham;
int Product::nextId = 1;

Product::Product()
{
    id = 0;
    tenSanPham = "";
    soLuong = 0;
    donGia = 0;
}

Product::Product(int id, string tenSanPham, int soLuong, double donGia)
{
    this->id = id;
    this->tenSanPham = tenSanPham;
    this->soLuong = soLuong;
    this->donGia = donGia;
}
int Product::getId()
{
    return id;
}

string Product::getTenSanPham()
{
    return tenSanPham;
}

int Product::getSoLuong()
{
    return soLuong;
}

double Product::getDonGia()
{
    return donGia;
}

void Product::setId(int id)
{
    this->id = id;
}

void Product::setTenSanPham(string tenSanPham)
{
    this->tenSanPham = tenSanPham;
}

void Product::setSoLuong(int soLuong)
{
    this->soLuong = soLuong;
}

void Product::setDonGia(double donGia)
{
    this->donGia = donGia;
}

void Product::hienThi() 
{
    cout << "ID: " << id << endl;
    cout << "Ten san pham: " << tenSanPham << endl;
    cout << "So luong: " << soLuong << endl;
    cout << "Don gia: " << fixed << setprecision(2) << donGia << endl;
}

vector<Product*>& Product::getDanhSachSanPham()
{
    return danhSachSanPham;
}

Product* Product::timTheoId(int id)
{
    for (int i = 0; i < danhSachSanPham.size(); i++)
    {
        if (danhSachSanPham[i]->getId() == id)
        {
            return danhSachSanPham[i];
        }
    }

    return NULL;
}

int Product::capIdMoi()
{
    int idMoi = nextId;
    nextId++;
    return idMoi;
}

void Product::themSanPham(Product* product)
{
    if (product != NULL)
    {
        danhSachSanPham.push_back(product);
    }
}

bool Product::xoaSanPham(int id)
{
    for (int i = 0; i < danhSachSanPham.size(); i++)
    {
        if (danhSachSanPham[i]->getId() == id)
        {
            delete danhSachSanPham[i];
            danhSachSanPham.erase(danhSachSanPham.begin() + i);
            ghiFile();
            return true;
        }
    }

    return false;
}

void Product::docFile()
{
    ifstream file("products.txt");

    if (!file.is_open())
    {
        return;
    }

    string line;
    int maxId = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string idText;
        string tenSanPham;
        string soLuongText;
        string donGiaText;

        getline(ss, idText, '|');
        getline(ss, tenSanPham, '|');
        getline(ss, soLuongText, '|');
        getline(ss, donGiaText);

        if (idText.empty()) continue;

        int id = stoi(idText);
        int soLuong = stoi(soLuongText);
        double donGia = stod(donGiaText);

        Product* product = new Product(id, tenSanPham, soLuong, donGia);
        themSanPham(product);

        if (id > maxId)
        {
            maxId = id;
        }
    }

    file.close();
    nextId = maxId + 1;
}

void Product::ghiFile()
{
    ofstream file("products.txt", ios::trunc);

    if (!file.is_open())
    {
        cout << "Khong the mo file products.txt!" << endl;
        return;
    }

    for (int i = 0; i < danhSachSanPham.size(); i++)
    {
        Product* product = danhSachSanPham[i];

        file << product->getId() << "|";
        file << product->getTenSanPham() << "|";
        file << product->getSoLuong() << "|";
        file << fixed << setprecision(2) << product->getDonGia() << endl;
    }

    file.close();
}
bool validProductName(string tenSanPham)
{
    if (tenSanPham.length() == 0)
    {
        cout << "Ten san pham khong duoc de trong!" << endl;
        return false;
    }

    return true;
}

bool validSoLuong(string soLuong)
{
    if (soLuong.length() == 0)
    {
        return false;
    }

    for (int i = 0; i < soLuong.length(); i++)
    {
        if (!isdigit(soLuong[i]))
        {
            return false;
        }
    }

    return true;
}

bool validDonGia(string donGia)
{
    if (donGia.length() == 0)
    {
        return false;
    }

    int dauCham = 0;
    int chuSo = 0;

    for (int i = 0; i < donGia.length(); i++)
    {
        if (donGia[i] == '.')
        {
            dauCham++;

            if (dauCham > 1)
            {
                return false;
            }
        }
        else if (isdigit(donGia[i]))
        {
            chuSo++;
        }
        else
        {
            return false;
        }
    }

    if (chuSo == 0)
    {
        return false;
    }

    return true;
}
