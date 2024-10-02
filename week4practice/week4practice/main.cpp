//
//  main.cpp
//  week4practice
//
//  Created by Nguyễn Bảo An on 30/3/24.
//

#include "book.h"

int main(){
    book* ds;
    int n;
    inputSach(ds, n);
    outputSach(ds, n);
    cout << "Sap xep sach: ..." << endl;
    sapxepSach(ds, n);
    outputSach(ds, n);
    maxCostSach(ds, n);
    themSach(ds, n);
    cout << "Danh sach sau khi them: ..." << endl;
    outputSach(ds, n);
    xoaSach(ds, n);
    cout << "Danh sach sau khi xoa: ..." << endl;
    outputSach(ds, n);
    
    delSach(ds, n);
    
}

