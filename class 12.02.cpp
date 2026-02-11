// class 12.02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>
#include <cstdio>

using namespace std;

class Matrix {
private:
    int rows, cols;
    double** data;

public:
    Matrix(int r, int c) {
        if (r <= 0 || c <= 0) throw invalid_argument("Размеры матрицы должны быть положительными");
        rows = r;
        cols = c;
        data = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0.0;
            }
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new double* [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) delete[] data[i];
        delete[] data;
    }

    void SetValue(int row, int col, double value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Индексы вне границ матрицы");
        }
        data[row][col] = value;
    }

    double GetValue(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Индексы вне границ матрицы");
        }
        return data[row][col];
    }

    int GetRows() const { return rows; }
    int GetCols() const { return cols; }
};

template <typename T>
class SmartPtr {
private:
    T* ptr;

public:
    SmartPtr() : ptr(nullptr) {}
    explicit SmartPtr(T* p) : ptr(p) {}

    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;

    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    ~SmartPtr() {
        delete ptr;
    }

    T* get() const { return ptr; }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
};

class Logger {
private:
    static Logger* instance;

    Logger() {}
    ~Logger() {}

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& GetInstance() {
        if (instance == nullptr) {
            instance = new Logger();
        }
        return *instance;
    }

    void Log(const string& message) {
        cout << message << "\n";
    }

    static void DestroyInstance() {
        delete instance;
        instance = nullptr;
    }
};

Logger* Logger::instance = nullptr;

class FixedStack {
private:
    int* data;
    int capacity;
    int topIndex;

public:
    FixedStack(int cap) : capacity(cap), topIndex(-1) {
        data = new int[capacity];
    }

    FixedStack(const FixedStack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        data = new int[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            data[i] = other.data[i];
        }
    }

    ~FixedStack() {
        delete[] data;
    }

