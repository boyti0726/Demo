#include "Order.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

vector<Order*> Order::danhSachDonHang;
int Order::nextId = 1;

Order::Order()
{
    id = 0;
    ngayDat = "";
    taiKhoanKhach = "";
    nguoiNhan = "";
    soDienThoai = "";
    diaChi = "";
    tongTien = 0;
}

Order::Order(int id, string ngayDat, string taiKhoanKhach,
             string nguoiNhan, string soDienThoai,
             string diaChi, double tongTien)
{
    this->id = id;
    this->ngayDat = ngayDat;
    this->taiKhoanKhach = taiKhoanKhach;
    this->nguoiNhan = nguoiNhan;
    this->soDienThoai = soDienThoai;
    this->diaChi = diaChi;
    this->tongTien = tongTien;
}

Order::~Order()
{
}

int Order::getId() { return id; }
string Order::getNgayDat() { return ngayDat; }
string Order::getTaiKhoanKhach() { return taiKhoanKhach; }
string Order::getNguoiNhan() { return nguoiNhan; }
string Order::getSoDienThoai() { return soDienThoai; }
string Order::getDiaChi() { return diaChi; }
double Order::getTongTien() { return tongTien; }

vector<CartItem>& Order::getDanhSachSanPham()
{
    return danhSachSanPham;
}

void Order::themSanPham(CartItem item)
{
    danhSachSanPham.push_back(item);
}

void Order::hienThi()
{
    cout << "\n========== DON HANG ==========" << endl;
    cout << "Ma don hang: " << id << endl;
    cout << "Ngay dat: " << ngayDat << endl;
    cout << "Tai khoan khach: " << taiKhoanKhach << endl;
    cout << "Nguoi nhan: " << nguoiNhan << endl;
    cout << "So dien thoai: " << soDienThoai << endl;
    cout << "Dia chi: " << diaChi << endl;

    cout << "San pham:" << endl;

    for (int i = 0; i < (int)danhSachSanPham.size(); i++)
    {
        cout << "  " << i + 1 << ". "
             << danhSachSanPham[i].getTenSanPham()
             << " - SL: " << danhSachSanPham[i].getSoLuong()
             << " - Don gia: " << fixed << setprecision(2)
             << danhSachSanPham[i].getDonGia() << endl;
    }

    cout << "Tong tien: " << fixed << setprecision(2)
         << tongTien << endl;
}

vector<Order*>& Order::getDanhSachDonHang()
{
    return danhSachDonHang;
}

int Order::capIdMoi()
{
    int idMoi = nextId;
    nextId++;
    return idMoi;
}

void Order::themDonHang(Order* order)
{
    if (order != NULL)
    {
        danhSachDonHang.push_back(order);
    }
}

void Order::ghiFile()
{
    ofstream file("orders.txt", ios::trunc);

    if (!file.is_open())
    {
        cout << "Khong the mo file orders.txt!" << endl;
        return;
    }

    for (int i = 0; i < (int)danhSachDonHang.size(); i++)
    {
        Order* order = danhSachDonHang[i];

        file << order->getId() << "|";
        file << order->getNgayDat() << "|";
        file << order->getTaiKhoanKhach() << "|";
        file << order->getNguoiNhan() << "|";
        file << order->getSoDienThoai() << "|";
        file << order->getDiaChi() << "|";
        file << fixed << setprecision(2) << order->getTongTien() << "|";

        for (int j = 0; j < (int)order->getDanhSachSanPham().size(); j++)
        {
            CartItem item = order->getDanhSachSanPham()[j];

            file << item.getProductId() << "~";
            file << item.getTenSanPham() << "~";
            file << item.getSoLuong() << "~";
            file << fixed << setprecision(2) << item.getDonGia();

            if (j < (int)order->getDanhSachSanPham().size() - 1)
            {
                file << ";";
            }
        }

        file << endl;
    }

    file.close();
}

void Order::docFile()
{
    ifstream file("orders.txt");

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
        string ngayDat;
        string taiKhoanKhach;
        string nguoiNhan;
        string soDienThoai;
        string diaChi;
        string tongTienText;
        string itemText;

        getline(ss, idText, '|');
        getline(ss, ngayDat, '|');
        getline(ss, taiKhoanKhach, '|');
        getline(ss, nguoiNhan, '|');
        getline(ss, soDienThoai, '|');
        getline(ss, diaChi, '|');
        getline(ss, tongTienText, '|');
        getline(ss, itemText);

        if (idText.empty()) continue;

        int id = stoi(idText);
        double tongTien = stod(tongTienText);

        Order* order = new Order(id, ngayDat, taiKhoanKhach,
                                  nguoiNhan, soDienThoai,
                                  diaChi, tongTien);

        stringstream itemStream(itemText);
        string oneItem;

        while (getline(itemStream, oneItem, ';'))
        {
            if (oneItem.empty()) continue;

            stringstream itemData(oneItem);
            string productIdText;
            string tenSanPham;
            string soLuongText;
            string donGiaText;

            getline(itemData, productIdText, '~');
            getline(itemData, tenSanPham, '~');
            getline(itemData, soLuongText, '~');
            getline(itemData, donGiaText);

            CartItem item(stoi(productIdText),
                          tenSanPham,
                          stoi(soLuongText),
                          stod(donGiaText));

            order->themSanPham(item);
        }

        themDonHang(order);

        if (id > maxId)
        {
            maxId = id;
        }
    }

    file.close();
    nextId = maxId + 1;
}
