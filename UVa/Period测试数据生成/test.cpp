#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

// #define M 5000
// #define N 50
#define M 20
#define N 5

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    srand(unsigned(time(0)));
    cout << 1000 << endl;
    int count = 0;
    while(count++ < 1000)
    {
        short m = rand()%10+M-9, n = rand()%N+1;
        for (short i=0; i<n; ++i) cout << char('a'+rand()%26);
        cout << endl;
        for (short i=0; i<m; ++i) cout << char('a'+rand()%26);
        cout << endl;
    }
    return 0;
} 