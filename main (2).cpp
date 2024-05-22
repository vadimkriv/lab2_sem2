#include <iostream>
#include <fstream> // Для работы с файлами

class Vector {
private:
    double* elements; // Указатель на массив элементов вектора
    int size; // Размер вектора

public:
    // Конструктор без параметров
    Vector() : elements(nullptr), size(0) {}

    // Конструктор для создания вектора из массива
    Vector(double* arr, int n) : size(n) {
        elements = new double[size]; // Выделение памяти под массив элементов вектора
        for (int i = 0; i < size; ++i) {
            elements[i] = arr[i]; // Копирование элементов из переданного массива в вектор
        }
    }

    // Конструктор копирования
    Vector(const Vector& other) : size(other.size) {
        elements = new double[size]; // Выделение памяти под новый массив элементов вектора
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i]; // Копирование элементов из другого вектора в текущий
        }
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept : elements(other.elements), size(other.size) {
        other.elements = nullptr; // Перемещение указателя на массив элементов из другого вектора
        other.size = 0; // Обнуление размера другого вектора
    }

    // Деструктор
    ~Vector() {
        delete[] elements; // Освобождение памяти, выделенной под массив элементов вектора
    }

    // Перегрузка оператора присваивания с копированием
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements; // Освобождение памяти, выделенной под текущий массив элементов вектора
            size = other.size; // Присваивание нового размера
            elements = new double[size]; // Выделение памяти под новый массив элементов
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i]; // Копирование элементов из другого вектора
            }
        }
        return *this;
    }

    // Перегрузка оператора присваивания с перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] elements; // Освобождение памяти, выделенной под текущий массив элементов вектора
            elements = other.elements; // Перемещение указателя на массив элементов
            size = other.size; // Присваивание нового размера
            other.elements = nullptr; // Обнуление указателя в другом векторе
            other.size = 0; // Обнуление размера другого вектора
        }
        return *this;
    }

    // Перегрузка оператора доступа к элементу вектора по индексу
    double& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range"); // Проверка выхода за границы вектора
        }
        return elements[index]; // Возвращение ссылки на элемент вектора по указанному индексу
    }

    // Перегрузка оператора вставки в поток вывода
    friend std::ostream& operator<<(std::ostream& out, const Vector& vec) {
        out << "(";
        for (int i = 0; i < vec.size; ++i) {
            out << vec.elements[i]; // Вывод элементов вектора через запятую
            if (i < vec.size - 1) {
                out << ", ";
            }
        }
        out << ")";
        return out;
    }

    // Перегрузка оператора извлечения из потока ввода
    friend std::istream& operator>>(std::istream& in, Vector& vec) {
        for (int i = 0; i < vec.size; ++i) {
            in >> vec.elements[i]; // Ввод элементов вектора из потока
        }
        return in;
    }

    // Скалярное произведение векторов
    friend double operator*(const Vector& vec1, const Vector& vec2) {
        if (vec1.size != vec2.size) {
            throw std::invalid_argument("Vectors must be of the same size"); // Проверка размеров векторов
        }
        double result = 0;
        for (int i = 0; i < vec1.size; ++i) {
            result += vec1.elements[i] * vec2.elements[i]; // Вычисление скалярного произведения
        }
        return result;
    }
};

int main() {
    std::ifstream input("input.txt"); // Открыть файл для чтения
    std::ofstream output("output.txt"); // Открыть файл для записи

    double arr1[3], arr2[3];
    for (int i = 0; i < 3; ++i) {
        input >> arr1[i]; // Чтение данных для первого вектора из файла
    }
    for (int i = 0; i < 3; ++i) {
        input >> arr2[i]; // Чтение данных для второго вектора из файла
    }

    Vector vec1(arr1, 3); // Создание первого вектора
    Vector vec2(arr2, 3); // Создание второго вектора

    output << "Vector 1: " << vec1 << std::endl; // Вывод первого вектора в файл
    output << "Vector 2: " << vec2 << std::endl; // Вывод второго вектора в файл
    output << "Scalar product: " << (vec1 * vec2) << std::endl; // Вывод скалярного произведения векторов

    return 0;
}