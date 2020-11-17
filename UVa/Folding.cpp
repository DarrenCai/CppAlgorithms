/**
 * UVa1630
 * 串折叠
 */

#include <iostream>
using namespace std;

#define N 110
struct Node { short n, i, j, d; } d[N][N]; char s[N]; short len[N][N], n;

bool common(const Node &n1, const Node &n2) {
    if (n1.n == 1 || n2.n == 1) {
        short a = max(n1.j-n1.i, n2.j-n2.i)+1, b = min(n1.j-n1.i, n2.j-n2.i)+1;
        if (a % b != 0) return false;
        for (short i=0; i < b; ++i) if (s[n1.i+i] != s[n2.i+i]) return false;
        for (short i=n1.i+b; i<=n1.j; ++i) if (s[i] != s[n1.i+(i-n1.i)%b]) return false;
        for (short i=n2.i+b; i<=n2.j; ++i) if (s[i] != s[n2.i+(i-n2.i)%b]) return false;
        return true;
    }
    if (n1.j-n1.i != n2.j-n2.i) return false;
    if (n1.i == n2.i) return true;
    return common(d[n1.i][n1.j], d[n2.i][n2.j]);
}

void print(const Node &node) {
    if (node.d > 0) {
        print(d[node.i][node.d-1]); return print(d[node.d][node.j]);
    }
    if (node.n == 1) {
        for (short i=node.i; i <= node.j; ++i) cout << s[i];
        return;
    } else {
        cout << node.n << '(';
        print(d[node.i][node.j]);
        cout << ')';
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s) {
        for (n=0; s[n]; ++n);
        for (short l=1; l<=n; ++l) for (short i=0, j; i+l<=n; ++i) {
            Node &node = d[i][j=i+l-1]; node.n=1; node.i=i; node.j=j; node.d=0; len[i][j] = l;
            for (short ll=1; ll<l; ++ll) {
                Node &n1 = d[i][i+ll-1], &n2 = d[i+ll][j];
                if (common(n1, n2)) {
                    short a = n1.j-n1.i+1, b = n2.j-n2.i+1, m = min(a, b);
                    short nn = (n1.n > 1 ? n1.n : a/m) + (n2.n > 1 ? n2.n : b/m);
                    short v = (nn<10 ? 1 : (nn<100 ? 2 : 3)) + 2 + len[n1.i][n1.i+m-1];
                    if (v < len[i][j]) {
                        len[i][j] = v; node.n = nn; node.i = n1.i; node.j = n1.i+m-1; node.d=0;
                    }
                } else {
                    short v = len[i][i+ll-1] + len[i+ll][j];
                    if (v < len[i][j]) {
                        len[i][j] = v; node.i=i; node.j=j; node.d = i+ll;
                    }
                }
            }
        }
        print(d[0][n-1]);
        cout << endl;
    }
    return 0;
}