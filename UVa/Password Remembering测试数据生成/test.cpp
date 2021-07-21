#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#define N 1000

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    srand(unsigned(time(0)));
    int count = 0;
    cout << 25 << endl;
    while(count++ < 25)
    {
        int a = rand() % N, b = rand() % N;
        cout << a << ' ' << a+b << endl;
    }
    return 0;
} 