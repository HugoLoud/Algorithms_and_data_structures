#include <iostream>
#include <chrono>
#include <iomanip>
#include "../Include/MonteCarloFunc.h"

const int TOTAL_POINTS = 10000000; // Общее количество случайных точек


int main() {
    setlocale(LC_ALL,"RU");
    // Измерение времени выполнения
    auto startTime = std::chrono::high_resolution_clock::now();

    int numThreads = std::thread::hardware_concurrency();
    runMonteCarloThreads(TOTAL_POINTS, numThreads);

    double pi_estimate = 4.0 * pointsInsideCircle / TOTAL_POINTS;

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Вывод результатов
    std::cout << "Предпологаемое число пи: " << std::setprecision(10) << pi_estimate << std::endl;
    std::cout << "Затраченное время: " << duration.count() << " милисекунд" << std::endl;

    return 0;
}
