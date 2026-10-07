HUONG DAN CHAY PROJECT QUAN LY BAN HANG TREN VS CODE

1. Cai Visual Studio Code.
2. Cai extension C/C++ cua Microsoft.
3. Cai MSYS2 va UCRT64 GCC.
   Duong dan mac dinh phai co:
   C:\\msys64\\ucrt64\\bin\\g++.exe
   C:\\msys64\\ucrt64\\bin\\gdb.exe

4. Mo thu muc QLBanHang bang VS Code:
   File -> Open Folder -> QLBanHang

5. Build:
   Ctrl + Shift + B
   Chon: Build QuanLyBanHang

6. Chay:
   Nhap F5 hoac Run and Debug -> Chay QuanLyBanHang

7. Du lieu txt duoc tao tai chinh thu muc project:
   users.txt
   products.txt
   orders.txt

8. Tai khoan Admin mac dinh lan dau:
   Username: admin01
   Password: Admin@123

9. Neu build bao khong tim thay conio.h:
   Phai dung toolchain MSYS2 UCRT64, khong phai clang/mac/g++ Linux.

10. Neu muon build bang Terminal MSYS2 UCRT64, dung:
   g++ -std=c++17 -g main.cpp User.cpp Admin.cpp Staff.cpp Customer.cpp Product.cpp Cart.cpp CartItem.cpp Order.cpp -o QuanLyBanHang.exe
   .\\QuanLyBanHang.exe
