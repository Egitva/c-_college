#include <iostream>
#include <Windows.h>

using namespace std;

class Employee {
private:
    int id;
    char* fullName;
    char* Position;
    float Salary;

public:
    Employee() : id(0), fullName(nullptr), Position(nullptr), Salary(0) {}

    Employee(int id, char* fullName, char* Position, float Salary) : Salary(Salary), id(id) {
        fullName = new char[strlen(fullName) + 1];
        strcpy_s(fullName, strlen(fullName) + 1, fullName);
        Position = new char[strlen(Position) + 1];
        strcpy_s(Position, strlen(Position) + 1, Position);
    }

    Employee(const Employee& other) : Salary(other.Salary), id(other.id) {
        if (other.fullName) {
            fullName = new char[strlen(other.fullName) + 1];
            strcpy_s(fullName, strlen(other.fullName) + 1, other.fullName);
        }
        else {
            fullName = nullptr;
        }
    }

    Employee(Employee&& other) noexcept : id(other.id), fullName(other.fullName), Position(other.Position), Salary(other.Salary) {
        other.id = 0;
        other.fullName = nullptr;
        other.Position = nullptr;
        other.Salary = 0;
    }

    ~Employee() {
        delete[] fullName;
        delete[] Position;
    }

    Employee& operator=(const Employee& other) {
        if (this != &other) {
            delete[] fullName;
            delete[] Position;
            Salary = other.Salary;
            id = other.id;
            if (other.fullName) {
                fullName = new char[strlen(other.fullName) + 1];
                strcpy_s(fullName, strlen(other.fullName) + 1, other.fullName);
            }
            else {
                fullName = nullptr;
            }
            if (other.Position) {
                Position = new char[strlen(other.Position) + 1];
                strcpy_s(Position, strlen(other.Position) + 1, other.Position);
            }
            else {
                Position = nullptr;
            }
        }
        return *this;
    }

    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            delete[] fullName;
            delete[] Position;
            fullName = other.fullName;
            Position = other.Position;
            id = other.id;
            Salary = other.Salary;
            other.fullName = nullptr;
            other.Position = nullptr;
            other.Salary = 0;
            other.id = 0;
        }
        return *this;
    }

    void setId(int a) {
        Salary = a;
    }

    void setFullName(const char* name) {
        delete[] fullName;
        fullName = new char[strlen(name) + 1];
        strcpy_s(fullName, strlen(name) + 1, name);
    }

    void setPosition(const char* name) {
        delete[] Position;
        Position = new char[strlen(name) + 1];
        strcpy_s(Position, strlen(name) + 1, name);
    }

    void setSalary(float a) {
        Salary = a;
    }

    int getId() const {
        return id;
    }

    const char* getFullName() const {
        return fullName;
    }

    const char* getPosition() const {
        return Position;
    }

    const float getSalary() const {
        return Salary;
    }

    void display() const {
        cout << "ФИО: " << fullName << "Должность" << Position << "Зарплата: " << Salary;
    }
};

class Company {
private:
    int number;
    Employee* employers;
    int residentCount;
    int capacity;

    void resize() {
        capacity = capacity == 0 ? 2 : capacity * 2;
        Employee* newemployers = new Employee[capacity];
        for (int i = 0; i < residentCount; ++i) {
            newemployers[i] = employers[i];
        }
        delete[] employers;
        employers = newemployers;
    }

public:
    Company() : number(0), employers(nullptr), residentCount(0), capacity(0) {}

    Company(int num) : number(num), employers(nullptr), residentCount(0), capacity(0) {}

    Company(const Company& other) : number(other.number), residentCount(other.residentCount), capacity(other.capacity) {
        if (other.employers && other.residentCount > 0) {
            employers = new Employee[other.capacity];
            for (int i = 0; i < residentCount; ++i) {
                employers[i] = other.employers[i];
            }
        }
        else {
            employers = nullptr;
        }
    }

    Company(Company&& other) noexcept
        : number(other.number), employers(other.employers), residentCount(other.residentCount), capacity(other.capacity) {
        other.number = 0;
        other.employers = nullptr;
        other.residentCount = 0;
        other.capacity = 0;
    }

    ~Company() {
        delete[] employers;
    }

    Company& operator=(const Company& other) {
        if (this != &other) {
            delete[] employers;
            number = other.number;
            residentCount = other.residentCount;
            capacity = other.capacity;
            if (other.employers && other.residentCount > 0) {
                employers = new Employee[other.capacity];
                for (int i = 0; i < residentCount; ++i) {
                    employers[i] = other.employers[i];
                }
            }
            else {
                employers = nullptr;
            }
        }
        return *this;
    }

