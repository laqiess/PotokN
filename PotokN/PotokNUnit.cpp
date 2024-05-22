// author: Ключерев Артемий

#include "PotokN.h"

using namespace std;
// функция для заполнения матрицы случайными числами
void MatrRandom(vector<vector<int>>& matr)
{
    for (size_t i = 0; i < matr.size(); ++i)
    {
        for (size_t j = 0; j < matr[0].size(); ++j)
        {
            matr[i][j] = rand() % 2 + 1; // генерация случайного числа от 1 до 2
        }
    }
}


// функция для перемножения подматриц
// матрицы matr1 и matr2 - исходные матрицы 
void Resultat(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int startRow, int endRow)
{
    mutex mt; // мьютекс для синхронизации доступа к общей памяти

    int cols_A = matr1[0].size(); // количество столбцов в матрице matr1
    int cols_B = matr2[0].size(); // количество столбцов в матрице matr2

    // цикл по строкам подматриц
    for (int i = startRow; i < endRow; ++i)
    {
        // Цикл по столбцам матрицы B
        for (int j = 0; j < cols_B; ++j)
        {
            int sum = 0;

            // Цикл перемножения элементов подматрицы
            for (int k = 0; k < cols_A; ++k)
            {
                sum += pow(matr1[i][k], 2) * pow(matr2[k][j],2);
            }

            mt.lock(); // блокировка мьютекса
            result[i][j] = sum;
            mt.unlock(); // разблокировка мьютекса
        }
    }
}

// Функция для вывода матрицы
void printMatr(const vector<vector<int>>& matr)
{
    for (const auto& row : matr)
    {
        for (int num : row)
        {
            cout << num << " ";
        }
        cout << endl;
    }
}

// функция, организующая работу потоков и распределение между ними задач
// matr1 и matr2 - перемножаемые матрицы
void Threads(vector<vector<int>>& matr, vector<vector<int>>& matr2, vector<vector<int>>& result, int matr_size, int n_threads) {


    // массив из потоков
    vector<thread> threads;

    // определяем количество строк на поток
    int rowsPerThread = matr_size / n_threads;

    // цикл по всем потокам
    for (int i = 0; i < n_threads; ++i)
    {
        // вычисляется начальная строка
        int startRow = i * rowsPerThread;

        // вычисляется конечная строка
        // если текущий поток последний, то конечная строка будет равна MATR_SIZE,
        // иначе конечная строка будет равна начальной строке следующего потока
        int endRow = (i == n_threads - 1) ? matr_size : (i + 1) * rowsPerThread;

        cout << startRow << " " << endRow << endl;

        // создаём поток и добавляем его в массив потоков
        // Resultat - выполняемая функция
        threads.push_back(thread(Resultat, ref(matr), ref(matr2), ref(result), startRow, endRow));
    }

    // ожидание выполнения всех потоков (основной поток заблокирован, пока не выполнятся все отдельные потоки)
    for (auto& th : threads)
    {
        th.join();
    }
}