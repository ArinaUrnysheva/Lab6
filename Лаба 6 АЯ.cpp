#include <iostream>
#include <stdexcept>

using namespace std;

// Класс для исключения, производный от invalid_argument
class NotGP : public std::invalid_argument {
private:
    double first;
    double z;
    double* elements;
    int size;
public:
    // Конструктор исключения
    NotGP(double first, double r, double* elements, int n)
        : invalid_argument("Invalid Geometric Progression"), first(first), z(r), elements(elements), size(n) {}

    // Метод для печати данных недопустимого объекта
    void printData() {
        cout << "Invalid Geometric Progression Data:" << std::endl;
        cout << "First Element: " << first << std::endl;
        cout << "Ratio: " << z << std::endl;
        cout << "Initial Elements: ";
        for (int i = 0; i < size; ++i) {
            cout << elements[i] << " ";
        }
        cout << std::endl;
    }
};

// Класс "Массив - геометрическая прогрессия"
class GeometricProgressionArray {
private:
    double firstElement;
    double ratio;
    double* elements;
    int size;
public:
    // Конструктор для инициализации полей
    GeometricProgressionArray(double first, double r, double* initElements, int n) {
        firstElement = first;
        ratio = r;
        size = n;
        elements = new double[size];

        // Проверка, что переданный массив является геометрической прогрессией
        for (int i = 0; i < size; ++i) {
            elements[i] = firstElement * pow(ratio, i);

            if (initElements[i] != elements[i]) {
                // Бросаем исключение, если массив не является геометрической прогрессией
                throw NotGP(first, r, initElements, n);
            }
        }
    }

    // Деструктор для освобождения памяти
    ~GeometricProgressionArray() {
        delete[] elements;
    }
};

int main() {
    double initialElements1[3] = { 2, 4, 8 };
    double initialElements2[3] = { 1, 3, 5 };

    try {
        GeometricProgressionArray validArray(2, 2, initialElements1, 3);
        std::cout << "Valid Geometric Progression Array created successfully!" << std::endl;
    }
    catch (NotGP& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        ex.printData();
    }

    try {
        GeometricProgressionArray invalidArray(1, 2, initialElements2, 3);
        std::cout << "Valid Geometric Progression Array created successfully!" << std::endl;
    }
    catch (NotGP& ex) {
        std::cout << "Exception caught: " << ex.what() << std::endl;
        ex.printData();
    }

    return 0;
}