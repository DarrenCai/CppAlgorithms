#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <set>
using namespace std;

const short N = 10;

int main()
{
    freopen("in.txt", "w", stdout);
    srand(time(NULL));
    for (short i=0; i<1000; ++i) {
        short n = rand()%N, m = n>0 ? rand()%((n-1)*n/2+1) : 0;
        bool vis[N][N] = {false}; short c[N] = {0};
        cout << n << ' ' << m;
        while (m--) {
            short u = rand()%n, v = rand()%n;
            while (c[u] == n-1) u = rand()%n;
            while (v==u || vis[u][v]) {
                v = rand()%n;
            }
            ++c[u]; ++c[v];
            vis[u][v] = vis[v][u] = true;
            cout << " (" << u << ',' << v << ')';
        }
        cout << endl;
    }
    return 0;
}