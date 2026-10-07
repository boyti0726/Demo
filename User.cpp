#include "User.h"
#include "Admin.h"
#include "Staff.h"
#include "Customer.h"
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

vector<User*> User::danhSachUser;
int User::nextId = 1;
int User::nextMaSo = 1;

User::User()
{
    id = 0;
    maNguoiDung = "";
    userName = "";
    passWord = "";
    role = Role::CUSTOMER;
    hoTen = "";
    chucVu = Position::NONE;
    soDienThoai = "";
    diaChi = "";
}

User::User(int id,
           string maNguoiDung,
           string userName,
           string passWord,
           Role role,
           string hoTen,
           Position chucVu,
           string soDienThoai,
           string diaChi)
{
    this->id = id;
    this->maNguoiDung = maNguoiDung;
    this->userName = userName;
    this->passWord = passWord;
    this->role = role;
    this->hoTen = hoTen;
    this->chucVu = chucVu;
    this->soDienThoai = soDienThoai;
    this->diaChi = diaChi;
}

User::~User()
{
}

int User::getId() { return id; }
string User::getMaNguoiDung() { return maNguoiDung; }
string User::getUserName() { return userName; }
string User::getPassWord() { return passWord; }
Role User::getRole() { return role; }
string User::getHoTen() { return hoTen; }
Position User::getChucVu() { return chucVu; }
string User::getSoDienThoai() { return soDienThoai; }
string User::getDiaChi() { return diaChi; }

void User::setId(int id) { this->id = id; }
void User::setMaNguoiDung(string userCode) { this->maNguoiDung = userCode; }
void User::setUserName(string userName) { this->userName = userName; }
void User::setPassWord(string passWord) { this->passWord = passWord; }
void User::setRole(Role role) { this->role = role; }
void User::setHoTen(string hoTen) { this->hoTen = hoTen; }
void User::setChucVu(Position chucVu) { this->chucVu = chucVu; }
void User::setSoDienThoai(string soDienThoai) { this->soDienThoai = soDienThoai; }
void User::setDiaChi(string diaChi) { this->diaChi = diaChi; }

vector<User*>& User::getDanhSachUser()
{
    return danhSachUser;
}

User* User::timTheoId(int id)
{
    for (int i = 0; i < (int)danhSachUser.size(); i++)
    {
        if (danhSachUser[i]->getId() == id)
        {
            return danhSachUser[i];
        }
    }
    return NULL;
}

User* User::timTheoTaiKhoan(string userName)
{
    for (int i = 0; i < (int)danhSachUser.size(); i++)
    {
        if (danhSachUser[i]->getUserName() == userName)
        {
            return danhSachUser[i];
        }
    }
    return NULL;
}

bool User::taiKhoanDaTonTai(string userName)
{
    if (timTheoTaiKhoan(userName) != NULL)
    {
        return true;
    }
    return false;
}

int User::capIdMoi()
{
    int idMoi = nextId;
    nextId++;
    return idMoi;
}

string User::capMaMoi(Role role)
{
    string phanDau = "customer";

    if (role == Role::ADMIN)
    {
        phanDau = "admin";
    }
    else if (role == Role::STAFF)
    {
        phanDau = "staff";
    }

    stringstream ss;
    ss << phanDau << setw(6) << setfill('0') << nextMaSo;
    nextMaSo++;
    return ss.str();
}

void User::themUser(User* user)
{
    if (user != NULL)
    {
        danhSachUser.push_back(user);
    }
}

bool User::xoaUser(int id)
{
    for (int i = 0; i < (int)danhSachUser.size(); i++)
    {
        if (danhSachUser[i]->getId() == id)
        {
            delete danhSachUser[i];
            danhSachUser.erase(danhSachUser.begin() + i);
            return true;
        }
    }
    return false;
}

string User::roleToString(Role role)
{
    if (role == Role::ADMIN) return "ADMIN";
    if (role == Role::STAFF) return "STAFF";
    return "CUSTOMER";
}

Role User::stringToRole(string role)
{
    if (role == "ADMIN") return Role::ADMIN;
    if (role == "STAFF") return Role::STAFF;
    return Role::CUSTOMER;
}

string User::positionToString(Position position)
{
    if (position == Position::GIAMDOC) return "GIAMDOC";
    if (position == Position::NHANVIEN) return "NHANVIEN";
    return "NONE";
}

Position User::stringToPosition(string position)
{
    if (position == "GIAMDOC") return Position::GIAMDOC;
    if (position == "NHANVIEN") return Position::NHANVIEN;
    return Position::NONE;
}

void User::ghiFile()
{
    ofstream file("users.txt", ios::trunc);

    if (!file.is_open())
    {
        cout << "Khong the mo file users.txt!" << endl;
        return;
    }

    for (int i = 0; i < (int)danhSachUser.size(); i++)
    {
        User* user = danhSachUser[i];

        file << user->getId() << "|";
        file << user->getMaNguoiDung() << "|";
        file << user->getUserName() << "|";
        file << user->getPassWord() << "|";
        file << roleToString(user->getRole()) << "|";
        file << user->getHoTen() << "|";
        file << positionToString(user->getChucVu()) << "|";
        file << user->getSoDienThoai() << "|";
        file << user->getDiaChi() << endl;
    }

    file.close();
}

