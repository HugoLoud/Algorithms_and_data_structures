#include <iostream>
#include <chrono>
#include <thread>

size_t memsize = 32; // 32 гб
volatile int* memory = nullptr; // Глобальная переменная volatile

// Функция для чтения из памяти
void readMemory() {
    size_t num_elements = (memsize * 1024 * 1024 * 1024) / sizeof(int);
    memory = reinterpret_cast<int*>(malloc(num_elements * sizeof(int)));

    size_t step = 4 * 1024; // 4 KiB

    for (size_t i = 0; i < num_elements; i += step / sizeof(int)) {
        volatile int value = memory[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Задержка
    }

    free(const_cast<int*>(memory)); // Освобождаем выделенную память
    memory = nullptr;
}

// Функция для записи в память
void writeMemory() {
    size_t num_elements = (memsize * 1024 * 1024 * 1024) / sizeof(int);
    memory = reinterpret_cast<int*>(malloc(num_elements * sizeof(int)));

    size_t step = 4 * 1024; // 4 KiB

    for (size_t i = 0; i < num_elements; i += step / sizeof(int)) {
        const_cast<volatile int*>(memory)[i] = 0; // Записываем в память
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Задержка
    }

    free(const_cast<int*>(memory)); // Освобождаем выделенную память
    memory = nullptr;
}

int main() {
    setlocale(LC_ALL, "ru");
    char choice;
    std::cout << "Выберите режим работы (r - чтение, w - запись): ";
    std::cin >> choice;

    switch (choice) {
    case 'r':
        std::cout << "Тестирование чтения...\n";
        readMemory();
        break;
    case 'w':
        std::cout << "Тестирование записи...\n";
        writeMemory();
        break;
    default:
        std::cout << "Неправильный выбор.";
        return 1;
    }

    return 0;
}
