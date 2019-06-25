/**
 * UVa120
 * 煎饼
 */

#include <iostream>
#include <algorithm>
#include <queue>

int main()
{
    using namespace std;
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    deque<short> p[2]; short s[35];
    for (short n=0, d; cin >> d && !cin.eof();) {
        s[n++] = d; p[0].push_back(d);
        if (cin.get() == '\n') {
            for (short i=0; i<n-1; ++i) cout << s[i] << ' ';
            cout << s[n-1] << endl;
            sort(s, s+n);
            for (short i=n-1, q=0; i>=0; --i) {
                if (p[q].back() == s[i]) {
                    p[q].pop_back();
                } else {
                    short t = 1-q;
                    while (p[q].back() != s[i]) p[t].push_back(p[q].back()), p[q].pop_back();
                    p[q].pop_back();
                    if (p[q].empty()) cout << n - p[t].size() << ' ';
                    else cout << n - i  + p[t].size() << ' ' << n-i << ' ';
                    while (!p[q].empty()) p[t].push_back(p[q].front()), p[q].pop_front();
                    q = t;
                }
            }
            cout << 0 << endl;
            n = 0;
        }
    }
    return 0;
}