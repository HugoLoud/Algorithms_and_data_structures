#include <iostream>
#include <vector>
#include <random>
#include <chrono>

const int size = 30000;

void generateMATRIX(const int size, std::vector<std::vector<int>>& matrix) {
	matrix.resize(size, std::vector<int>(size));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = dis(gen);
		}
	}
	//Вывод матрицы
	//std::cout << "Matrix:" << std::endl;
	//for (int i = 0; i < size; ++i) {
	//	for (int j = 0; j < size; ++j) {
	//		std::cout << matrix[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
};

void OnColumns(const std::vector<std::vector<int>>& matrix) {
	int num = 0;
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			num += matrix[j][i];
		}
	}
	std::cout<<"По столбцам " << num << std::endl;
}

void OnLines(const std::vector<std::vector<int>>& matrix) {
	int num = 0;
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			num += matrix[i][j];
		}
	}
	std::cout << "По строкам " << num << std::endl;
}


int main()
{
	setlocale(LC_ALL, "ru");

	std::vector<std::vector<int>> matrix;
	generateMATRIX(size, matrix);

	auto timeStartOnLines = std::chrono::high_resolution_clock::now();
	OnLines(matrix);
	auto timeEndOnLines = std::chrono::high_resolution_clock::now();

	auto timeStartOnColumns = std::chrono::high_resolution_clock::now();
	OnColumns(matrix);
	auto timeEndOnColumns = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> durationOnLines = timeEndOnLines - timeStartOnLines;
	std::cout << "Время, затраченное на перебор по строкам: " << durationOnLines.count() << " seconds" << std::endl;

	std::chrono::duration<double> durationOnColumns = timeEndOnColumns - timeStartOnColumns;
	std::cout << "Время, затраченное на перебор по столбцам: " << durationOnColumns.count() << " seconds" << std::endl;

	return 0;
}


