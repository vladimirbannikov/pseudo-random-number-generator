#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
unsigned long long next = 1;
unsigned long long _rand()
{
    unsigned long long int c = 1234321342121, a = 3315188075855877;
    next = (unsigned long long int)(a * next) / 2 + c;
    return next;
}
unsigned int _srand(unsigned int seed) {
    next = seed;
}
void specifications()
{
    unsigned long long a = 3315188075855877, first = 0, x = a-1, //Параметр a, первый элемент генератора и переменная для вычисления мощности
    m = 10000000, period = m; //Предполагаемый диапазон для поиска периода и период
    int power = 0; //Мощность генератора power = (a - 1)^power = 0(mod m)
    int k = 0;
    for (int i = 0; i < 10000; i++)
        first = _rand();
    for (int i = 0; i < 10000000; i++)
        if (_rand() == first)
            period = i;
    _srand(time(NULL));
    unsigned long long int rasbros[10000]; int fl = 0;
    for(int i = 0; i<10000; i++){
        rasbros[i] = _rand();
        for(int j = 0; j<i; j++){
            if(rasbros[j]==rasbros[i]) fl = 1;
        }
    }
    wprintf(L"Период генератора: >%llu\n", period);
    if(fl==0) wprintf(L"Разброс генератора - хороший, в искомом диапазоне 10000 \nне найдено повторяющихся элементов.\n");
    else wprintf(L"Разброс генератора плохой, в диапазоне 10000 найдены совпадающие элементы.");
    while (x % 2 == 0)
    {
        x /= 2;
        power++;
    }
    wprintf(L"Мощность генератора: %d\n", 64/power);
}
void punkt3(){
    _srand(time(NULL));
    wprintf(L"Проверка младших битов: \n");
    for(int i = 0; i<100; i++){
        wprintf(L"%llu ", _rand()%2);
    }
}
void xi_2()
{
    long long int k[11] = {0}, a, n = 1000000, kinterval = 0;
    double v1;
    _srand(time(NULL));
    for(int j = 0; j<10; j++) {
        v1 = 0;
        for (int i = 0; i < n; i++) {
            a = _rand() % 11;
            k[a]++;
        }
        for (int i = 0; i < 11; i++) {
            v1 += (k[i] * k[i] * 11);
        }
        v1 = v1 / n - n;
        if(v1>3.94&&v1<18.31) kinterval ++;
        for(int i = 0; i<11; i++) k[i] = 0;
    }
    wprintf(L"\nДля критерия X^2: Кол-во значений X^2, попадающих в интервал (5%, 95%): %d из %d, при n = %d, k = %d\n", kinterval, 10, n, 11);
}
void perest()
{
    long int k[6], n = 1000000, kinterval = 0;
    double v1;
    _srand(time(NULL));
    unsigned long long ms[3];
    for(int j = 0; j<10; j++) {
        v1 = 0;
        for(int i = 0; i<6; i++) k[i] = 0;
        for (int i = 0; i < n; i++) {
            ms[0] = _rand();
            ms[1] = _rand();
            ms[2] = _rand();
            if (ms[0] < ms[1] && ms[0] > ms[2]) k[0]++;
            if (ms[1] < ms[0] && ms[1] > ms[2]) k[1]++;
            if (ms[2] < ms[1] && ms[2] > ms[0]) k[2]++;
            if (ms[0] > ms[1] && ms[0] < ms[2]) k[3]++;
            if (ms[1] > ms[0] && ms[1] < ms[2]) k[4]++;
            if (ms[2] > ms[1] && ms[2] < ms[0]) k[5]++;
        }
        for(int i = 0; i<6; i++){
            v1 += (k[i] * k[i] * 6);
        }
        v1 = v1 / n - n;
        if(v1>1.1455&&v1<11.07) kinterval++;
    }
    wprintf(L"\nДля критерия перестановок: Кол-во значений X^2, попадающих в интервал (5%, 95%): %d из %d, при n = %d, k = %d", kinterval, 10, n, 6);
}
int main() {
    setlocale(0, "");
    punkt3();
    perest();
    xi_2();
    specifications();
    return 0;
}
