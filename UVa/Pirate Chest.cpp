/**
 * UVa1580
 * 海盗的宝箱
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define max(a, b) (a>b ? a:b)
#define N 502
int a, b, m, n, d[N][N], w[N][N][2], h[N*N], q[N], t;

long long calc(long long hi, int mn, int mx) {
    long long s = hi * mn, hh = s / (mn-mx);
    if (s % (mn-mx) == 0) --hh;
    return hh * mx;
}

long long solve() {
    const int mn = m*n, mab = min(a,n)*min(b,m), mba = min(a,m)*min(b,n), mx = max(mab, mba); long long ans = 0;
    while (t--) {
        int mxx = 0, len = 0; bool br = false;
        for (int i=m-1; i>=0; --i) for (int j=0; j<n; ++j) {
            if (d[i][j] < h[t]) {
                w[i][j][0] = w[i][j][1] = 0;
            } else {
                w[i][j][0] = j==0 ? 1 : 1 + w[i][j-1][0];
                w[i][j][1] = i==m-1 ? 1 : 1 + w[i+1][j][1];
                d[i][j] = t>0 ? h[t-1] : 0;
            }
        }
        for (int i=0; !br && i<m; ++i) for (int j=0; !br && j<n; ++j) {
            if (!w[i][j][0]) len = 0;
            else {
                int mh = min(b, w[i][j][1]);
                mxx = max(mxx, mh);
                while (len && min(b, w[i][q[len-1]][1]) >= mh) --len;
                if (!i || min(w[i][j][0], a) > min(w[i-1][j][0], a)) {
                    if (len == 0) {
                        mxx = max(mxx, min(w[i][j][0], a) * mh);
                    } else for (int k=len-1; k>=0; --k) {
                        int mw = j-q[k]+1;
                        if (mw > a) break;
                        int mh1 = min(b, w[i][q[k]][1]), loss = mh * (k==len-1 ? 1 : j-q[k+1]+1) - mw*mh1;
                        if (loss >= 0) break;
                        mxx = max(mxx, mw * (mh = mh1));
                    }
                }
                q[len++] = j;
                if (mxx == mab) br = true;
            }
        }
        len = 0; br = false;
        if (a != b && mxx < mba) for (int j=n-1; !br && j>=0; --j) for (int i=m-1; !br && i>=0; --i) {
            if (!w[i][j][0]) len = 0;
            else {
                int mw = min(b, w[i][j][0]);
                mxx = max(mxx, mw);
                while(len && min(a, w[q[len-1]][j][0]) >= mw) --len;
                if (j==n-1 || min(w[i][j][1], a) > min(w[i][j+1][1], a)) {
                    if (len == 0) {
                        mxx = max(mxx, min(w[i][j][1], a) * mw);
                    } else for (int k=len-1; k>=0; --k) {
                        int mh = i-q[k]+1;
                        if (mh > a) break;
                        int mw1 = min(b, w[q[k]][j][0]), loss = mw * (k==len-1 ? 1 : i-q[k+1]+1) - mh*mw1;
                        if (loss >= 0) break;
                        mxx = max(mxx, mh * (mw = mw1));
                    }
                }
                q[len++] = i;
                if (mxx == mba) br = true;
            }
        }
        ans = max(calc(h[t], mn, mxx), ans);
        if (mxx == mx) return ans;
    }
    return ans;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    while (cin >> a >> b >> m >> n) {
        t = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) cin >> d[i][j], h[t++] = d[i][j];
        sort(h, h+t); t = unique(h, h+t) - h;
        cout << solve() << endl;
    }
    return 0;
}