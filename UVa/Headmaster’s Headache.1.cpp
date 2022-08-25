/**
 * UVa10817
 * 校长的烦恼
 */

#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

#define S 8
#define N 110
#define T 6600
int a[S], d[T], s, m, n; char buf[N]; istringstream iss;

int encode() {
    int x = 0;
    for (int i=0; i<s; ++i) x = 3*x + a[i];
    return x;
}

void decode(int x) {
    for (int i=s-1; i>=0; --i) a[i] = x%3, x /= 3;
}

int solve() {
    int cc = 0;
    cin.get(); memset(a, 0, sizeof(a)); memset(d, 0, sizeof(d));
    for (int i=0; i<m; ++i) {
        cin.getline(buf, N); iss.str(buf); iss.clear();
        int c; iss >> c; cc += c;
        while (iss >> c) if (a[--c] < 2) ++a[c];
    }
    int x = encode(), y = 0;
    for (int i=0; i<s; ++i) y = 3*y + 2;
    d[x] = cc;
    for (int i=0; i<n; ++i) {
        cin.getline(buf, N);
        if (x == y) continue;
        int c; bool b[S] = {false};
        iss.str(buf); iss.clear(); iss >> c;
        while (iss >> m) b[--m] = true;
        for (int j=y; j>=x; --j) if (d[j]) {
            decode(j);
            bool f = true;
            for (int k=0; k<s; ++k) if (b[k] && a[k]<2) ++a[k], f = false;
            if (f) continue;
            int z = encode();
            d[z] ? d[z] = min(d[z], d[j]+c) : d[z] = d[j]+c;
        }
    }
    return d[y];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>s>>m>>n && s) cout << solve() << endl;
    return 0;
}