void User::docFile()
{
    ifstream file("users.txt");

    if (!file.is_open())
    {
        return;
    }

    string line;
    int maxId = 0;
    int maxMaSo = 0;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        string idText;
        string maNguoiDung;
        string userName;
        string passWord;
        string roleText;
        string hoTen;
        string positionText;
        string soDienThoai;
        string diaChi;

        getline(ss, idText, '|');
        getline(ss, maNguoiDung, '|');
        getline(ss, userName, '|');
        getline(ss, passWord, '|');
        getline(ss, roleText, '|');
        getline(ss, hoTen, '|');
        getline(ss, positionText, '|');
        getline(ss, soDienThoai, '|');
        getline(ss, diaChi);

        if (idText.empty() || userName.empty()) continue;

        int id = stoi(idText);
        Role role = stringToRole(roleText);
        Position position = stringToPosition(positionText);

        User* user = NULL;

        if (role == Role::ADMIN)
        {
            user = new Admin(id, maNguoiDung, userName, passWord,
                             hoTen, position, soDienThoai, diaChi);
        }
        else if (role == Role::STAFF)
        {
            user = new Staff(id, maNguoiDung, userName, passWord,
                             hoTen, position, soDienThoai, diaChi);
        }
        else
        {
            user = new Customer(id, maNguoiDung, userName, passWord,
                                hoTen, soDienThoai, diaChi);
            user->setChucVu(position);
        }

        themUser(user);

        if (id > maxId)
        {
            maxId = id;
        }

        if (maNguoiDung.length() >= 6)
        {
            string phanSo = maNguoiDung.substr(maNguoiDung.length() - 6);
            bool hopLe = true;

            for (int i = 0; i < (int)phanSo.length(); i++)
            {
                if (!isdigit(phanSo[i]))
                {
                    hopLe = false;
                    break;
                }
            }

            if (hopLe)
            {
                int so = stoi(phanSo);
                if (so >= maxMaSo) maxMaSo = so;
            }
        }
    }

    file.close();

    nextId = maxId + 1;
    nextMaSo = maxMaSo + 1;
}

string typePassWord()
{
    string password = "";
    char c;

    while (true)
    {
        c = getchar();

        if (c == '\n' || c == '\r') break;

        if (c == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
            }
        }
        else
        {
            password += c;
        }
    }

    return password;
}

void User::login()
{
    string taikhoan;
    string password;

    cout << "Username: ";
    cin >> taikhoan;

    cout << "Password: ";
    cin >> password;

    if (taikhoan == userName && password == passWord)
    {
        cout << "Dang nhap thanh cong!" << endl;
    }
    else
    {
        cout << "Sai tai khoan hoac mat khau!" << endl;
    }
}

void User::logout()
{
    cout << "Dang xuat thanh cong!" << endl;
}

bool validUserName(string UserName)
{
    if (UserName.length() < 6)
    {
        cout << "Username phai co it nhat 6 ky tu!" << endl;
        return false;
    }

    if (UserName.length() > 12)
    {
        cout << "Username khong duoc qua 12 ky tu!" << endl;
        return false;
    }

    if (UserName.find(" ") != string::npos)
    {
        cout << "Username khong duoc chua dau cach!" << endl;
        return false;
    }

    for (int i = 0; i < (int)UserName.length(); i++)
    {
        if (!isalnum((unsigned char)UserName[i]))
        {
            cout << "Username chi duoc chua chu va so!" << endl;
            return false;
        }
    }

    return true;
}

bool validpassword(string PassWord)
{
    int digit = 0;
    int uppercase = 0;
    int lowercase = 0;
    int specialchar = 0;

    if (PassWord.length() >= 8)
    {
        if (PassWord.find(" ") == string::npos)
        {
            for (int i = 0; i < (int)PassWord.length(); i++)
            {
                if (isdigit((unsigned char)PassWord[i]))
                {
                    digit++;
                }
                else if (islower((unsigned char)PassWord[i]))
                {
                    lowercase++;
                }
                else if (isupper((unsigned char)PassWord[i]))
                {
                    uppercase++;
                }
                else if (ispunct((unsigned char)PassWord[i]))
                {
                    specialchar++;
                }
            }

            if (digit == 0)
            {
                cout << "Password phai co it nhat 1 chu so!" << endl;
                return false;
            }

            if (uppercase == 0)
            {
                cout << "Password phai co it nhat 1 chu hoa!" << endl;
                return false;
            }

            if (lowercase == 0)
            {
                cout << "Password phai co it nhat 1 chu thuong!" << endl;
                return false;
            }

            if (specialchar == 0)
            {
                cout << "Password phai co it nhat 1 ky tu dac biet!" << endl;
                return false;
            }

            return true;
        }

        cout << "Password khong duoc chua dau cach!" << endl;
        return false;
    }

    cout << "Password cua ban it hon 8 ky tu!" << endl;
    return false;
}

bool validName(string Name)
{
    if (Name.length() == 0)
    {
        cout << "Ho ten khong duoc de trong!" << endl;
        return false;
    }

    if (Name[0] < 'A' || Name[0] > 'Z')
    {
        cout << "Ky tu dau tien cua ho ten phai viet hoa!" << endl;
        return false;
    }

    return true;
}

bool validPhone(string Phone)
{
    if (Phone.length() == 10)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!isdigit((unsigned char)Phone[i]))
            {
                cout << "So dien thoai chi duoc chua chu so!" << endl;
                return false;
            }
        }

        return true;
    }

    cout << "So dien thoai phai co 10 chu so!" << endl;
    return false;
}
