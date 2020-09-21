#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
// #include<ctime>

using namespace std;

#define N 210
short g[N][N], gc[N] = {0}, n, t = 1, last = 1; queue<short> q;

void build() {
    if (t >= n) return;
    q.push(1);
    while(!q.empty()) {
        short i = q.front(); q.pop();
        const short c = max(rand()%min((n-t), 5), 1); t += c;
        // const short c = max(rand()%min((n-t), 15), 1); t += c;
        for (short j=0; j<c; ++j) g[i][gc[i]++] = ++last, q.push(last);
        if (t >= n) return;
    }
}

void print(short i) {
    if (gc[i] == 0) return;
    cout << i << ' ';
    for (short j=0; j<gc[i]; ++j) {
        short f = rand() % 3;
        cout << g[i][j] << (f==0 ? " " : (f==1 ? "d " : "u "));
    }
    cout << 0 << endl;
    for (short j=0; j<gc[i]; ++j) print(g[i][j]);
}

int main()
{
    srand(time(nullptr));
    freopen("in.txt", "w", stdout);
    // n = max(rand()%N, 1);
    n = 13;
    // n = 57;
    build();
    short count = 0;
    while (count++ < 10000) {
        print(1);
        cout << 0 << endl;
    }
    cout << 0 << endl;
    return 0;
}
