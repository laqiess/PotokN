#pragma once
// author: Ключерев Артем


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>

using namespace std;
// функция для заполнения матрицы случайными числами
void MatrRandom(vector<vector<int>>& matr);

// функция для перемножения подматриц
void Resultat(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int startRow, int endRow);
// результат перемножения записывается в матрицу result
// startRow - индекс строки, с которой начинается умножение подматриц
// endRow - индекс строки, на которой заканчивается умножение подматриц 


// Функция для вывода матрицы
void printMatr(const vector<vector<int>>& matr);


// функция, организующая работу потоков и распределение между ними задач
void Threads(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int matr_size, int n_threads);
// matr1 и matr2 - перемножаемые матрицы
// result - итоговая матрица, результат перемножения