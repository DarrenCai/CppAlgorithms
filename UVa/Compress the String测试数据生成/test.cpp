#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <set>
using namespace std;

int main()
{
    freopen("in.txt", "w", stdout);
    srand(time(NULL));
    for (int i=0; i<150; ++i) {
        short n = rand()%4 + 1, t, l;
        cout << n << endl << ( t = l = rand()%4+1);
        for (short j=1; j<n; ++j) {
            cout << ' ' << (l = rand()%4+1);
            t *= l;
        }
        cout << endl;
        short m = rand()%(t+1) + 1;
        for (short j=0; j<m; ++j) cout << char('a'+rand()%26);
        cout << endl;
    }
    return 0;
}