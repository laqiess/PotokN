// PotokN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// author: Ключерев Артемий

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>
#include "PotokN.h"

using namespace std;

const int SIZE_MATR = 3; // размер матрицы
const int N_THREADS = 4; // количество потоков





int main()
{
    setlocale(LC_ALL, "Russian");

    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    // создание матриц
    vector<vector<int>> matr1(SIZE_MATR, vector<int>(SIZE_MATR));
    vector<vector<int>> matr2(SIZE_MATR, vector<int>(SIZE_MATR));
    vector<vector<int>> result(SIZE_MATR, vector<int>(SIZE_MATR));

    // Инициализация матриц matr1 и matr2 (заполнение случайными числами)
    MatrRandom(matr1);
    MatrRandom(matr2);

    // начало измерения времени
    auto startT = chrono::high_resolution_clock::now();

    Threads(matr1, matr2, result, SIZE_MATR, N_THREADS);
   

    // конец измерения времени
    auto endT = chrono::high_resolution_clock::now();

    // рассчитываем время выполнения перемножения
    auto time = chrono::duration_cast<chrono::milliseconds>(endT - startT).count();

    // Вывод результата
    cout << "Время перемножения для " << N_THREADS << " потоков: " << time << " миллисекунд" << endl;

    cout << "Start"<<endl;
    printMatr(matr1);
    cout << endl;
    printMatr(matr2);
    cout << endl;
    printMatr(result);

}

