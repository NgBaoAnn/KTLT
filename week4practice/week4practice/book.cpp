//
//  book.cpp
//  week4practice
//
//  Created by Nguyễn Bảo An on 30/3/24.
//

#include "book.h"

void inputSach(book* &danhsach, int &n){
    cout << "Nhap so luong sach: ";
    cin >> n;
    if (n < 1) {
        cout << "So luong sach khong hop le!";
        return;
    }
    danhsach = new book[n];
    cin.ignore();
    cout << "Nhap danh sach...\n";
    for (int i = 0; i < n; ++i){
        cout << "Nhap sach so " << i + 1 << ":\n";
        danhsach[i].input();
    }
}
void outputSach(book* danhsach, int n) {
    cout << "Danh sach...\n";
    for (int i = 0; i < n; i++) {
        danhsach[i].output();
    }
}
void delSach(book* &danhsach, int n) {
    for (int i = 0; i < n; i++) {
        danhsach[i].del();
    }
    delete [] danhsach;
    danhsach = NULL;
}
void swapSach(book &a, book &b) {
    book temp = a;
    a = b;
    b = temp;
}
void sapxepSach(book* &danhsach, int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (danhsach[i].namxb > danhsach[j].namxb) {
                swapSach(danhsach[i], danhsach[j]);
            }
        }
    }
}
void maxCostSach(book* danhsach, int n) {
    cout << "Nhap k = ";
    int k;
    cin >> k;
    float maxCost = 0;

    for (int i = 0; i < n; i++) {
        if (danhsach[i].sotrang < k && danhsach[i].cost > maxCost){
            maxCost = danhsach[i].cost;
        }
    }
    cout << "Sach co it hon " << k << " trang va co gia ban cao nhat la:..." << endl;
    for (int i = 0; i < n; i++) {
        if (danhsach[i].cost == maxCost) {
            danhsach[i].output();
        }
    }
}
void themSach(book* &danhsach, int &n) {
    cout << "Nhap vi tri them: ";
    int index;
    cin >> index;
    if (index > n || index < 0) {
        cout << "Vi tri them khong hop le!!";
        return;
    }
    cout << "Nhap thong tin sach can them: ..." << endl;
    book subSach;
    cin.ignore();
    subSach.input();
    for(int i = n; i > index; i--){
        danhsach[i] = danhsach[i-1];
    }
    n++;
    danhsach[index] = subSach;
    
}
void xoaSach(book* &danhsach, int &n){
    cout << "Nhap nam: ";
    int nam;
    cin >> nam;
    for (int i = 0; i < n;i ++){
        if (danhsach[i].namxb < nam){
            for (int j = i; j < n - 1; j++){
                danhsach[j] = danhsach[j+1];
            }
            n--;
        }
    }
    
}



