#include <iostream>
#include <cmath>
#include <type_traits>

// Шаблонный класс для арифметики на основе логарифмической системы счисления
template<typename B = double>
class log_num_sys {
    static_assert(std::is_floating_point<B>::value || std::is_integral<B>::value,
                  "Base type must be a floating-point or fixed-point type");

private:
    B log_value; // Логарифм значения

public:
    // Конструктор по умолчанию (логарифм от 1 = 0)
    log_num_sys() : log_value(0) {}

    // Конструктор из обычного числа
    explicit log_num_sys(B value) {
        if (value <= 0) {
            throw std::invalid_argument("Value must be positive for logarithmic representation.");
        }
        log_value = std::log(value);
    }

    // Получение значения в стандартной форме
    B to_value() const {
        return std::exp(log_value);
    }

    // Операция умножения (сложение логарифмов)
    log_num_sys operator*(const log_num_sys& other) const {
        return log_num_sys::from_log(log_value + other.log_value);
    }

    // Операция деления (вычитание логарифмов)
    log_num_sys operator/(const log_num_sys& other) const {
        return log_num_sys::from_log(log_value - other.log_value);
    }

    // Операция возведения в степень
    log_num_sys pow(B exponent) const {
        return log_num_sys::from_log(log_value * exponent);
    }

    // Операция сложения (через преобразование значений)
    log_num_sys operator+(const log_num_sys& other) const {
        B sum_value = to_value() + other.to_value();
        return log_num_sys(sum_value);
    }

    // Операция вычитания (через преобразование значений)
    log_num_sys operator-(const log_num_sys& other) const {
        B diff_value = to_value() - other.to_value();
        if (diff_value <= 0) {
            throw std::invalid_argument("Resulting value must be positive for logarithmic representation.");
        }
        return log_num_sys(diff_value);
    }

    // Оператор сравнения на равенство
    bool operator==(const log_num_sys& other) const {
        return log_value == other.log_value;
    }

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const log_num_sys& num) {
        os << "Value: " << num.to_value() << " (Log: " << num.log_value << ")";
        return os;
    }

private:
    // Внутренний конструктор для создания из логарифма
    static log_num_sys from_log(B log_val) {
        log_num_sys num;
        num.log_value = log_val;
        return num;
    }
};

// Пример использования
int main() {
    using LogNum = log_num_sys<>; // Используем double по умолчанию

    LogNum a(10.0); // Представление числа 10
    LogNum b(2.0);  // Представление числа 2

    auto product = a * b;    // Умножение
    auto quotient = a / b;   // Деление
    auto sum = a + b;        // Сложение
    auto diff = a - b;       // Вычитание
    auto power = a.pow(3);   // Возведение в степень

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "a * b: " << product << "\n";
    std::cout << "a / b: " << quotient << "\n";
    std::cout << "a + b: " << sum << "\n";
    std::cout << "a - b: " << diff << "\n";
    std::cout << "a^3: " << power << "\n";

    return 0;
}
