#include <iostream>
#include <omp.h>
#include <locale.h>

using namespace std;

void GetMatr(int** mas, int** p, int i, int j, int m) {
    int ki, kj, di, dj;
    di = 0;
#pragma omp for private(ki)
    for (ki = 0; ki < m - 1; ki++) { // проверка индекса строки
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++) { // проверка индекса столбца
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}
// Рекурсивное вычисление определителя
int Determinant(int** mas, int m) {
    int i, j, d, k, n;
    int** p;
    p = new int* [m];
    for (i = 0; i < m; i++)
        p[i] = new int[m];
    j = 0; d = 0;
    k = 1; //(-1) в степени i
    n = m - 1;
    if (m < 1) cout << "Определитель вычислить невозможно!";
    if (m == 1) {
        d = mas[0][0];
        return(d);
    }
    if (m == 2) {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
        return(d);
    }
    if (m > 2) {
        for (i = 0; i < m; i++) {
            GetMatr(mas, p, i, 0, m);
            d = d + k * mas[i][0] * Determinant(p, n);
            k = -k;
        }
    }
    return(d);
}

/// функция для проверки является ли чар цифрой
bool is_digit(const char* S) {
    const char* temp = "0123456789-+";
    unsigned point_count = 0;

    for (int i = 0; i < strlen(S); i++) {
        if ((i > 0) && (S[i] == '+' || S[i] == '-')) return false;
        if (S[i] == '.') {
            point_count++;
            if (point_count > 1) return false;
        }
        if (!strchr(temp, S[i])) return false;
    }
    return true;
}

/// функция для проверки введенных данных на корректность
int CheckInput() {
    const int N = 256;
    char S[N];
    // проверяем на то что введелнное число - не строка и записываем его в переменнуб n
    cin.getline(S, N);
    while (!is_digit(S)) {
        cerr << "Неправильный ввод, попробуйте еще раз!\n";
        cin.getline(S, N);
    }
    return atof(S);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n, k;
    cout << "Введите размерность матрицы: ";
    n = CheckInput();
    while (n <= 0) {
        n = CheckInput();
        cout << "Число должно быть положительным!\n";
    }
    cout << "\nВведите количестов потоков: ";
    k = CheckInput();
    while (k <= 0) {
        cout << "Число должно быть положительным!\n";
        k = CheckInput();
    }
    int** A = new int* [n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            A[i][j] = CheckInput();
        }
    }
    omp_set_num_threads(k);
#pragma omp parallel
    cout << "Матрица, которую вы ввели: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << "Детерминант введенной матрицы = " << Determinant(A, n);

    return 0;
}