    Company& operator=(Company&& other) noexcept {
        if (this != &other) {
            delete[] employers;
            number = other.number;
            employers = other.employers;
            residentCount = other.residentCount;
            capacity = other.capacity;
            other.number = 0;
            other.employers = nullptr;
            other.residentCount = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void setNumber(int num) {
        number = num;
    }

    int getNumber() const {
        return number;
    }

    void addResident(const Employee& Employee) {
        if (residentCount == capacity) {
            resize();
        }
        employers[residentCount++] = Employee;
    }

    void removeResident(int index) {
        if (index >= 0 && index < residentCount) {
            for (int i = index; i < residentCount - 1; ++i) {
                employers[i] = employers[i + 1];
            }
            residentCount--;
        }
    }

    void display() const {
        for (int i = 0; i < residentCount; ++i) {
            cout << "  " << i + 1 << ". ";
            cout << " Name: " << employers[i].getFullName();
            cout << " Position: " << employers[i].getPosition();
            cout << " Salary: " << employers[i].getSalary();
            cout << "\n";
        }
    }

    int getResidentCount() const {
        return residentCount;
    }

    Employee* getResident(int index) const {
        if (index >= 0 && index < residentCount) {
            return &employers[index];
        }
        return nullptr;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Company company;
    int choice;
    bool running = true;

    cout << "Программа управления сотрудниками компании\n\n";

    while (running) {
        cout << "\n МЕНЮ \n";
        cout << "1. Добавить сотрудника\n";
        cout << "2. Удалить сотрудника\n";
        cout << "3. Найти сотрудника по ФИО\n";
        cout << "4. Сортировка сотрудников по зарплате\n";
        cout << "5. Показать всех сотрудников\n";
        cout << "6. Показать количество сотрудников\n";
        cout << "0. Выйти\n\n";
        cout << "Ваш выбор: ";

        try {
            if (!(cin >> choice)) {
                throw runtime_error("Ошибка ввода: ожидалось целое число");
            }

            switch (choice) {
            case 1: {
                int id;
                float salary;
                char buffer[256];
                Employee newEmp;
                cout << "Введите ID сотрудника: ";
                if (!(cin >> id)) throw runtime_error("Ошибка ввода ID");
                newEmp.setId(id);

                cout << "Введите ФИО сотрудника: ";
                cin.ignore();
                cin.getline(buffer, sizeof(buffer));
                newEmp.setFullName(buffer);

                cout << "Введите должность: ";
                char position[256];
                cin.getline(position, sizeof(position));
                newEmp.setPosition(position);

                cout << "Введите зарплату: ";
                if (!(cin >> salary)) throw runtime_error("Ошибка ввода зарплаты");
                newEmp.setSalary(salary);

                company.addResident(newEmp);

                cout << "Сотрудник успешно добавлен!\n";
                break;
            }

            case 2: {
                if (company.getResidentCount() == 0) {
                    cout << "Список сотрудников пуст!\n";
                    break;
                }

                int index;
                cout << "Введите номер сотрудника для удаления (1-"
                    << company.getResidentCount() << "): ";
                if (!(cin >> index) || index < 1 || index > company.getResidentCount()) {
                    throw runtime_error("Неверный номер сотрудника");
                }

                company.removeResident(index - 1);
                cout << "Сотрудник удалён.\n";
                break;
            }

            case 3: {
                if (company.getResidentCount() == 0) {
                    cout << "Список сотрудников пуст!\n";
                    break;
                }

                char searchName[256];
                cout << "Введите ФИО для поиска: ";
                cin.ignore();
                cin.getline(searchName, sizeof(searchName));

                bool found = false;
                for (int i = 0; i < company.getResidentCount(); ++i) {
                    Employee* emp = company.getResident(i);
                    if (emp && strcmp(emp->getFullName(), searchName) == 0) {
                        cout << "Найден сотрудник:\n";
                        cout << "  " << (i + 1) << ". ";
                        emp->display();
                        cout << "\n";
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Сотрудник с таким ФИО не найден.\n";
                }
                break;
            }

            case 4: {
                if (company.getResidentCount() <= 1) {
                    cout << "Нечего сортировать.\n";
                    break;
                }
                for (int i = 0; i < company.getResidentCount() - 1; ++i) {
                    for (int j = 0; j < company.getResidentCount() - i - 1; ++j) {
                        Employee* a = company.getResident(j);
                        Employee* b = company.getResident(j + 1);
                        if (a && b && a->getSalary() > b->getSalary()) {
                            Employee temp = *a;
                            *a = *b;
                            *b = temp;
                        }
                    }
                }

                cout << "Сотрудники отсортированы по зарплате (по возрастанию).\n";
                break;
            }

            case 5:
                if (company.getResidentCount() == 0) {
                    cout << "Список сотрудников пуст.\n";
                }
                else {
                    company.display();
                }
                break;

            case 6:
                cout << "Всего сотрудников в компании: "
                    << company.getResidentCount() << endl;
                break;

            case 0:
                cout << "Программа завершена. До свидания!\n";
                running = false;
                break;

            default:
                cout << "Неверный выбор! Пожалуйста, выберите число от 0 до 6.\n";
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
        }
        catch (...) {
            cout << "Произошла неизвестная ошибка!\n";
            cin.clear();
        }
    }
}
