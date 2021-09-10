#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
//#include<ctime>

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    //srand(unsigned(time(0)));
    cout << 100 << endl;
    short count = 0;
    while(count++ < 100)
    {
        short n = rand()%4 + 2;
        short m = 26 + rand()%5;
        cout << n << ' ' << m << endl;
        short k = rand()%m;
        cout << k;
        set<short> s;
        while (s.size() != k) {
            s.insert(2+rand()%(m-1));
        }
        for (auto v: s) cout << ' ' << v;
        cout << endl;
        for (short i=0; i<n; ++i) {
            cout << "0." << 1 + rand()%999;
            for (short j=1; j<m; ++j)
                cout << " 0." << 1 + rand()%999;
            cout << endl;
        }
    }
    return 0;
} 