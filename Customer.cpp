#include "User.h"
#include "Customer.h"
#include "Product.h"
#include "Order.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

Customer::Customer()
    : User()
{
    setRole(Role::CUSTOMER);
    setChucVu(Position::NONE);
}

Customer::Customer(int id, string userCode, string userName, string passWord,
                   string hoTen, string soDienThoai, string diaChi)
    : User(id, userCode, userName, passWord, Role::CUSTOMER,
           hoTen, Position::NONE, soDienThoai, diaChi)
{
}

void Customer::dangKy()
{
    string userName;
    string passWord;
    string hoTen;
    string soDienThoai;
    string diaChi;

    cout << "\n========== DANG KY CUSTOMER ==========" << endl;

    cout << "Username: ";
    do
    {
        cin >> userName;

        if (!validUserName(userName))
        {
            cout << "Username khong hop le! Nhap lai: ";
        }
        else if (User::taiKhoanDaTonTai(userName))
        {
            cout << "Username da ton tai! Nhap lai: ";
        }
        else
        {
            break;
        }
    }
    while (true);

    cout << "Password: ";
    do
    {
        cin >> passWord;
    }
    while (!validpassword(passWord));

    cin.ignore();

    cout << "Ho ten: ";
    do
    {
        getline(cin, hoTen);
    }
    while (!validName(hoTen));

    cout << "So dien thoai: ";
    do
    {
        cin >> soDienThoai;
    }
    while (!validPhone(soDienThoai));

    cin.ignore();

    cout << "Dia chi: ";
    getline(cin, diaChi);

    int idMoi = User::capIdMoi();
    string maMoi = User::capMaMoi(Role::CUSTOMER);

    Customer* customer = new Customer(idMoi, maMoi, userName,
                                       passWord, hoTen,
                                       soDienThoai, diaChi);

    User::themUser(customer);
    User::ghiFile();

    cout << "\nDang ky thanh cong!" << endl;

}

void Customer::khachVangLai()
{
    Cart gioHang;

    int tiepTuc = 1;

    while (tiepTuc == 1)
    {
        int productId;
        int soLuong;

        cout << "\nNhap ID san pham: ";
        cin >> productId;

        cout << "Nhap so luong: ";
        cin >> soLuong;

        if (gioHang.themSanPham(productId, soLuong))
        {
            cout << "Them san pham thanh cong!" << endl;
        }

        cout << "Tiep tuc mua san pham?" << endl;
        cout << "1. Co" << endl;
        cout << "2. Khong" << endl;
        cout << "Nhap lua chon: ";
        cin >> tiepTuc;
    }

    if (gioHang.rong())
    {
        cout << "Khong co san pham de mua!" << endl;
        return;
    }

    string nguoiNhan;
    string soDienThoaiNhan;
    string diaChiNhan;

    cin.ignore();

    cout << "\n===== THONG TIN NHAN HANG =====" << endl;

    cout << "Ho ten nguoi nhan: ";
    do
    {
        getline(cin, nguoiNhan);
    }
    while (!validName(nguoiNhan));

    cout << "So dien thoai: ";
    do
    {
        getline(cin, soDienThoaiNhan);
    }
    while (!validPhone(soDienThoaiNhan));

    cout << "Dia chi: ";
    getline(cin, diaChiNhan);

    time_t now = time(0);
    tm* localTime = localtime(&now);

    stringstream ngay;
    ngay << setfill('0') << setw(2) << localTime->tm_mday << "/";
    ngay << setfill('0') << setw(2) << localTime->tm_mon + 1 << "/";
    ngay << localTime->tm_year + 1900;

    int orderId = Order::capIdMoi();
    double tongTien = gioHang.tinhTongTien();

    Order* order = new Order(orderId, ngay.str(), "KHACH_VANG_LAI",
                             nguoiNhan, soDienThoaiNhan,
                             diaChiNhan, tongTien);

    vector<CartItem>& items = gioHang.getDanhSachItem();

    for (int i = 0; i < (int)items.size(); i++)
    {
        CartItem item = items[i];
        order->themSanPham(item);

        Product* product = Product::timTheoId(item.getProductId());
        product->setSoLuong(product->getSoLuong() - item.getSoLuong());
    }

    Order::themDonHang(order);
    Product::ghiFile();
    Order::ghiFile();
    gioHang.xoaGioHang();

    cout << "\nDat mua thanh cong!" << endl;
    cout << "Ma don hang: " << orderId << endl;
    cout << "Tong tien: " << fixed << setprecision(2)
         << tongTien << endl;
}

