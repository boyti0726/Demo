#include "Admin.h"
#include "User.h"
#include "Staff.h"
#include "Product.h"
#include "Order.h"

Admin::Admin()
    : User()
{
    setRole(Role::ADMIN);
}

Role chooseRole() {
    int choice;

    do {
        cout << "\n===== CHON VAI TRO =====\n";
        cout << "1. ADMIN\n";
        cout << "2. STAFF\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice != 1 && choice != 2) {
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        return Role::ADMIN;
    }

    return Role::STAFF;
}
Position choosePosition() {
    int choice;
    do {
        cout << "\n===== CHON CHUC VU =====\n";
        cout << "1. GIAMDOC\n";
        cout << "2. NHANVIEN\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        if (choice != 1 && choice != 2) {
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        return Position::GIAMDOC;
    }

    return Position::NHANVIEN;
}
void Admin::themNguoiDung()
{
    string userName;
    string passWord;
    string hoTen;
    string soDienThoai;
    string diaChi;

    cout << "\n===== THEM NGUOI DUNG =====" << endl;

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

    Role vaiTro = chooseRole();

    cin.ignore();

    cout << "Ho ten: ";
    do
    {
        getline(cin, hoTen);
    }
    while (!validName(hoTen));

    Position chucVu = choosePosition();

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
    string maMoi = User::capMaMoi(vaiTro);

    User* user = NULL;

    if (vaiTro == Role::ADMIN)
    {
        user = new Admin(idMoi, maMoi, userName, passWord,
                         hoTen, chucVu, soDienThoai, diaChi);
    }
    else
    {
        user = new Staff(idMoi, maMoi, userName, passWord,
                         hoTen, chucVu, soDienThoai, diaChi);
    }

    User::themUser(user);
    User::ghiFile();

    cout << "\nThem nguoi dung thanh cong!" << endl;
    cout << "ID: " << user->getId() << endl;
    cout << "Ma user: " << user->getMaNguoiDung() << endl;
}
void Admin::xoaNguoiDung()
{
    int id;

    cout << "Nhap ID nguoi dung can xoa: ";
    cin >> id;

    if (id == this->getId())
    {
        cout << "Khong duoc xoa tai khoan Admin dang dang nhap!" << endl;
        return;
    }

    User* user = User::timTheoId(id);

    if (user == NULL)
    {
        cout << "Khong tim thay nguoi dung!" << endl;
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
        User::xoaUser(id);
        User::ghiFile();
        cout << "Xoa nguoi dung thanh cong!" << endl;
    }
    else
    {
        cout << "Da huy xoa!" << endl;
    }
}
void Admin::suaNguoiDung()
{
    int id;

    cout << "Nhap ID nguoi dung can sua: ";
    cin >> id;

    User* user = User::timTheoId(id);

    if (user == NULL)
    {
        cout << "Khong tim thay nguoi dung!" << endl;
        return;
    }

    cout << "\nNhap thong tin moi" << endl;

    string passWord;
    string hoTen;
    string soDienThoai;
    string diaChi;

    cout << "Password moi: ";
    do
    {
        cin >> passWord;
    }
    while (!validpassword(passWord));

    cin.ignore();

    cout << "Ho ten moi: ";
    do
    {
        getline(cin, hoTen);
    }
    while (!validName(hoTen));

    cout << "So dien thoai moi: ";
    do
    {
        cin >> soDienThoai;
    }
    while (!validPhone(soDienThoai));

    cin.ignore();

    cout << "Dia chi moi: ";
    getline(cin, diaChi);

    user->setPassWord(passWord);
    user->setHoTen(hoTen);
    user->setSoDienThoai(soDienThoai);
    user->setDiaChi(diaChi);

    User::ghiFile();

    cout << "Sua thong tin thanh cong!" << endl;
}
void Admin::xemDanhSachSanPham()
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
void Admin::xemDanhSachDonHang()
{
    vector<Order*>& danhSach = Order::getDanhSachDonHang();

    if (danhSach.size() == 0)
    {
        cout << "Danh sach don hang dang rong!" << endl;
        return;
    }

    cout << "\n========== DANH SACH DON HANG ==========" << endl;

    for (int i = 0; i < danhSach.size(); i++)
    {
        danhSach[i]->hienThi();
    }
}
void Admin::xemDanhSachNguoiDung()
{
    vector<User*>& danhSach = User::getDanhSachUser();

    if (danhSach.size() == 0)
    {
        cout << "Danh sach nguoi dung dang rong!" << endl;
        return;
    }

    cout << "\n========== DANH SACH NGUOI DUNG ==========" << endl;

    for (int i = 0; i < (int)danhSach.size(); i++)
    {
        User* user = danhSach[i];

        cout << "\n-----------------------------" << endl;
        cout << "ID: " << user->getId() << endl;
        cout << "Ma nguoi dung: " << user->getMaNguoiDung() << endl;
        cout << "Username: " << user->getUserName() << endl;
        cout << "Password: ********" << endl;
        cout << "Vai tro: " << User::roleToString(user->getRole()) << endl;
        cout << "Ho ten: " << user->getHoTen() << endl;
        cout << "Chuc vu: " << User::positionToString(user->getChucVu()) << endl;
        cout << "So dien thoai: " << user->getSoDienThoai() << endl;
        cout << "Dia chi: " << user->getDiaChi() << endl;
    }
}
