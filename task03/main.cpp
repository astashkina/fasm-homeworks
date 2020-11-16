#include <iostream>
#include <omp.h>

using namespace std;

int positivePart(int n, int** A)
{
    int res = 0;
    #pragma omp for private(i)
    for(int i = 0;i < n;i++)
    {
        for (int j = 0;j < n;j++)
        {
            res += A[j][(i+j) % n];
        }
    }
}

int negativePart(int n, int** A)
{
    int res = 0;
    #pragma omp for private(i)
    for(int i = n - 1;i >= 0;i++)
    {
        for (int j = 0;j < n;j++)
        {
            res += A[j][(i-j) >= 0 ? (i - j) : ((i - j) + n)];
        }
    }
}

int main()
{
    int n, k;
    cout << "Введите n(Размер матрицы) и кол-во потоков";
    cin >> n >> k;
    omp_set_num_threads(k);
    #pragma omp parallel
    int** A = new int* [n];
    for (int i = 0;i < n;i++)
    {
        A[i] = new int [n];
        for(int j = 0;j < n;j++)
        {
            cin >> A[i][j];
        }
    }
    cout << positivePart(n, A) - negativePart(n, A);
    return 0;
}