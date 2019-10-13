/**
 * UVa1612
 * 猜名次
 */

#include <iostream>
#include <iomanip>
using namespace std;

#define max(a,b) (a>b ? a:b)
#define min(a,b) (a<b ? a:b)
#define N 16385
short n, k=0, r[N]; int s[N][3], a[8]={0};

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << setiosflags(ios::fixed) << setprecision(2);
    while (cin >> n && n) {
        for (short i=1; i<=n; ++i) {
            float a, b, c; cin >> a >> b >> c;
            int ia = a*100+.5, ib = b*100+.5, ic = c*100+.5;
            s[i][0] = max(ia, max(ib,ic));
            s[i][2] = min(ia, min(ib,ic));
            s[i][1] = ia + ib + ic - s[i][0] - s[i][2];
        }
        for (short i=1; i<=n; ++i) cin >> r[i];
        int m = s[r[1]][0] + s[r[1]][1] + s[r[1]][2];
        bool ok = true;
        for (short i=2; i<=n; ++i) {
            a[0] = s[r[i]][0] + s[r[i]][1] + s[r[i]][2];
            a[1] = a[0] - s[r[i]][2];
            a[2] = a[0] - s[r[i]][1];
            int v = a[0] - s[r[i]][0];
            a[3] = max(s[r[i]][0], v);
            a[4] = min(s[r[i]][0], v);
            a[5] = s[r[i]][1];
            a[6] = s[r[i]][2];
            bool flag = false;
            for (short j=0; j<8; ++j)
                if (a[j] < m || (a[j] == m && r[i] > r[i-1])) {
                    m = a[j]; flag = true; break;
                }
            if (!(ok = flag)) break;
        }
        cout << "Case " << ++k << ": ";
        if (ok) {
            cout << (m/100.0) << endl;
        } else cout << "No solution" << endl;
    }
    return 0;
}