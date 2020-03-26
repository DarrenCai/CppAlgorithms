/**
 * UVa10817
 * 校长的烦恼
 */

#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define INF 1e8
#define S 10
#define M 22
#define N 102
short s, m, n; int c[N], t[N], a[S], b[S], d[45000][N]; char buf[N];

int encode() {
    int v = 0;
    for (int i=0; i<s; ++i) v |= a[i] << (i<<1);
    return v;
}

void decode(int v) {
    for (int i=0; i<s; ++i) a[i] = v&3, v >>= 2;
}

int dp(int v, short i) {
    if (v == 0) return 0;
    if (i < 0) return INF;
    if (d[v][i] > -1) return d[v][i];
    d[v][i] = INF;
    decode(v);
    bool ok = false;
    for (int j=0; j<s; ++j) if (a[j] && t[i] & (1<<j)) ok = true, --a[j];
    if (ok) d[v][i] = c[i] + dp(encode(), i-1);
    return d[v][i] = min(min(d[v][i], dp(v, i-1)), INF);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    istringstream is;
    while (cin>>s>>m>>n && s) {
        cin.get();
        int cost = 0; 
        memset(t, 0, sizeof(t)); memset(d, -1, sizeof(d));
        for (int i=0; i<s; ++i) a[i] = 2;
        for (short i=0; i<m; ++i) {
            cin.getline(buf, N);
            is.str(buf); is.clear();
            int k; is >> k;
            cost += k;
            while (is >> k && k--) if (a[k] > 0) --a[k];
        }
        int v = encode();
        for (short i=0; i<n; ++i) {
            cin.getline(buf, N);
            is.str(buf); is.clear();
            is >> c[i];
            int k;
            while (is >> k && k--) t[i] |= 1<<k;
        }
        cout << cost + dp(v, n) << endl;
    }
    return 0;
}