void Customer::xemDanhSachSanPham()
{
    vector<Product*>& danhSach = Product::getDanhSachSanPham();

    if (danhSach.size() == 0)
    {
        cout << "Danh sach san pham dang rong!" << endl;
        return;
    }

    cout << "\n========== DANH SACH SAN PHAM ==========" << endl;

    for (int i = 0; i < (int)danhSach.size(); i++)
    {
        cout << "\n-----------------------------" << endl;
        danhSach[i]->hienThi();
    }
}

void Customer::themVaoGioHang()
{
    xemDanhSachSanPham();

    int productId;
    int soLuong;

    cout << "\nNhap ID san pham muon mua: ";
    cin >> productId;

    cout << "Nhap so luong: ";
    cin >> soLuong;

    if (gioHang.themSanPham(productId, soLuong))
    {
        cout << "Them vao gio hang thanh cong!" << endl;
    }
}

void Customer::xemGioHang()
{
    gioHang.hienThi();
}

void Customer::datMua()
{
    if (gioHang.rong())
    {
        xemDanhSachSanPham();

        cout << "\nBan chua co gio hang. Nhap san pham de dat mua." << endl;

        int tiepTuc = 1;

        while (tiepTuc == 1)
        {
            int productId;
            int soLuong;

            cout << "Nhap ID san pham: ";
            cin >> productId;

            cout << "Nhap so luong: ";
            cin >> soLuong;

            if (gioHang.themSanPham(productId, soLuong))
            {
                cout << "Them san pham thanh cong!" << endl;
            }

            cout << "Tiep tuc them san pham?" << endl;
            cout << "1. Co" << endl;
            cout << "2. Khong" << endl;
            cout << "Nhap lua chon: ";
            cin >> tiepTuc;
        }
    }

    if (gioHang.rong())
    {
        cout << "Khong co san pham de dat mua!" << endl;
        return;
    }

    vector<CartItem>& item = gioHang.getDanhSachItem();

    for (int i = 0; i < (int)item.size(); i++)
    {
        Product* product = Product::timTheoId(item[i].getProductId());

        if (product == NULL)
        {
            cout << "San pham khong con ton tai!" << endl;
            return;
        }

        if (item[i].getSoLuong() > product->getSoLuong())
        {
            cout << "San pham " << product->getTenSanPham()
                 << " khong du ton kho!" << endl;
            return;
        }
    }

    string nguoiNhan;
    string soDienThoaiNhan;
    string diaChiNhan;

    cin.ignore();

    cout << "\n===== THONG TIN NHAN HANG =====" << endl;

    cout << "Ho ten nguoi nhan: ";
    do
    {
        getline(cin, nguoiNhan);
    }
    while (!validName(nguoiNhan));

    cout << "So dien thoai: ";
    do
    {
        getline(cin, soDienThoaiNhan);
    }
    while (!validPhone(soDienThoaiNhan));

    cout << "Dia chi: ";
    getline(cin, diaChiNhan);

    time_t now = time(0);
    tm* localTime = localtime(&now);

    stringstream ngay;
    ngay << setfill('0') << setw(2) << localTime->tm_mday << "/";
    ngay << setfill('0') << setw(2) << localTime->tm_mon + 1 << "/";
    ngay << localTime->tm_year + 1900;

    string taiKhoanKhach = getUserName();

    int orderId = Order::capIdMoi();
    double tongTien = gioHang.tinhTongTien();

    Order* order = new Order(orderId, ngay.str(), taiKhoanKhach,
                             nguoiNhan, soDienThoaiNhan,
                             diaChiNhan, tongTien);

    for (int i = 0; i < (int)item.size(); i++)
    {
        CartItem itemDonHang(item[i].getProductId(),
                             item[i].getTenSanPham(),
                             item[i].getSoLuong(),
                             item[i].getDonGia());

        order->themSanPham(itemDonHang);

        Product* product = Product::timTheoId(item[i].getProductId());
        product->setSoLuong(product->getSoLuong() - item[i].getSoLuong());
    }

    Order::themDonHang(order);
    Product::ghiFile();
    Order::ghiFile();

    gioHang.xoaGioHang();

    cout << "\n===== DAT HANG THANH CONG =====" << endl;
    cout << "Ma don hang: " << orderId << endl;
    cout << "Tong tien: " << fixed << setprecision(2) << tongTien << endl;
}

void Customer::xemDonHangCuaToi()
{
    vector<Order*>& danhSach = Order::getDanhSachDonHang();
    bool coDonHang = false;

    cout << "\n========== DON HANG CUA TOI ==========" << endl;

    for (int i = 0; i < (int)danhSach.size(); i++)
    {
        if (danhSach[i]->getTaiKhoanKhach() == getUserName())
        {
            danhSach[i]->hienThi();
            coDonHang = true;
        }
    }

    if (!coDonHang)
    {
        cout << "Ban chua co don hang nao!" << endl;
    }
}
