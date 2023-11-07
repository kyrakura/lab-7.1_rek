#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

const int ROWS = 8;//кількість рядків
const int COLS = 5;// кількість стовбців

// створення випадкової матриці
void Generate(int matrix[ROWS][COLS], int min, int max, int i = 0, int j = 0) {
    if (i == ROWS) {
        return;
    }

    matrix[i][j] = rand() % (max - min + 1) + min;

    if (j == COLS - 1) {
        Generate(matrix, min, max, i + 1, 0);
    }
    else {
        Generate(matrix, min, max, i, j + 1);
    }
}

// виведення матриці
void Print(const int matrix[ROWS][COLS], int i = 0, int j = 0) {
    if (i == ROWS) {
        return;
    }

    cout << matrix[i][j] << '\t';

    if (j == COLS - 1) {
        cout << endl;
        Print(matrix, i + 1, 0);
    }
    else {
        Print(matrix, i, j + 1);
    }
}

// обчислення кількості та суми елементів, які задовольняють критерію
void Apply(int matrix[ROWS][COLS], int& count, int& sum, int i = 0, int j = 0) {
    if (i == ROWS) {
        return;
    }

    if (matrix[i][j] < 0 && matrix[i][j] % 4 != 0) {
        count++;
        sum += matrix[i][j];
        matrix[i][j] = 0;
    }

    if (j == COLS - 1) {
        Apply(matrix, count, sum, i + 1, 0);
    }
    else {
        Apply(matrix, count, sum, i, j + 1);
    }
}

//перевіряє і обмінює рядки матриці
void SwapRows(int matrix[ROWS][COLS], const int sorting[3], int i, int j, int k = 0) {
    if (k < 3) {
        return;
    }
        if (matrix[i][sorting[k]] > matrix[j][sorting[k]]) {
            for (int col = 0; col < COLS; ++col) {
                swap(matrix[i][col], matrix[j][col]);
            }
        }
        else if (matrix[i][sorting[k]] == matrix[j][sorting[k]]) {
            SwapRows(matrix, sorting, i, j, k + 1);
        }
        else {
            SwapRows(matrix, sorting, i, j, k + 1);
        }
    }

// сортування матриці
void Sort(int matrix[ROWS][COLS], const int sorting[3], int i = 0) {
    if (i == ROWS - 1) {
        return;
    }

    for (int j = i + 1; j < ROWS; ++j) {
        SwapRows(matrix, sorting, i, j);
    }

    Sort(matrix, sorting, i + 1);
}

// сортування матриці за вказаними ключами
void Sort2(int matrix[ROWS][COLS], int i = 0) {
    if (i == COLS) {
        return;
    }

    for (int j = 0; j < ROWS - 1; ++j) {
        for (int k = 0; k < ROWS - j - 1; ++k) {
            if (matrix[k][i] > matrix[k + 1][i]) {
                for (int l = 0; l < COLS; ++l) {
                    swap(matrix[k][l], matrix[k + 1][l]);
                }
            }
            else if (matrix[k][i] == matrix[k + 1][i]) {
                Sort2(matrix, i + 1);
            }
        }
    }

    Sort2(matrix, i + 1);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int matrix[ROWS][COLS];
    int min = -17;
    int max = 14;

    srand(time(nullptr));
    Generate(matrix, min, max);

    cout << "Початкова матриця: " << endl;
    Print(matrix);

    int count = 0, sum = 0;
    Apply(matrix, count, sum);
    cout << "Кількість елементів, що відповідають критерію: " << count << endl;
    cout << "Загальна сума елементів, що відповідають критерію: " << sum << endl;

    int sorting[3] = { 0, 1, 2 };
    Sort(matrix, sorting);

    cout << "Матриця після сортування(1):" << endl;
    Print(matrix);

    Sort2(matrix);

    cout << "Матриця після сортування(2):" << endl;
    Print(matrix);

    return 0;
}
