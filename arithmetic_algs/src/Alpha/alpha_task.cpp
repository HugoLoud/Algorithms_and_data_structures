#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

template<typename B>
class ones_compl_int {
private:
    B value;  // Число хранится в виде строки в двоичном представлении

public:
    // Конструктор
    ones_compl_int(const B& val = "0") : value(val) {}

    // Оператор сложения
    ones_compl_int operator+(const ones_compl_int& other) const {
        return ones_compl_int(addBinary(value, other.value));
    }

    // Оператор вычитания
    ones_compl_int operator-(const ones_compl_int& other) const {
        return ones_compl_int(subtractBinary(value, other.value));
    }

    // Оператор умножения
    ones_compl_int operator*(const ones_compl_int& other) const {
        // Простое умножение двоичных чисел
        return ones_compl_int(multiplyBinary(value, other.value));
    }

    // Оператор деления
    ones_compl_int operator/(const ones_compl_int& other) const {
        // Простое деление двоичных чисел
        return ones_compl_int(divideBinary(value, other.value));
    }

    // Оператор сравнения на равенство
    bool operator==(const ones_compl_int& other) const {
        return value == other.value;
    }

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const ones_compl_int& num) {
        os << num.value;
        return os;
    }

    // Оператор ввода из потока
    friend std::istream& operator>>(std::istream& is, ones_compl_int& num) {
        B input;
        is >> input;
        num.value = input;  // Просто считываем строку
        return is;
    }

private:
    // Вспомогательная функция для выполнения сложения двоичных чисел
    B addBinary(const B& a, const B& b) const {
        B result;
        int carry = 0;
        for (int i = a.size() - 1; i >= 0; i--) { // size_t вместо int
            int sum = (a[i] - '0') + (b[i] - '0') + carry;
            result.push_back(sum % 2 + '0');
            carry = sum / 2;
        }
        if (carry) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    // Вспомогательная функция для выполнения умножения двоичных чисел
    B multiplyBinary(const B& a, const B& b) const {
        // Преобразуем строки в целые числа в двоичной системе
        std::bitset<sizeof(B)> num1(a);
        std::bitset<sizeof(B)> num2(b);

        // Выполняем умножение
        std::bitset<sizeof(B) * 8> result = num1.to_ulong() * num2.to_ulong();

        // Преобразуем результат обратно в строку в двоичном представлении
        std::string resultStr = result.to_string();

        // Удаляем ведущие нули
        resultStr.erase(0, resultStr.find('1'));

        return resultStr;
    }

    // Вспомогательная функция для выполнения деления двоичных чисел
    B divideBinary(const B& a, const B& b) const {
        // Преобразуем строки в целые числа в двоичной системе
        std::bitset<sizeof(B) * 8> num1(a);
        std::bitset<sizeof(B) * 8> num2(b);

        // Проверяем деление на ноль
        if (num2.to_ulong() == 0) {
            throw std::invalid_argument("Деление на ноль!");
        }

        // Выполняем деление
        std::bitset<sizeof(B) * 8> result = num1.to_ulong() / num2.to_ulong();

        // Преобразуем результат обратно в строку в двоичном представлении
        std::string resultStr = result.to_string();

        // Удаляем ведущие нули
        resultStr.erase(0, resultStr.find('1'));

        return resultStr;
    }


    // Вспомогательная функция для выполнения вычитания двоичных чисел
    B subtractBinary(const B& a, const B& b) const {
        // Инвертируем все биты числа B (обратный код)
        B negB = b;
        for (char& bit : negB) {
            bit = (bit == '0') ? '1' : '0';
        }

        // Добавляем единицу к обратному коду для выполнения операции сложения
        int carry = 1;
        for (int i = negB.size() - 1; i >= 0; i--) {
            int sum = (negB[i] - '0') + carry;
            negB[i] = sum % 2 + '0';
            carry = sum / 2;
        }

        // Выполняем операцию сложения A + (-B)
        B result = addBinary(a, negB);

        // Если результат превышает размер строки, удаляем старший разряд
        if (result.size() > a.size()) {
            result.erase(0, 1);
        }

        return result;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    ones_compl_int<std::string> num1, num2;
    std::cout << "Введите первое число в двоичном виде: ";
    std::cin >> num1;

    std::cout << "Введите второе число в двоичном виде: ";
    std::cin >> num2;

    ones_compl_int<std::string> sum = num1 + num2;
    ones_compl_int<std::string> diff = num1 - num2;
    ones_compl_int<std::string> product = num1 * num2;
    ones_compl_int<std::string> quotient = num1 / num2;

    std::cout << "Сумма: " << sum << std::endl;
    std::cout << "Разность: " << diff << std::endl;
    std::cout << "Произведение: " << product << std::endl;
    std::cout << "Частное: " << quotient << std::endl;

    return 0;
}