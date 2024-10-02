#include "array_ops.h"
void OutPutArray(int* arr, int arr_length) {
    // In ra các phần tử của mảng
    for (int i = 0; i < arr_length; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n> "; // In ra prompt cho người dùng
}
bool InputArray(int*& arr, int& arr_length, string file_name) {
    ifstream file(file_name); // Mở tập tin để đọc
    int count = 0;
    if (file.is_open()) {
        int num = 0;
        // Đếm số phần tử trong tập tin
        while (file >> num) {
            count++;
        }
        // Tạo mảng mới có kích thước bằng số phần tử trong tập tin
        int* temp = new int[count];
        file.clear(); // Đặt lại trạng thái của tập tin
        file.seekg(0, ios::beg); // Quay lại đầu tập tin
        while (file >> num) {
            // Đọc giá trị và thêm vào mảng
            temp[arr_length++] = num;
        }
        arr = temp; // Gán mảng mới cho biến arr
        OutPutArray(arr, arr_length); // In ra mảng
        file.close(); // Đóng tập tin
        return true;
    }
    else {
        cout << "Can't open the file !"; // Thông báo lỗi nếu không thể mở tập tin
        return false;
    }
}
void Storage(int**& storage_arr, int& storage_arr_index, int& storage_arr_length, int* arr, int arr_length) {
    // Tạo mảng mới để lưu các trạng thái cũ
    int** arr_temp = new int* [storage_arr_index + 1];

    // Sao chép dữ liệu cũ vào mảng tạm thời
    if (storage_arr != nullptr && storage_arr_index > 0) {
        memmove(arr_temp, storage_arr, storage_arr_index * sizeof(int*));
    }

    // Tạo mảng mới với phần tử đầu là độ dài mảng
    int* temp = new int[arr_length + 1];
    temp[0] = arr_length;

    // Sao chép các giá trị từ mảng chính vào mảng mới
    for (int i = 0; i < arr_length; ++i) {
        temp[i + 1] = arr[i];
    }

    // Gán mảng mới cho mảng tạm thời
    arr_temp[storage_arr_index] = temp;
    delete[] storage_arr; // Xóa mảng cũ
    storage_arr = arr_temp; // Gán mảng tạm thời cho storage_arr
    storage_arr_index++; // Tăng chỉ số index của storage_arr
    storage_arr_length = storage_arr_index; // Cập nhật độ dài storage_arr
}
void Free(int**& storage_arr, int& storage_arr_index) {
    if (storage_arr == nullptr) // Kiểm tra nếu storage_arr đã bị giải phóng
        return;

    // Giải phóng các mảng con
    for (int i = 0; i < storage_arr_index; ++i) {
        delete[] storage_arr[i];
    }
    delete[] storage_arr; // Giải phóng mảng chính
    storage_arr = nullptr;  // Đặt lại con trỏ
}
void InvalidInputWarning(const string& message, int& warning) {
    warning = 1;
    cout << message << "\n";
}

// Hàm phân tích lệnh
void TokenCommand(const string& command_input, string& command, int& index_1, int& index_2, int arr_length, int& warning) {
    istringstream stream(command_input);
    string part;
    int part_count = 0;

    command = "";
    index_1 = 0;
    index_2 = 0;

    while (stream >> part) {
        if (part.find_first_of(".,") != string::npos) {
            InvalidInputWarning("Invalid characters in index.", warning);
            command = "";
            return;
        }

        if (part_count == 0) {
            command = part;
        }
        else if (part_count == 1) {
            index_1 = stoi(part);
        }
        else if (part_count == 2) {
            index_2 = stoi(part);
        }

        part_count++;
    }

    if (part_count > 3) {
        InvalidInputWarning("Too many parts in command.", warning);
        command = "";
        return;
    }

    // Kiểm tra các chỉ số trong phạm vi hợp lệ
    if ((command == "delete" || command == "insert") && (index_1 < 1 || index_1 > arr_length)) {
        InvalidInputWarning("Invalid position input.", warning);
        command = "";
        return;
    }

    if (command == "delete" && index_2 != 0) {
        command = "";
        return;
    }

    // Kiểm tra lệnh đơn giản không có chỉ số
    if ((command == "undo" || command == "redo" || command == "save" || command == "reset") && (index_1 != 0 || index_2 != 0)) {
        command = "";
        return;
    }
}
void Delete(int*& arr, int& arr_length, int index) {
    int* temp = new int[arr_length - 1]; // Tạo mảng mới với độ dài nhỏ hơn 1
    int pos = 0; // Vị trí trong mảng mới
    index--; // Điều chỉnh index để phù hợp với 0-based index

    for (int i = 0; i < arr_length; ++i) {
        if (i == index) { // Bỏ qua phần tử cần xóa
            i++;    
        }
        temp[pos++] = arr[i]; // Sao chép phần tử vào mảng mới
    }

    delete[] arr; // Giải phóng mảng cũ
    arr = temp; // Gán mảng mới cho arr
    arr_length--; // Giảm độ dài mảng
}
void Insert(int*& arr, int& arr_length, int index_1, int index_2) {
    int* temp = new int[arr_length + 1]; // Tạo mảng mới với độ dài lớn hơn 1
    int pos = 0; // Vị trí trong mảng mới
    index_1--; // Điều chỉnh index để phù hợp với 0-based index

    for (int i = 0; i < arr_length; ++i) {
        if (i == index_1) { // Chèn phần tử tại vị trí này
            temp[pos++] = index_2; // Chèn phần tử mới
        }
        temp[pos++] = arr[i]; // Sao chép các phần tử còn lại
    }

    delete[] arr; // Giải phóng mảng cũ
    arr = temp; // Gán lại mảng
    arr_length++; // Tăng độ dài mảng
}
void Undo(int** storage_arr, int& storage_arr_index, int*& arr, int& arr_length) {
    if (storage_arr_index - 2 < 0) { // Kiểm tra chỉ số hợp lệ
        cout << "No more commands to undo...\n";
        return;
    }

    // Tạo mảng mới với độ dài từ mảng lưu trữ
    int* temp = new int[storage_arr[storage_arr_index - 2][0]];

    // Sao chép dữ liệu từ mảng lưu trữ
    memcpy(temp, &storage_arr[storage_arr_index - 2][1], storage_arr[storage_arr_index - 2][0] * sizeof(int));

    delete[] arr; // Giải phóng mảng cũ
    arr = temp; // Gán lại mảng mới
    arr_length = storage_arr[storage_arr_index - 2][0]; // Cập nhật độ dài mảng
    storage_arr_index--; // Giảm chỉ số lưu trữ
}
void Redo(int**& storage_arr, int& storage_arr_index, int storage_arr_length, int*& arr, int& arr_length) {
    if (storage_arr_index >= storage_arr_length) { // Kiểm tra chỉ số hợp lệ
        cout << "No more commands to redo...\n";
        return;
    }

    int new_arr_length = storage_arr[storage_arr_index][0]; // Lấy độ dài mảng mới
    int* temp = new int[new_arr_length]; // Tạo mảng mới

    // Sao chép dữ liệu từ mảng lưu trữ
    memcpy(temp, &storage_arr[storage_arr_index][1], new_arr_length * sizeof(int));

    delete[] arr; // Giải phóng mảng cũ
    arr = temp; // Gán lại mảng mới
    arr_length = storage_arr[storage_arr_index][0]; // Cập nhật độ dài mảng
    storage_arr_index++; // Tăng chỉ số lưu trữ
}
void Save(int* arr, int arr_length, string file_name) {
    ofstream file(file_name); // Mở tập tin để ghi
    if (file.is_open()) { // Kiểm tra tập tin mở thành công
        // Ghi các phần tử của mảng vào tập tin
        for (int i = 0; i < arr_length; ++i) {
            file << arr[i] << " ";
        }
        file.close(); // Đóng tập tin
        cout << "Numbers have been stored...\n"; // Thông báo lưu thành công
    }
    else {
        cout << "Can't open the file !"; // Thông báo lỗi nếu không thể mở tập tin
    }
}
void Reset(int**& storage_arr, int& storage_arr_index, int& storage_arr_length, int*& arr, int& arr_length) {
    arr_length = 0; // Đặt lại độ dài mảng
    delete[] arr; // Giải phóng mảng chính
    Free(storage_arr, storage_arr_index); // Giải phóng mảng lưu trữ
    storage_arr_index = 0; // Đặt lại chỉ số lưu trữ
    storage_arr_length = 1; // Đặt lại độ dài lưu trữ
    if (!InputArray(arr, arr_length, "input.txt")) // Đọc lại dữ liệu từ tập tin
        cout << "Can't open the file !"; // Thông báo lỗi nếu không thể mở tập tin
    Storage(storage_arr, storage_arr_index, storage_arr_length, arr, arr_length); // Lưu trữ trạng thái mới
}