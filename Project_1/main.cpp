#include "array_ops.h"

// Hàm chính của chương trình
int main() {
    int warning = 0; // Cờ cảnh báo
    int arr_length = 0; // Độ dài mảng
    int* arr = nullptr; // Con trỏ tới mảng chính
    if (!InputArray(arr, arr_length, "input.txt")) // Đọc mảng từ tập tin
        return 1; // Thoát nếu không thể mở tập tin

    int storage_arr_index = 0; // Chỉ số mảng lưu trữ
    int storage_arr_length = 1; // Độ dài mảng lưu trữ
    int** storage_arr = nullptr; // Con trỏ tới mảng lưu trữ

    Storage(storage_arr, storage_arr_index, storage_arr_length, arr, arr_length); // Lưu trữ trạng thái ban đầu

    string command_input; // Chuỗi nhập lệnh
    string command; // Lệnh được phân tích
    int index_1 = 0, index_2 = 0; // Các chỉ số
    while (getline(cin, command_input)) { // Đọc lệnh từ người dùng
        TokenCommand(command_input, command, index_1, index_2, arr_length, warning); // Phân tích lệnh
        if (command == "delete") { // Lệnh xóa
            Delete(arr, arr_length, index_1); // Xóa phần tử
            OutPutArray(arr, arr_length); // In mảng
            Storage(storage_arr, storage_arr_index, storage_arr_length, arr, arr_length); // Lưu trạng thái
        }
        else if (command == "insert") { // Lệnh chèn
            Insert(arr, arr_length, index_1, index_2); // Chèn phần tử
            OutPutArray(arr, arr_length); // In mảng
            Storage(storage_arr, storage_arr_index, storage_arr_length, arr, arr_length); // Lưu trạng thái
        }
        else if (command == "undo") { // Lệnh undo (hoàn tác)
            Undo(storage_arr, storage_arr_index, arr, arr_length); // Thực hiện undo
            OutPutArray(arr, arr_length); // In mảng
        }
        else if (command == "redo") { // Lệnh redo (làm lại)
            Redo(storage_arr, storage_arr_index, storage_arr_length, arr, arr_length); // Thực hiện redo
            OutPutArray(arr, arr_length); // In mảng
        }
        else if (command == "save") { // Lệnh save (lưu)
            Save(arr, arr_length, "output.txt"); // Lưu mảng vào tập tin
            OutPutArray(arr, arr_length); // In mảng
        }
        else if (command == "reset") { // Lệnh reset (đặt lại)
            Reset(storage_arr, storage_arr_index, storage_arr_length, arr, arr_length); // Thực hiện reset
        }
        else if (command == "quit") { // Lệnh thoát
            break; // Thoát khỏi vòng lặp
        }
        else { // Lệnh không hợp lệ
            if (warning != 1) {
                cout << "Command not found...\n"; // Thông báo lệnh không hợp lệ
                OutPutArray(arr, arr_length); // In mảng
            }
            else {
                OutPutArray(arr, arr_length); // In mảng nếu có cảnh báo
            }
            warning = 0; // Đặt lại cờ cảnh báo
        }
    }

    Free(storage_arr, storage_arr_index); // Giải phóng mảng lưu trữ
    delete[] arr; // Giải phóng mảng chính
    return 0; // Kết thúc chương trình
}