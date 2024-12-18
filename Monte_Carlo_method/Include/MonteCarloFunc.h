#ifndef MONTE_CARLO_PI_H
#define MONTE_CARLO_PI_H

#include <random>
#include <thread>
#include <mutex>

extern int pointsInsideCircle;
extern std::mutex pointsMutex; // Объявление мьютекса

double generateRandomNumber(double min, double max);
void monteCarloPi(int threadID, int totalPoints);
void runMonteCarloThreads(int totalPoints, int numThreads);

#endif // MONTE_CARLO_PI_H
