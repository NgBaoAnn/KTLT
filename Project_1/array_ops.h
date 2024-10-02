#ifndef ARRAY_OPS_H
#define ARRAY_OPS_H

#include <iostream> 
#include <string>   
#include <fstream> 
#include <sstream>
using namespace std;
// Khai báo các hàm sử dụng trong chương trình

// In mảng
void OutPutArray(int* arr, int arr_length);

// Đọc mảng từ tập tin
bool InputArray(int*& arr, int& arr_length, std::string file_name);

// Lưu trữ trạng thái mảng số nguyên
void Storage(int**& storage_arr, int& storage_arr_index, int& storage_arr_length, int* arr, int arr_length); 

// Giải phóng mảng lưu trữ
void Free(int**& storage_arr, int& storage_arr_index);


// Hàm thông báo lỗi
void InvalidInputWarning(const string& message, int& warning);

// Phân tích lệnh
void TokenCommand(const string& command_input, string& command, int& index_1, int& index_2, int arr_length, int& warning);

// Xóa phần tử
void Delete(int*& arr, int& arr_length, int index); 

// Chèn phần tử
void Insert(int*& arr, int& arr_length, int index_1, int index_2);

// Hoàn tác
void Undo(int** storage_arr, int& storage_arr_index, int*& arr, int& arr_length);

// Làm lại
void Redo(int**& storage_arr, int& storage_arr_index, int storage_arr_length, int*& arr, int& arr_length);

// Lưu mảng vào tập tin
void Save(int* arr, int arr_length, std::string file_name);

// Đặt lại mảng
void Reset(int**& storage_arr, int& storage_arr_index, int& storage_arr_length, int*& arr, int& arr_length);


#endif // ARRAY_OPS_H