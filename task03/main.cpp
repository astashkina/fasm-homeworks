#include<iostream>
#include<math.h>
#include <vector>

using namespace std;

/// функция для подсчета детерминанта матрицы
int determinant( int matrix[10][10], int n) {
    int det = 0;
    int submatrix[10][10];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
        }
    }
    return det;
}

/// функция для проверки является ли чар цифрой
bool is_digit(const char *S){
    const char *temp = "0123456789-+";
    unsigned point_count = 0;

    for (int i=0; i<strlen(S); i++){
        if ((i>0) && (S[i] == '+' || S[i] == '-')) return false;
        if (S[i] == '.') {
            point_count++;
            if (point_count > 1) return false;
        }
        if (!strchr(temp,S[i])) return false;
    }
    return true;
}

/// функция для проверки введенных данных на корректность
int CheckInput(){
    const int N = 256;
    char S[N];
// проверяем на то что введелнное число - не строка и записываем его в переменнуб n
    cin.getline(S,N);
    while(!is_digit(S)){
        cerr << "Неправильный ввод, попробуйте еще раз!\n";
        cin.getline(S,N);
    }
    return atof(S);
}

int main() {
    int n;

    int matrix[10][10];
    cout << "Введите размерность матрицы(одно число - она квадратная): ";
    n = CheckInput();
    while (n <= 0) {
        cout << "Число должно быть положительным!";
        n = CheckInput();
    }
    cout << "Введите эдементы матрицы: ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = CheckInput();
    cout<<"Матрица, которую вы ввели :"<<endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout<<endl;
    }
    cout<<"Детерминант матрицы = "<< determinant(matrix, n);
    return 0;
}