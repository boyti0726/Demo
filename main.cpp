
#include "User.h"
#include "Admin.h"
#include "Staff.h"
#include "Customer.h"
#include "Product.h"
#include "Order.h"

using namespace std;

void menuAdmin(Admin* admin)
{
    int choice;

    do
    {
        cout << "\n========== MENU ADMIN ==========" << endl;
        cout << "1. Them nguoi dung" << endl;
        cout << "2. Xem danh sach nguoi dung" << endl;
        cout << "3. Sua thong tin nguoi dung" << endl;
        cout << "4. Xoa thong tin nguoi dung" << endl;
        cout << "5. Xem danh sach san pham" << endl;
        cout << "6. Xem danh sach don hang" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice == 1)
        {
            admin->themNguoiDung();
        }
        else if (choice == 2)
        {
            admin->xemDanhSachNguoiDung();
        }
        else if (choice == 3)
        {
            admin->suaNguoiDung();
        }
        else if (choice == 4)
        {
            admin->xoaNguoiDung();
        }
        else if (choice == 5)
        {
            admin->xemDanhSachSanPham();
        }
        else if (choice == 6)
        {
            admin->xemDanhSachDonHang();
        }
        else if (choice == 0)
        {
            cout << "Dang xuat..." << endl;
        }
        else
        {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
    while (choice != 0);
}

void menuStaff(Staff* staff)
{
    int choice;

    do
    {
        cout << "\n========== MENU STAFF ==========" << endl;
        cout << "1. Them san pham" << endl;
        cout << "2. Xem danh sach san pham" << endl;
        cout << "3. Sua thong tin san pham" << endl;
        cout << "4. Xoa thong tin san pham" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice == 1)
        {
            staff->themSanPham();
        }
        else if (choice == 2)
        {
            staff->xemDanhSachSanPham();
        }
        else if (choice == 3)
        {
            staff->suaSanPham();
        }
        else if (choice == 4)
        {
            staff->xoaSanPham();
        }
        else if (choice == 0)
        {
            cout << "Dang xuat..." << endl;
        }
        else
        {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
    while (choice != 0);
}

void menuCustomer(Customer* customer)
{
    int choice;

    do
    {
        cout << "\n========== MENU CUSTOMER ==========" << endl;
        cout << "1. Xem danh sach san pham" << endl;
        cout << "2. Chon mua san pham" << endl;
        cout << "3. Xem gio hang" << endl;
        cout << "4. Dat mua" << endl;
        cout << "5. Xem danh sach don hang" << endl;
        cout << "0. Dang xuat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice == 1)
        {
            customer->xemDanhSachSanPham();
        }
        else if (choice == 2)
        {
            customer->themVaoGioHang();
        }
        else if (choice == 3)
        {
            customer->xemGioHang();
        }
        else if (choice == 4)
        {
            customer->datMua();
        }
        else if (choice == 5)
        {
            customer->xemDonHangCuaToi();
        }
        else if (choice == 0)
        {
            cout << "Dang xuat..." << endl;
        }
        else
        {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
    while (choice != 0);
}

void xemSanPhamKhongDangNhap()
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

int main()
{
    User::docFile();
    Product::docFile();
    Order::docFile();

    // Neu chua co tai khoan thi tao Admin mac dinh
    if (User::getDanhSachUser().size() == 0)
    {
        int id = User::capIdMoi();
        string ma = User::capMaMoi(Role::ADMIN);

        Admin* admin = new Admin(id, ma,
                                 "admin01",
                                 "Admin@123",
                                 "Administrator",
                                 Position::GIAMDOC,
                                 "0900000000",
                                 "Ha Noi");

        User::themUser(admin);
        User::ghiFile();

        cout << "Da tao tai khoan Admin mac dinh." << endl;
       
    }

    int choice;

    do
    {
        cout << "\n========== QUAN LY BAN HANG ==========" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky tai khoan Customer" << endl;
        cout << "3. Khach hang khong dang nhap" << endl;
        cout << "0. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice == 1)
        {
            string userName;
            string passWord;

            cout << "Username: ";
            cin >> userName;

            cout << "Password: ";
            cin >> passWord;

            User* user = User::timTheoTaiKhoan(userName);

            if (user == NULL)
            {
                cout << "Tai khoan khong ton tai!" << endl;
                continue;
            }

            if (user->getPassWord() != passWord)
            {
                cout << "Sai mat khau!" << endl;
                continue;
            }

            cout << "Dang nhap thanh cong!" << endl;

            if (user->getRole() == Role::ADMIN)
            {
                Admin* admin = static_cast<Admin*>(user);
                menuAdmin(admin);
            }
            else if (user->getRole() == Role::STAFF)
            {
                Staff* staff = static_cast<Staff*>(user);
                menuStaff(staff);
            }
            else
            {
                Customer* customer = static_cast<Customer*>(user);
                menuCustomer(customer);
            }
        }
        else if (choice == 2)
        {
            Customer::dangKy();
        }
        else if (choice == 3)
        {
            cout << "\n===== KHACH HANG KHONG DANG NHAP =====" << endl;
            xemSanPhamKhongDangNhap();

            int mua;
            cout << "Ban co muon mua san pham khong?" << endl;
            cout << "1. Co" << endl;
            cout << "2. Khong" << endl;
            cout << "Nhap lua chon: ";
            cin >> mua;

            if (mua == 1)
            {
                Customer::khachVangLai();
            }
        }
        else if (choice == 0)
        {
            cout << "Dang luu du lieu..." << endl;
        }
        else
        {
            cout << "Lua chon khong hop le!" << endl;
        }
    }
    while (choice != 0);

    User::ghiFile();
    Product::ghiFile();
    Order::ghiFile();

    for (int i = 0; i < User::getDanhSachUser().size(); i++)
    {
        delete User::getDanhSachUser()[i];
    }
    User::getDanhSachUser().clear();

    for (int i = 0; i < Product::getDanhSachSanPham().size(); i++)
    {
        delete Product::getDanhSachSanPham()[i];
    }
    Product::getDanhSachSanPham().clear();

    for (int i = 0; i < Order::getDanhSachDonHang().size(); i++)
    {
        delete Order::getDanhSachDonHang()[i];
    }
    Order::getDanhSachDonHang().clear();

    cout << "Da thoat chuong trinh." << endl;

    return 0;
}
