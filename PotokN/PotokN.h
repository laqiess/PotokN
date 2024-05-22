#pragma once
// author: �������� �����


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>

using namespace std;
// ������� ��� ���������� ������� ���������� �������
void MatrRandom(vector<vector<int>>& matr);

// ������� ��� ������������ ���������
void Resultat(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int startRow, int endRow);
// ��������� ������������ ������������ � ������� result
// startRow - ������ ������, � ������� ���������� ��������� ���������
// endRow - ������ ������, �� ������� ������������� ��������� ��������� 


// ������� ��� ������ �������
void printMatr(const vector<vector<int>>& matr);


// �������, ������������ ������ ������� � ������������� ����� ���� �����
void Threads(vector<vector<int>>& matr1, vector<vector<int>>& matr2, vector<vector<int>>& result, int matr_size, int n_threads);
// matr1 � matr2 - ������������� �������
// result - �������� �������, ��������� ������������