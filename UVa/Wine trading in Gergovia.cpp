/**
 * UVa11054
 * Gergovia的酒交易
 */

#include <iostream>
#include <queue>
using namespace std;

struct village {
    int p; short a;
    village(int p, short a):p(p),a(a){};
};
queue<village> buy, sale;

int main()
{
    int n;
    while (cin >> n && n) {
        long long t = 0; short a;
        for (int i=0; i<n; ++i) {
            cin >> a;
            if (a > 0) {
                while (!sale.empty()) {
                    village &v = sale.front();
                    a += v.a;
                    if (a < 0) {
                        t -= (v.a - a) * (i - v.p); v.a = a;
                        break;
                    } else {
                        t -= v.a * (i - v.p);
                        sale.pop();
                    }
                }
                if (a > 0) buy.push(village(i, a));
            } else {
                while (!buy.empty()) {
                    village &v = buy.front();
                    a += v.a;
                    if (a > 0) {
                        t += (v.a - a) * (i - v.p); v.a = a;
                        break;
                    } else {
                        t += v.a * (i - v.p);
                        buy.pop();
                    }
                }
                if (a < 0) sale.push(village(i, a));
            }
        }
        cout << t << endl;
    }
    return 0;
}