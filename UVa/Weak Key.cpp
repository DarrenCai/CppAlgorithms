/**
 * UVa1618
 * 弱键
 */

#include <iostream>
using namespace std;

#define N 5000
int a[N];
short n, b1[2][N][N], b2[2][N][N], n1[2][N], n2[2][N];

void bsi1(short q, short p) {
    if (a[q] < a[p]) {
        short low = 0, high = n1[0][q] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b1[0][q][mid]] < a[p]) high = mid - 1;
            else low = mid + 1;
        }
        for (short i = n1[0][q]; i>low; --i) b1[0][q][i] = b1[0][q][i-1];
        b1[0][q][low] = p;
        ++ n1[0][q];
    } else {
        short low = 0, high = n1[1][q] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b1[1][q][mid]] < a[p]) low = mid + 1;
            else high = mid - 1;
        }
        for (short i = n1[1][q]; i>low; --i) b1[1][q][i] = b1[1][q][i-1];
        b1[1][q][low] = p;
        ++ n1[1][q];
    }
}

void bsi2(short r, short s) {
    if (a[s] < a[r]) {
        short low = 0, high = n2[0][r] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b2[0][r][mid]] < a[s]) low = mid + 1;
            else high = mid - 1;
        }
        for (short i = n2[0][r]; i>low; --i) b2[0][r][i] = b2[0][r][i-1];
        b2[0][r][low] = s;
        ++ n2[0][r];
    } else {
        short low = 0, high = n2[1][r] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b2[1][r][mid]] < a[s]) high = mid - 1;
            else low = mid + 1;
        }
        for (short i = n2[1][r]; i>low; --i) b2[1][r][i] = b2[1][r][i-1];
        b2[1][r][low] = s;
        ++ n2[1][r];
    }
}

bool bs(short q, short r) {
    if (a[q] < a[r]) {
        if (!n1[0][q] || !n2[0][r]) return false;
        short low = 0, high = n1[0][q] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b1[0][q][mid]] > a[r]) low = mid + 1;
            else high = mid - 1;
        }
        if (low < 0 || low >= n1[0][q]) return false;
        short p = b1[0][q][low];
        low = 0, high = n2[0][r] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b2[0][r][mid]] > a[q]) high = mid - 1;
            else low = mid + 1;
        }
        if (low < 0 || low >= n2[0][r]) return false;
        short s = b2[0][r][low];
        return a[q] < a[s] && a[s] < a[p] && a[p] < a[r];
    } else {
        if (!n1[1][q] || !n2[1][r]) return false;
        short low = 0, high = n1[1][q] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b1[1][q][mid]] > a[r]) high = mid - 1;
            else low = mid + 1;
        }
        if (low < 0 || low >= n1[1][q]) return false;
        short p = b1[1][q][low];
        low = 0, high = n2[1][r] - 1;
        while (low <= high) {
            short mid = (low + high) >> 1;
            if (a[b2[1][r][mid]] > a[q]) low = mid + 1;
            else high = mid - 1;
        }
        if (low < 0 || low >= n2[1][r]) return false;
        short s = b2[1][r][low];
        return a[q] > a[s] && a[s] > a[p] && a[p] > a[r];
    }
}

void solve() {
    for (short q=1; q<n-2; ++q) {
        n1[0][q] = n1[1][q] = 0;
        for (short p=0; p<q; ++p) bsi1(q, p);
    }
    for (short r=2; r<n-1; ++r) {
        n2[0][r] = n2[1][r] = 0;
        for (short s=r+1; s<n; ++s) bsi2(r, s);
    }
    for (short q=1; q<n-2; ++q) for (short r=q+1; r<n-1; ++r)
        if (bs(q, r)) {
            cout << "YES" << endl;
            return;
        }
    cout << "NO" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) {
        cin >> n; for (short i=0; i<n; ++i) cin >> a[i];
        solve();
    }
    return 0;
}