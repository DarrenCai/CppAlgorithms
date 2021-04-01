/**
 * UVa1641
 * ASCII面积
 */

#include <iostream>
using namespace std;

#define N 110
char s[N]; short h, w;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> h >> w) {
        short area = 0;
        for (short i=0; i<h; ++i) {
            cin >> s;
            short index, t = 0;
            for (short j=0; j<w; ++j) if (s[j] != '.') {
                if (t++ & 1) area += j-index;
                index = j;
            }
        }
        cout << area << endl;
    }
    return 0;
}