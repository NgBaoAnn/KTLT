//
//  book.h
//  week4practice
//
//  Created by Nguyễn Bảo An on 30/3/24.
//

#ifndef book_h
#define book_h

#include <iostream>

using namespace std;

struct book {
    char* masach;
    char* tensach;
    char* tacgia;
    char* nxb;
    float cost;
    int sotrang;
    int namxb;
    void input(){
        
        cout << "Ma sach: ";
        masach = new char[7];
        cin.getline(masach, 7);
        cout << "Ten sach: ";
        tensach = new char[50];
        cin.getline(tensach, 50);
        cout << "Ten tac gia: ";
        tacgia = new char[40];
        cin.getline(tacgia, 40);
        cout << "Nha xuat ban: ";
        nxb = new char[30];
        cin.getline(nxb, 30);
        cout << "Gia ban: ";
        cin >> cost;
        cout << "So trang: ";
        cin >> sotrang;
        cout << "Nam xuat ban: ";
        cin >> namxb;
        cin.ignore();
    }
    void output(){
        cout << masach << "\t" << tensach << "\t" << tacgia << "\t" << nxb << "\t" << cost << "\t" << sotrang << "\t" << namxb << endl;
    }
    void del(){
        delete [] masach;
        delete [] tensach;
        delete [] tacgia;
        delete [] nxb;
    }
};
void inputSach(book* &danhsach, int &n);
void outputSach(book* danhsach, int n);
void delSach(book* &danhsach, int n);
void sapxepSach(book* &danhsach, int n);
void swapSach(book &a, book &b);
void maxCostSach(book* danhsach, int n);
void themSach(book* &danhsach, int &n);
void xoaSach(book* &danhsach, int &n);



#endif /* book_h */

