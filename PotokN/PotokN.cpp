// PotokN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

const int MATR_SIZE = 8; // размер матрицы
const int THREADS = 6; // количество потоков

mutex mtx; // мьютекс для синхронизации доступа к общей памяти


// функция для заполнения матрицы случайными числами
void MatrRandom(vector<vector<int>>& matrix)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            matrix[i][j] = rand() % 2 + 1; // генерация случайного числа от 1 до 2
        }
    }
}


// функция для перемножения подматриц
// матрицы matrixA и matrixB - исходные матрицы 
// результат перемножения записывается в матрицу result
// startRow - индекс строки, с которой начинается умножение подматриц
// endRow - индекс строки, на которой заканчивается умножение подматриц (не включительно)
void multiplyMatrices(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int startRow, int endRow)
{

    int cols_A = matr1[0].size(); // количество столбцов в матрице matrixA
    int cols_B = matr2[0].size(); // количество столбцов в матрице matrixB

    // цикл по строкам подматриц
    for (int i = startRow; i < endRow; ++i)
    {
        // Цикл по столбцам матрицы B
        for (int j = 0; j < cols_B; ++j)
        {
            int sum = 0;

            // Цикл возведение в степень элементов подматрицы
            for (int k = 0; k < cols_A; ++k)
            {               
                sum += pow(matr1[i][k] , matr2[k][j]);
            }

            mtx.lock(); // блокировка мьютекса
            result[i][j] = sum;
            mtx.unlock(); // разблокировка мьютекса
            /*Функция mtx.lock() блокирует мьютекс, 
            предотвращая доступ к общему ресурсу другим потокам,
            пока данный поток выполняет операцию записи.
            После завершения операции записи поток вызывает mtx.unlock(),
            чтобы разблокировать мьютекс и разрешить доступ другим потокам к общему ресурсу.*/
        }
    }
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix)
{
    for (const auto& row : matrix)
    {
        for (int num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}




int main()
{
    setlocale(LC_ALL, "Russian");

    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    // массив из потоков
    vector<thread> threads;

    // создание матриц
    vector<vector<int>> matr1(MATR_SIZE, vector<int>(MATR_SIZE));
    vector<vector<int>> matr2(MATR_SIZE, vector<int>(MATR_SIZE));
    vector<vector<int>> result(MATR_SIZE, vector<int>(MATR_SIZE));

    // Инициализация матриц matrixA и matrixB (заполнение случайными числами)
    MatrRandom(matr1);
    MatrRandom(matr2);

    // определяем количество строк на поток
    int rowsThread = MATR_SIZE / THREADS;

    // начало измерения времени
    auto startTime = chrono::high_resolution_clock::now();

    // цикл по всем потокам
    for (int i = 0; i < THREADS; ++i) {
        //устанавливаем начальную строку для каждого потока, учитывая номер потока и количество строк на поток.
        int startRow = i * rowsThread;

        // вычисляется конечная строка
        // если текущий поток последний, то конечная строка будет равна MATR_SIZE,
        // иначе конечная строка будет равна начальной строке следующего потока
        int endRow = (i == THREADS - 1) ? MATR_SIZE : (i + 1) * rowsThread;

        //определяем конечную строку, которая будет обработана текущим потоком.
        /*int endRow;

        //определяем кому отдать лишние строки при распределении по потокам
        if (MATR_SIZE % THREADS > i) {
            endRow = THREADS + 1;
        }
        else {
            endRow = (i + 1) * rowsThread;// противном случае устанавливаем конечную строку как начальная строка следующей группы строк для обработки текущим потоком.
        }*/

        // создаём поток и добавляем его в массив потоков
        // multiplyMatrices - выполняемая функция
        threads.push_back(thread(multiplyMatrices, ref(matr1), ref(matr2), ref(result), startRow, endRow));
    }



    // ожидание выполнения всех потоков (основной поток заблокирован, пока не выполнятся все отдельные потоки)
    for (auto& th : threads)
    {
        th.join();
    }

    cout << endl;
    printMatrix(matr1);
    cout << endl;
    printMatrix(matr2);
    cout << endl;
    printMatrix(result);

    // конец измерения времени
    auto endTime = chrono::high_resolution_clock::now();

    // рассчитываем время выполнения перемножения
    auto resultat = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    // Вывод результата
    cout << "Время вычислени для " << THREADS << " потоков: " << resultat << " миллисек" << endl;
}

