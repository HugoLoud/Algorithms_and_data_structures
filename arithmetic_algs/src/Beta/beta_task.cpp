#include <iostream>
#include <bitset>
#include <stdexcept>

template<typename B = int32_t, unsigned FRAC = 16>
class fixed_point {
private:
    // Маска для извлечения целой части
    static constexpr B INT_MASK = (1 << (sizeof(B) * 8 - FRAC)) - 1;
    // Маска для извлечения дробной части
    static constexpr B FRAC_MASK = (1 << FRAC) - 1;

    B data;

public:
    // Конструктор
    fixed_point(const B& value = 0) : data(value) {}

    // Оператор сложения
    fixed_point operator+(const fixed_point& other) const {
        B sum = data + other.data;
        return fixed_point((sum & INT_MASK) | (sum & FRAC_MASK));
    }

    // Оператор вычитания
    fixed_point operator-(const fixed_point& other) const {
        B diff = data - other.data;
        return fixed_point((diff & INT_MASK) | (diff & FRAC_MASK));
    }

    // Оператор умножения
    fixed_point operator*(const fixed_point& other) const {
        B product = (data * other.data) >> FRAC;
        return fixed_point(product);
    }

    // Оператор деления
    fixed_point operator/(const fixed_point& other) const {
        if (other.data == 0) {
            throw std::invalid_argument("Деление на ноль!");
        }
        B quotient = (data << FRAC) / other.data;
        return fixed_point(quotient);
    }

    friend std::ostream& operator<<(std::ostream& os, const fixed_point& num) {
        std::string resultStr = std::bitset<sizeof(B) * 8>(num.data).to_string();

        // Удаляем ведущие нули
        resultStr.erase(0, resultStr.find('1'));

        // Добавляем ноль, если строка пуста
        if (resultStr.empty()) {
            resultStr = "0";
        }

        os << resultStr;
        return os;
    }
};

int main() {
    setlocale(LC_ALL,"ru");
    // Пример использования
    fixed_point<> num1(0b1100110011001100); // Целая часть: 1100, дробная часть: 1100110011001100 (16 бит)
    fixed_point<> num2(0b1111000011110001); // Целая часть: 1111, дробная часть: 0000111100001111 (16 бит)

    // Выполним операции
    fixed_point<> sum = num1 + num2;
    fixed_point<> diff = num1 - num2;
    fixed_point<> product = num1 * num2;
    fixed_point<> quotient = num1 / num2;

    // Выведем результаты
    std::cout << "Сумма: " << sum << std::endl;
    std::cout << "Разность: " << diff << std::endl;
    std::cout << "Произведение: " << product << std::endl;
    std::cout << "Частное: " << quotient << std::endl;

    return 0;
}
