// SuperPoly.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

class Shape {
protected:
    string color;

public:
    Shape(const string& col = "unknown") : color(col) {}
    virtual ~Shape() {}

    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;

    string GetColor() const { return color; }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, const string& col = "red") : Shape(col), radius(r) {}

    virtual double GetArea() const override {
        return 3.14 * radius * radius;
    }

    virtual double GetPerimeter() const override {
        return 2 * 3.14 * radius;
    }

    double GetRadius() const { return radius; }
};

class Rectangled : public Shape {
private:
    double width;
    double height;

public:
    Rectangled(double w, double h, const string& col = "blue")
        : Shape(col), width(w), height(h) {
    }

    virtual double GetArea() const override {
        return width * height;
    }

    virtual double GetPerimeter() const override {
        return 2 * (width + height);
    }

    double GetWidth() const { return width; }
    double GetHeight() const { return height; }
};

class Triangle : public Shape {
private:
    double a, b, c;

public:
    Triangle(double side1, double side2, double side3, const string& col = "green")
        : Shape(col), a(side1), b(side2), c(side3) {
    }

    virtual double GetArea() const override {
        double p = GetPerimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    virtual double GetPerimeter() const override {
        return a + b + c;
    }

    bool IsValid() const {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }
};

void task1() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0, "red"));
    shapes.push_back(new Rectangled(4.0, 6.0, "blue"));
    shapes.push_back(new Triangle(3.0, 4.0, 5.0, "green"));

    double totalArea = 0.0;
    for (size_t i = 0; i < shapes.size(); ++i) {
        cout << "Фигура " << i + 1 << ": " << shapes[i]->GetColor()
            << ", площадь = " << shapes[i]->GetArea() << "\n";
        totalArea += shapes[i]->GetArea();
    }

    cout << "Общая площадь: " << totalArea << "\n\n";

    for (Shape* shape : shapes) delete shape;
}

class Sound {
public:
    virtual string ThatSound(string s) {};
};

class Dog : Sound{
private:
    string sou;
public:
    Dog(string s) : sou(s) {};
    virtual string ThatSound(string s){
        return s;
    }
};

class Cat : Sound {
private:
    string sou;
public:
    Cat(string s) : sou(s) {};
    virtual string ThatSound(string s) {
        return s;
    }
};

class Machina : Sound {
private:
    string sou;
public:
    Machina(string s) : sou(s) {};
    virtual string ThatSound(string s) {
        return s;
    }
};

class Radio : Sound {
private:
    string sou;
public:
    Radio(string s) : sou(s) {};
    virtual string ThatSound(string s) {
        return s;
    }
};
main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choose = 0;
    while (true) {
        cin >> choose;
        if (choose == 1) {
            task1();
        }
        else if (choose == 2) {
            task2();
        }
        else if (choose == 3) {
            task3();
        }
        else if (choose == 4) {
            task4();
        }
        else if (choose == 5) {
            task5();
        }
        else if (choose == 6) {
            task6();
        }
        else if (choose == 7) {
            task7();
        }
        else if (choose == 8) {
            task8();
        }
        else if (choose == 9) {
            task9();
        }
        else if (choose == 0) {
            break;
        }
        else {
            cout << "Нет такого задания\n";
        }
    }
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
