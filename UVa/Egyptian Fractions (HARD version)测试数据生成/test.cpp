#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include<ctime>

short gcd(short a, short b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    } 
}

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    srand(unsigned(time(0)));
    for (short i=876; i>2; --i) {
        short t=0;
        for (short j=i-1; j>1; --j) {
            if (gcd(j, i) == 1) {
                bool use = rand() & 1;
                if (!use) continue;
                if (++ t > 7) break;
                short k = rand()%5 + 1;
                short min = (i+j-1)/j;
                set<int> s;
                while (s.size() < k)
                    s.insert((rand()&0x7f) + min);
                cout << j << ' ' << i << ' ' << k;
                for (auto v: s) cout << ' ' << v;
                cout << endl;
            }
        }
    }
    return 0;
}