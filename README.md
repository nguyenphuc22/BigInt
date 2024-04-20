# BigInt

## **Mục Tiêu:** 

Đề án này nhằm mục đích cung cấp cho các thành viên trong nhóm cơ hội trải nghiệm việc triển khai các thuật toán số học sử dụng cấu trúc số nguyên lớn (bigint).

### **Phần 1: Triển khai BigInt và Các Phép Toán Cơ Bản**  
- Mô tả và triển khai cấu trúc số nguyên lớn bigint.
- Implement các phép toán cơ bản như cộng (+), trừ (-), nhân (*), chia (/), modulo (mod).
- Triển khai phép lũy thừa nhanh pow(x, m, n), tức là tính x^m mod n.
- Ngôn ngữ lập trình sử dụng: C++.

### **Phần 2: Thuật Toán Nhân Hai Số Nguyên với Độ Phức Tạp Thấp**  
- Trình bày và giải thích các thuật toán như Karatsuba và Schönhage-Strassen.
- Đánh giá nguyên lý giúp giảm độ phức tạp của các thuật toán này so với phương pháp truyền thống.

## **Hướng dẫn build source for vscode**
- cd /build
- cmake CMakeLists.txt
- make
- ./HCMUS-BigInt

## **Hướng dẫn run test case source for vscode**
- cd /build
- cmake CMakeLists.txt
- make
Tuỳ vào đang dev chức nào thì chạy một trong các code dưới này
- ./HCMUS-BigInt-Test ../../CreateTestCaseBigInt/data/add.txt Cho test case add 
- ./HCMUS-BigInt-Test ../../CreateTestCaseBigInt/data/sub.txt Cho test case sub
- ./HCMUS-BigInt-Test ../../CreateTestCaseBigInt/data/div.txt Cho test case div
- ./HCMUS-BigInt-Test ../../CreateTestCaseBigInt/data/mod.txt Cho test case mod
- ./HCMUS-BigInt-Test ../../CreateTestCaseBigInt/data/mul.txt Cho test case mul
- ./HCMUS-BigInt-Test ../../CreateTestCaseBigInt/data/pow.txt Cho test case pow
