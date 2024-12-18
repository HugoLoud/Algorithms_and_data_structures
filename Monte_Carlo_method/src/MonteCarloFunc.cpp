#include "../Include/MonteCarloFunc.h"

int pointsInsideCircle = 0;
std::mutex pointsMutex; // Определение мьютекса

double generateRandomNumber(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void monteCarloPi(int threadID, int totalPoints) {
    int pointsInside = 0;
    for (int i = 0; i < totalPoints; ++i) {
        double x = generateRandomNumber(-1.0, 1.0); // Генерация случайной точки на интервале [-1, 1]
        double y = generateRandomNumber(-1.0, 1.0); // Генерация случайной точки на интервале [-1, 1]
        if (x * x + y * y <= 1.0) { // Если точка попадает в круг радиуса 1
            pointsInside++;
        }
    }
    std::lock_guard<std::mutex> guard(pointsMutex); // Блокировка мьютекса
    pointsInsideCircle += pointsInside;
}

void runMonteCarloThreads(int totalPoints, int numThreads) {
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(monteCarloPi, i, totalPoints / numThreads);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}