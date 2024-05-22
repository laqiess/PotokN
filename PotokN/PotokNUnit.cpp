// author: �������� �������

#include "PotokN.h"

using namespace std;
// ������� ��� ���������� ������� ���������� �������
void MatrRandom(vector<vector<int>>& matr)
{
    for (size_t i = 0; i < matr.size(); ++i)
    {
        for (size_t j = 0; j < matr[0].size(); ++j)
        {
            matr[i][j] = rand() % 2 + 1; // ��������� ���������� ����� �� 1 �� 2
        }
    }
}


// ������� ��� ������������ ���������
// ������� matr1 � matr2 - �������� ������� 
void Resultat(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int startRow, int endRow)
{
    mutex mt; // ������� ��� ������������� ������� � ����� ������

    int cols_A = matr1[0].size(); // ���������� �������� � ������� matr1
    int cols_B = matr2[0].size(); // ���������� �������� � ������� matr2

    // ���� �� ������� ���������
    for (int i = startRow; i < endRow; ++i)
    {
        // ���� �� �������� ������� B
        for (int j = 0; j < cols_B; ++j)
        {
            int sum = 0;

            // ���� ������������ ��������� ����������
            for (int k = 0; k < cols_A; ++k)
            {
                sum += pow(matr1[i][k], 2) * pow(matr2[k][j],2);
            }

            mt.lock(); // ���������� ��������
            result[i][j] = sum;
            mt.unlock(); // ������������� ��������
        }
    }
}

// ������� ��� ������ �������
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

// �������, ������������ ������ ������� � ������������� ����� ���� �����
// matr1 � matr2 - ������������� �������
void Threads(vector<vector<int>>& matr, vector<vector<int>>& matr2, vector<vector<int>>& result, int matr_size, int n_threads) {


    // ������ �� �������
    vector<thread> threads;

    // ���������� ���������� ����� �� �����
    int rowsPerThread = matr_size / n_threads;

    // ���� �� ���� �������
    for (int i = 0; i < n_threads; ++i)
    {
        // ����������� ��������� ������
        int startRow = i * rowsPerThread;

        // ����������� �������� ������
        // ���� ������� ����� ���������, �� �������� ������ ����� ����� MATR_SIZE,
        // ����� �������� ������ ����� ����� ��������� ������ ���������� ������
        int endRow = (i == n_threads - 1) ? matr_size : (i + 1) * rowsPerThread;

        cout << startRow << " " << endRow << endl;

        // ������ ����� � ��������� ��� � ������ �������
        // Resultat - ����������� �������
        threads.push_back(thread(Resultat, ref(matr), ref(matr2), ref(result), startRow, endRow));
    }

    // �������� ���������� ���� ������� (�������� ����� ������������, ���� �� ���������� ��� ��������� ������)
    for (auto& th : threads)
    {
        th.join();
    }
}