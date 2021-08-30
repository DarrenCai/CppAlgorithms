#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <unordered_set>
using namespace std;

#define N 253

struct integer {
    int a[56], n;
    integer():n(0){}
    bool operator< (const integer& x) const {
        if (n == x.n) {
            for (int i=n-1; i>=0; --i) if (a[i] != x.a[i]) return a[i] < x.a[i];
            return false;
        }
        return n < x.n;
    }
    bool operator== (const integer& x) const {
        if (n != x.n) return false;
        for (int i=0; i<n; ++i) if (a[i] != x.a[i]) return false;
        return true;
    }
    integer operator+ (const integer& x) const {
        int m = max(n, x.n); long long r = 0; integer y;
        for (int i=0; i<m; ++i) {
            r = r + (i < n ? a[i] : 0) + (i < x.n ? x.a[i] : 0);
            y.a[y.n++] = r%1000000000;
            r /= 1000000000;
        }
        if (r > 0) y.a[y.n++] = r;
        return y;
    }
    integer operator- (const integer& x) const {
        integer y = *this;
        for (int i=0; i<y.n; ++i) {
            y.a[i] -= i < x.n ? x.a[i] : 0;
            if (y.a[i] < 0) {
                --y.a[i+1];
                y.a[i] += 1000000000;
            }
        }
        if (y.a[y.n-1] == 0) --y.n;
        return y;
    }
    integer operator* (const long long& x) const {
        integer y = *this;
        if (x == 0) {
            y.n = 0;
            return y;
        }
        long long r = 0;
        for (int i=0; i<y.n; ++i) {
            r = r + y.a[i]*x;
            y.a[i] = r%1000000000;
            r /= 1000000000;
        }
        if (r > 0) y.a[y.n++] = r;
        return y;
    }
    int operator/ (const integer& x) const {
        if (*this < x) return 0;
        __uint128_t y = x.a[x.n-1], z = n>x.n ? a[n-1]*(__uint128_t)1000000000 + a[n-2] : a[n-1];
        if (y<10000 && x.n>1) {
            y = y*1000000000 + x.a[x.n-2];
            z = z*1000000000 + a[x.n-2];
        }
        int k = z/y; integer i = x * k;
        if (i == *this) return k;
        if (*this < i) return --k;
        i = x + i;
        if (!(*this<i)) ++k;
        return k;
    }
    integer random() const {
        integer y = *this;
        for (int i=0; i<y.n; ++i)
            y.a[i] %= rand()%1000000000+1;
        while (y.n>1 && y.a[y.n-1]==0) --y.n;
        return y;
    }
    void print() const {
        printf("%d", a[n-1]);
        for (int i=n-2; i>=0; --i) printf("%09d", a[i]);
        printf("\n");
    }
} d[N][N];

int main()
{
    freopen("in.txt", "w", stdout);
    srand(unsigned(time(0)));
    for (int m=0; m<N; ++m) {
        d[m][m].a[0] = 1; d[m][m].n = 1;
        for (int n=m+1; n<N; ++n) d[m][n] = d[m][n-1]*n;
    }
    for (short i=0; i<50; ++i) {
        int n = rand()%(N-1)+1, m = rand()%n+1;
        integer k = d[m][n].random();
        cout << n << ' ' << m << ' ' << flush;
        k.print();
        unordered_set<int> s;
        while (s.size() < m) s.insert(rand()%n+1);
        unordered_set<int>::iterator it = s.begin();
        cout << *it;
        while (++it != s.end()) cout << ' ' << *it;
        cout << endl;
    }
    return 0;
}