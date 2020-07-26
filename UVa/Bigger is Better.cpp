/**
 * UVa12105
 * 越大越好
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define N 105
#define M 3005
short n, m, c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const long long p17 = 100000000000000000ll;

struct num {
    long long p[3];
    num():p{0, 0, 0}{}
    bool invalid() const {
        return p[0] < 0;
    }
    bool operator> (const num& rhs) const {
        if (p[2] != rhs.p[2]) return p[2] > rhs.p[2];
        if (p[1] != rhs.p[1]) return p[1] > rhs.p[1];
        return p[0] > rhs.p[0];
    }
    num append(short v) const {
        num tmp;
        if (invalid()) {
            tmp.p[0] = v;
        } else {
            tmp.p[2] = p[2]*10 + p[1]/p17;
            tmp.p[1] = p[1]%p17*10 + p[0]/p17;
            tmp.p[0] = p[0]%p17*10 + v;
        }
        return tmp;
    }
    void print() const {
        if (p[2] > 0) cout << p[2] << setfill('0') << setw(18) << p[1] << setw(18) << p[0];
        else if (p[1] > 0) cout << p[1] << setfill('0') << setw(18) << p[0];
        else cout << p[0];
    }
} d[N][M];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short kase = 0;
    while (cin >> n >> m && n) {
        memset(d, -1, sizeof(d));
        for (short v=0; v<10; ++v) d[c[v]][v%m] = num().append(v);
        for (short i=0; i<n; ++i) for (short j=0; j<m; ++j) if (!d[i][j].invalid()) {
            if (d[i][j] > d[i+1][j]) d[i+1][j] = d[i][j];
            for (short v=0; v<10; ++v) if (i+c[v] <= n) {
                num tmp = d[i][j].append(v); short r = (10*j+v)%m; 
                if (tmp > d[i+c[v]][r]) d[i+c[v]][r] = tmp;
            }
        }
        cout << "Case " << ++kase << ": ";
        if (d[n][0].invalid()) cout << -1;
        else d[n][0].print();
        cout << endl;
    }
    return 0;
}