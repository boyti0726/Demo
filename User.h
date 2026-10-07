#pragma once
#include "Enums.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User
{
private:
    int id;
    string maNguoiDung;
    string userName;
    string passWord;
    Role role;
    string hoTen;
    Position chucVu;
    string soDienThoai;
    string diaChi;

    static vector<User*> danhSachUser;
    static int nextId;
    static int nextMaSo;

public:
    User();
    User(int id,
         string maNguoiDung,
         string userName,
         string passWord,
         Role role,
         string hoTen,
         Position chucVu,
         string soDienThoai,
         string diaChi);
    virtual ~User();

    int getId();
    string getMaNguoiDung();
    string getUserName();
    string getPassWord();
    Role getRole();
    string getHoTen();
    Position getChucVu();
    string getSoDienThoai();
    string getDiaChi();

    void setId(int id);
    void setMaNguoiDung(string manguoidung);
    void setUserName(string userName);
    void setPassWord(string passWord);
    void setRole(Role role);
    void setHoTen(string hoTen);
    void setChucVu(Position chucVu);
    void setSoDienThoai(string soDienThoai);
    void setDiaChi(string diaChi);

    static vector<User*>& getDanhSachUser();
    static User* timTheoId(int id);
    static User* timTheoTaiKhoan(string userName);
    static bool taiKhoanDaTonTai(string userName);

    static int capIdMoi();
    static string capMaMoi(Role role);

    static void themUser(User* user);
    static bool xoaUser(int id);
    static void docFile();
    static void ghiFile();

    static string roleToString(Role role);
    static Role stringToRole(string role);
    static string positionToString(Position position);
    static Position stringToPosition(string position);

    void login();
    void logout();
};

string typePassWord();
bool validUserName(string);
bool validpassword(string);
bool validName(string);
bool validPhone(string);
