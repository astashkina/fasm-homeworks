#include "pthread.h"
#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

int n, N, swallowCount, i;
int startTime;

pthread_t *bees;
pthread_mutex_t beeT, bearT;


void *FillingThePot(void *param) {
    int beeNumber = *((int *) param);

    while (time(nullptr) - startTime < 30)
    {
        pthread_mutex_lock(&beeT);

        swallowCount++;
        cout << "Пчела #" << beeNumber << " заполнила горшок " << swallowCount << " глотков." << endl;

        if (swallowCount == N) {
            cout << "Пчела #" << beeNumber << " будит медведя." << endl;
            pthread_mutex_unlock(&bearT);
            continue;
        }

        i++;
        cout << "Другие пчелы теперь тоже имеют доступ к горшку!" << endl;
        pthread_mutex_unlock(&beeT);
        sleep(100);
    }

    pthread_mutex_unlock(&beeT);
    pthread_mutex_unlock(&bearT);
}

void *DrinkingThePot() {
    while (time(nullptr) - startTime < 30){
        pthread_mutex_lock(&bearT);

        cout << "Медведь выпил " << swallowCount << " глотков меда." << endl;
        swallowCount = 0;
        sleep(100);
        i++;
         cout << "Другие пчелы теперь тоже имеют доступ к горшку!" << endl;
        pthread_mutex_unlock(&beeT);
    }

    pthread_mutex_unlock(&beeT);
    return nullptr;
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

int main() {
    startTime = time(nullptr);
    cout << "Введите количество пчел: ";
    n = CheckInput();
    while (n <= 0 || n >= 50){
        cout << "Некорректный ввод! Попробуйте еще раз: ";
        n = CheckInput();
    }

    cout << "Введите количество глотоков в горшке: ";
    N = CheckInput();
    while (N <= 0 || N >= 500){
        cout << "Некорректный ввод! Попробуйте еще раз.\n";
        N = CheckInput();
    }

    pthread_mutex_init(&beeT, nullptr);
    pthread_mutex_init(&bearT, nullptr);

    bees = new pthread_t[n];
    swallowCount = 0;

    int *beess = new int[n];

    for (size_t i = 0; i < n; i++) {
        beess[i] = i + 1;
        pthread_create(&bees[i], nullptr, FillingThePot, (void *) (beess + i));
    }

    pthread_mutex_lock(&bearT);
    DrinkingThePot();

    delete[] beess;
    delete[] bees;

    return 0;
}
