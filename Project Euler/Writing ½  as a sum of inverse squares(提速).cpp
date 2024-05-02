/**
 * https://projecteuler.net/problem=152
 */

#include <iostream>
#include <vector>
using namespace std;

#define N 81

int p[] = {17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79};
int t[N], q[3] = {7, 11, 13}, c[3][N], cc[3] = {0}, tt = 0, cnt = 0;
vector<vector<int> > a[3]; vector<vector<long long> > r[3];
bool use[N] = {false}; struct {long long n, d;} s[N];

long long gcd(long long a, long long b) {
    if (a > b) return gcd(b, a);
    if (a==0) return b;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b>>1);
    } else {
        if (b & 1) return gcd(a>>1, b);
        return gcd(a>>1, b>>1)<<1;
    } 
}

void dfs(short i, short j) {
    if (j >= cc[i]) {
        long long lcm = 1, sum = 0;
        for (j=0; j<cc[i]; ++j) if (use[j]) {
            int v = c[i][j]/q[i];
            lcm = v/gcd(lcm,v)*lcm;
        }
        if (lcm > 1) {
            lcm *= lcm;
            for (j=0; j<cc[i]; ++j) if (use[j]) {
                int v = c[i][j]/q[i];
                sum += lcm/v/v;
            }
            if (sum % (q[i]*q[i]) == 0) {
                vector<int> v;
                for (j=0; j<cc[i]; ++j) if (use[j]) v.push_back(c[i][j]);
                a[i].push_back(v);
                sum /= q[i]*q[i];
                long long g = gcd(sum, lcm);
                r[i].push_back({sum/g, lcm/g});
            }
        }
        return;
    }
    use[j] = true;
    dfs(i, j+1);
    use[j] = false;
    dfs(i, j+1);
}

void dfs(long long n, long long d, short i) {
    for (short j=i; j<tt; ++j) {
        long long g = n*t[j]*t[j];
        if (g < d) continue;
        if (g == d) {
            use[t[j]] = true;
            cout << 2;
            for (short k=3; k<N; ++k) if (use[k]) cout << ' ' << k;
            cout << endl;
            use[t[j]] = false;
            ++cnt;
            continue;
        }
        long long n1 = g-d, d1 = d*t[j]*t[j];
        g = gcd(s[j].d, d);
        if (d/g*s[j].n >= s[j].d/g*n) {
            use[t[j]] = true;
            g = gcd(n1, d1);
            dfs(n1/g, d1/g, j+1);
            use[t[j]] = false;
        }
    }
}

void dfs(short i, long long n, long long d) {
    if (i < 0) return dfs(n, d, 0);
    if (a[i].size() == 0) return dfs(i-1, n, d);
    for (short j=0; j<a[i].size(); ++j) {
        for (int k: a[i][j]) use[k] = true;
        long long g = gcd(r[i][j][1], d), n1 = r[i][j][1]/g*n - d/g*r[i][j][0], d1 = d/g*r[i][j][1];
        g = gcd(n1, d1);
        dfs(i-1, n1/g, d1/g);
        for (int k: a[i][j]) use[k] = false;
    }
    dfs(i-1, n, d);
}

int main() {
    // freopen("out.txt", "w", stdout);
    bool flag[N] = {false};
    for (short i=0; i<16; ++i) for (short j=N/p[i]; j>0; --j) flag[p[i]*j] = true;
    for (short i=2; i>=0; --i) for (short j=q[i]; j<N; j+=q[i]) if (!flag[j]) {
        flag[j] = true; c[i][cc[i]++] = j;
    }
    for (short i=0; i<3; ++i) dfs(i, 0);
    for (short i=3; i<N; ++i) if (!flag[i]) {
        bool ok = true;
        for (short j=0; j<3; ++j) if (i%q[j] == 0) {
            ok = false;
            break;
        }
        if (ok) t[tt++] = i;
    }
    s[tt-1].n = 1; s[tt-1].d = t[tt-1]*t[tt-1];
    for (short i=tt-2; i>=0; --i) {
        long long n = s[i+1].n*t[i]*t[i]+s[i+1].d, d = s[i+1].d*t[i]*t[i], g = gcd(n, d);
        s[i] = {n/g, d/g};
    }
    dfs(2, 1ll, 4ll);
    cout << cnt << endl;
}