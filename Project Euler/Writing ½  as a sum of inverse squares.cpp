/**
 * https://projecteuler.net/problem=152
 */

#include <iostream>
using namespace std;

#define M 81
#define N 41

int v[M], cnt = 0, p[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 18, 20, 21, 24, 25, 27, 28, 30,
                          32, 35, 36, 39, 40, 42, 45, 48, 49, 50, 52, 54, 56, 60, 63, 64, 70, 72, 75, 80};
struct {long long n, d;} s[N+1];            

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

void print(short d) {
    if (!v[d]) {
        cout << d;
        return;
    }
    print(v[d]);
    cout << ' ' << d;
}

void dfs(long long n, long long d, short i) {
    for (short j=i+1; j<=N; ++j) {
        long long g = n*p[j]*p[j];
        if (g < d) continue;
        if (g == d) {
            v[p[j]] = p[i];
            print(p[j]);
            cout << endl;
            ++cnt;
            continue;
        }
        long long n1 = g-d, d1 = d*p[j]*p[j];
        g = gcd(s[j].d, d);
        if (d/g*s[j].n < s[j].d/g*n) return;
        v[p[j]] = i==-1 ? 0 : p[i];
        g = gcd(n1, d1);
        dfs(n1/g, d1/g, j);
    }
}

int main() {
    // freopen("out.txt", "w", stdout);
    s[N].n = 1; s[N].d = p[N]*p[N];
    for (short i=N-1; i>=0; --i) {
        long long n = s[i+1].n*p[i]*p[i] + s[i+1].d, d = s[i+1].d*p[i]*p[i], g = gcd(n, d);
        s[i].n = n/g; s[i].d = d/g;
    }
    dfs(1, 2, -1);
    cout << cnt << endl;
    return 0;
}