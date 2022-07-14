/**
 * UVa10085
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 9
#define M 362900
int f[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320}, a[N], b[N], p[M], q[M], s[N]; char d[M];

int cantor() {
    int c = 0;
    for (int i=0; i<N; ++i) {
        int v = 0;
        for (int j=i+1; j<N; ++j) if (a[j] < a[i]) ++v;
        c += v * f[N-i-1];
    }
    return c;
}

void decantor(int v) {
    for (int i=0; i<N; ++i) s[i] = i;
    for (int i=0; i<N; ++i) {
        int c = v / f[N-i-1];
        v %= f[N-i-1];
        b[i] = s[c];
        for (int j=c+1; j<N; ++j) s[j-1] = s[j];
    }
}

void printPath(int v) {
    if (p[v] == M) return;
    printPath(p[v]);
    cout << d[v];
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int i=1; i<=t; ++i) {
        memset(p, -1, sizeof(p));
        for (int i=0; i<N; ++i) cin >> a[i];
        p[q[0] = cantor()] = M;
        int head = 0, tail = 1;
        while (head < tail) {
            int c = q[head++];
            decantor(c);
            for (int row=0; row<3; ++row) for (int col=0; col<3; ++col) {
                int j = 3*row + col;
                if (b[j] == 0) {
                    if (row > 0) {
                        int k = 3*(row-1) + col;
                        for (short e=0; e<N; ++e) a[e] = e==j ? b[k] : (e==k ? b[j] : b[e]);
                        int v = cantor();
                        if (p[v] < 0) {
                            p[v] = c; d[v] = 'U'; q[tail++] = v;
                        }
                    }
                    if (row < 2) {
                        int k = 3*(row+1) + col;
                        for (short e=0; e<N; ++e) a[e] = e==j ? b[k] : (e==k ? b[j] : b[e]);
                        int v = cantor();
                        if (p[v] < 0) {
                            p[v] = c; d[v] = 'D'; q[tail++] = v;
                        }
                    }
                    if (col > 0) {
                        int k = 3*row + col-1;
                        for (short e=0; e<N; ++e) a[e] = e==j ? b[k] : (e==k ? b[j] : b[e]);
                        int v = cantor();
                        if (p[v] < 0) {
                            p[v] = c; d[v] = 'L'; q[tail++] = v;
                        }
                    }
                    if (col < 2) {
                        int k = 3*row + col+1;
                        for (short e=0; e<N; ++e) a[e] = e==j ? b[k] : (e==k ? b[j] : b[e]);
                        int v = cantor();
                        if (p[v] < 0) {
                            p[v] = c; d[v] = 'R'; q[tail++] = v;
                        }
                    }
                }
            }
        }
        int v = q[--tail]; decantor(v);
        cout << "Puzzle #" << i << endl;
        for (int j=0; j<9; j+=3) cout << b[j] << ' ' << b[j+1] << ' ' << b[j+2] << endl;
        printPath(v);
        cout << endl << endl;
    }
    return 0;
}