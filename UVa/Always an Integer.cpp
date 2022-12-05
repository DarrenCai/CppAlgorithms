/**
 * UVa1069/LA4119
 * 总是整数
 * World Finals >> 2008 - Banff
 * cin >> ws：告诉编译器忽略缓冲区，并丢弃字符串或字符数组实际内容之前的所有不能打印的字符。
 * cin.peek()：观测输入流指针指向的当前字符（遇到流结束返回EOF），流指针并不后移。
 */

#include <iostream>
using namespace std;

#define N 102
int c[N], e[N], kase = 0; char s[N];

void solve() {
    int n = 0, d; char ch = cin.get();
    while (cin.peek() != ')') {
        ch = cin.peek();
        c[n] = 1;
        int s = ch == '-' ? -1 : 1;
        if (ch=='+' || ch=='-') cin >> ch;
        if (cin.peek() != 'n') cin >> c[n];
        c[n] *= s;
        if (cin.peek() == 'n') {
            cin >> ch;
            if (cin.peek() != '^') e[n++] = 1;
            else cin >> ch >> e[n++];
        } else e[n++] = 0;
    }
    cin >> ch >> ch >> d >> ws;
    bool ok = d == 1;
    if (!ok) {
        ok = true;
        for (int x=0; x<=e[0]; ++x) {
            long long r = 0, p = 1;
            for (int i=n-1, y = 0; i>=0; --i) {
                while (y < e[i]) p = (p*x) % d, ++y;
                r = (r + c[i] * p) % d;
            }
            if (r%d != 0) {
                ok = false; break;
            }
        }
    }
    cout << "Case " << ++kase << ": " << (ok ? "Always" : "Not always") << " an integer" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin.peek() != '.') solve();
    return 0;
}