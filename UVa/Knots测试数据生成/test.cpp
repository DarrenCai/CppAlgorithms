#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include<ctime>

#define L 30

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    srand(unsigned(time(0)));
    cout << 100 << endl;
    int count = 0;
    while(count++ < 100)
    {
        int l = rand() % L + 1, p = l==1 ? 0 : rand() % ((l>>1)+1);
        if (p > 5000) p = 5000;
        set<int> s;
        cout << endl << l << ' ' << p << endl;
        while (p--) {
            int a = rand() % l, b = rand() % l;
            while (s.count(a)) a = rand() % l;
            while (s.count(b) || a==b) b = rand() % l;
            s.insert(a); s.insert(b);
            cout << a << ' ' << b << endl;
        }
    }
    return 0;
}