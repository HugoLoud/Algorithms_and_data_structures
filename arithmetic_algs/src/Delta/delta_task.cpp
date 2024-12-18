#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

// Класс для логарифмической системы счисления
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

// Класс Trit (троичная система: 0, 1, 2)
template<typename B = double>
class Trit {
    using LogNum = log_num_sys<B>;
    LogNum value; // Логарифмическое представление значения

public:
    // Конструктор
    Trit(int val = 0) {
        if (val < 0 || val > 2) {
            throw std::invalid_argument("Trit must be 0, 1, or 2.");
        }
        value = LogNum(val == 0 ? 1 : val); // Для 0 представляем как 1 (нулевой логарифм)
    }

    // Получение значения
    int to_int() const {
        double real_value = value.to_value();
        if (real_value < 1.5) return 0;
        if (real_value < 2.5) return 1;
        return 2;
    }

    // Операторы сложения
    Trit operator+(const Trit& other) const {
        return Trit(this->to_int() + other.to_int());
    }

    // Операторы вычитания
    Trit operator-(const Trit& other) const {
        return Trit(this->to_int() - other.to_int());
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Trit& trit) {
        os << trit.to_int();
        return os;
    }
};

// Класс Tryte (тракт: набор тритов)
template<typename B = double>
class Tryte {
    using LogNum = log_num_sys<B>;
    std::vector<Trit<B>> trits; // Вектор тритов

public:
    // Конструктор по умолчанию
    Tryte(size_t size = 0) : trits(size) {}

    // Установка значения для конкретного трита
    void set(size_t index, int value) {
        if (index >= trits.size()) {
            throw std::out_of_range("Index out of range.");
        }
        trits[index] = Trit<B>(value);
    }

    // Получение значения конкретного трита
    int get(size_t index) const {
        if (index >= trits.size()) {
            throw std::out_of_range("Index out of range.");
        }
        return trits[index].to_int();
    }

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Tryte& tryte) {
        for (const auto& trit : tryte.trits) {
            os << trit << " ";
        }
        return os;
    }
};

// Пример использования
int main() {
    using LogNum = log_num_sys<>; // Используем double по умолчанию

    Trit<> t1(1);
    Trit<> t2(2);
    Trit<> t3 = t1 + t2;

    std::cout << "Trit t1: " << t1 << "\n";
    std::cout << "Trit t2: " << t2 << "\n";
    std::cout << "Trit t1 + t2: " << t3 << "\n";

    Tryte<> tryte(5);
    tryte.set(0, 1);
    tryte.set(1, 2);
    tryte.set(2, 0);

    std::cout << "Tryte: " << tryte << "\n";

    return 0;
}