    FixedStack& operator=(const FixedStack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            topIndex = other.topIndex;
            data = new int[capacity];
            for (int i = 0; i <= topIndex; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void Push(int value) {
        if (IsFull()) throw overflow_error("Стек переполнен");
        data[++topIndex] = value;
    }

    int Pop() {
        if (IsEmpty()) throw underflow_error("Стек пуст");
        return data[topIndex--];
    }

    bool IsEmpty() const { return topIndex == -1; }
    bool IsFull() const { return topIndex == capacity - 1; }
    int Top() const { if (!IsEmpty()) return data[topIndex]; throw underflow_error("Стек пуст"); }
    int Size() const { return topIndex + 1; }
};

FixedStack ReverseStack(FixedStack s) {
    FixedStack result(s.Size());
    while (!s.IsEmpty()) {
        result.Push(s.Pop());
    }
    return result;
}

class Animal {
protected:
    string name;

public:
    Animal(const string& n) : name(n) {
        cout << "Констр. Animal: " << name << "\n";
    }

    virtual ~Animal() {
        cout << "Дестр. Animal: " << name << "\n";
    }
};

class Dog : public Animal {
private:
    string breed;

public:
    Dog(const string& n, const string& b) : Animal(n), breed(b) {
        cout << "Констр. Dog: " << name << ", порода: " << breed << "\n";
    }

    ~Dog() override {
        cout << "Дестр. Dog: " << name << ", порода: " << breed << "\n";
    }
};

class Time {
private:
    int hours;
    int minutes;

    void Normalize() {
        hours += minutes / 60;
        minutes %= 60;
        hours %= 24;
        if (minutes < 0) {
            minutes += 60;
            hours--;
        }
        if (hours < 0) hours += 24;
    }

public:
    Time() : Time(0, 0) {}

    Time(int h, int m) : hours(h), minutes(m) {
        Normalize();
    }

    Time(int totalMinutes) : Time(totalMinutes / 60, totalMinutes % 60) {}

    void Print() const {
        cout << (hours < 10 ? "0" : "") << hours << ":"
            << (minutes < 10 ? "0" : "") << minutes << "\n";
    }
};

class FileHandler {
private:
    FILE* file;

public:
    FileHandler(const char* filename, const char* mode) {
        errno_t err = fopen_s(&file, filename, mode);
        if (err != 0 || !file) {
            throw runtime_error("Не удалось открыть файл");
        }
        cout << "Файл открыт: " << filename << "\n";
    }

    ~FileHandler() {
        if (file) {
            fclose(file);
            cout << "Файл закрыт\n";
        }
    }

    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;

    void Write(const string& text) {
        if (file) {
            fprintf_s(file, "%s", text.c_str());
        }
    }
};

class ConnectionPool {
private:
    static const int POOL_SIZE = 5;
    static bool inUse[POOL_SIZE];
    int id;

    ConnectionPool(int id) : id(id) {
        cout << "Соединение " << id << " создано\n";
    }

public:
    ~ConnectionPool() {
        cout << "Соединение " << id << " освобождено\n";
    }

    ConnectionPool(const ConnectionPool&) = delete;
    ConnectionPool& operator=(const ConnectionPool&) = delete;

    static ConnectionPool* Acquire() {
        for (int i = 0; i < POOL_SIZE; ++i) {
            if (!inUse[i]) {
                inUse[i] = true;
                return new ConnectionPool(i);
            }
        }
        throw runtime_error("Нет свободных соединений");
    }

    void Release() {
        for (int i = 0; i < POOL_SIZE; ++i) {
            if (i == id) {
                inUse[i] = false;
                break;
            }
        }
        delete this;
    }

    int GetId() const { return id; }
};

bool ConnectionPool::inUse[POOL_SIZE] = { false };

class ImmutablePoint {
private:
    const int x;
    const int y;
    int id;
    static int nextID;

public:
    ImmutablePoint(int x_val, int y_val) : x(x_val), y(y_val) {
        id = nextID++;
    }

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetId() const { return id; }
};

int ImmutablePoint::nextID = 1;

class Widget {
private:
    char* label;

public:
    Widget(const char* lbl) {
        label = new char[strlen(lbl) + 1];
        strcpy_s(label, strlen(lbl) + 1, lbl);
        cout << "Констр. Widget: " << label << "\n";
    }

    Widget(const Widget& other) {
        label = new char[strlen(other.label) + 1];
        strcpy_s(label, strlen(other.label) + 1, other.label);
        cout << "Копия Widget: " << label << "\n";
    }

    ~Widget() {
        cout << "Уничтожен Widget: " << label << "\n";
        delete[] label;
    }

    Widget& operator=(const Widget& other) {
        if (this != &other) {
            delete[] label;
            label = new char[strlen(other.label) + 1];
            strcpy_s(label, strlen(other.label) + 1, other.label);
            cout << "Оператор присваивания Widget: " << label << "\n";
        }
        return *this;
    }

    const char* GetLabel() const { return label; }
};

void task11() {
    try {
        Matrix m(3, 4);
        m.SetValue(0, 0, 5.5);
        Matrix m2 = m;
        cout << "Значение: " << m2.GetValue(0, 0) << "\n";
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void task12() {
    SmartPtr<int> sp1(new int(42));
    cout << "Значение: " << *sp1 << "\n";
    SmartPtr<int> sp2 = move(sp1);
    cout << "После перемещения: " << *sp2 << "\n";
}

void task13() {
    Logger::GetInstance().Log("Запуск программы");
    Logger::GetInstance().Log("Работа с логгером");
    Logger::DestroyInstance();
}

void task14() {
    FixedStack s(5);
    s.Push(1);
    s.Push(2);
    s.Push(3);
    cout << "Верхний элемент: " << s.Top() << "\n";
    FixedStack reversed = ReverseStack(s);
    cout << "После реверса: " << reversed.Top() << "\n";
}

void task15() {
    Dog myDog("Барсик", "Дворняга");
    cout << "Собака создана\n";
}

void task16() {
    Time t1(2, 75);
    cout << "Time(2,75): ";
    t1.Print();
    Time t2(125);
    cout << "Time(125): ";
    t2.Print();
}

void task17() {
    try {
        FileHandler fh("test.txt", "w");
        fh.Write("Hello World!");
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void task18() {
    try {
        ConnectionPool* conn1 = ConnectionPool::Acquire();
        cout << "Получено соединение " << conn1->GetId() << "\n";
        ConnectionPool* conn2 = ConnectionPool::Acquire();
        cout << "Получено соединение " << conn2->GetId() << "\n";
        conn1->Release();
        cout << "Соединение освобождено\n";
        conn2->Release();
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }
}

void task19() {
    ImmutablePoint p1(10, 20);
    ImmutablePoint p2(30, 40);
    cout << "Точка " << p1.GetId() << ": (" << p1.GetX() << "," << p1.GetY() << ")\n";
    cout << "Точка " << p2.GetId() << ": (" << p2.GetX() << "," << p2.GetY() << ")\n";
}

void task20() {
    vector<Widget> vec;
    vec.reserve(5);
    vec.push_back(Widget("A"));
    vec.push_back(Widget("B"));
    vec.push_back(Widget("C"));
    vec.insert(vec.begin() + 1, Widget("D"));
    vec.erase(vec.begin());
    vec.clear();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    cout << "Выберите задачу (11-20): ";
    cin >> choice;

    if (choice == 11) task11();
    else if (choice == 12) task12();
    else if (choice == 13) task13();
    else if (choice == 14) task14();
    else if (choice == 15) task15();
    else if (choice == 16) task16();
    else if (choice == 17) task17();
    else if (choice == 18) task18();
    else if (choice == 19) task19();
    else if (choice == 20) task20();
    else cout << "Неверный выбор\n";

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
