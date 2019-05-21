#include <iostream>
#include <cstdlib>
#include <cstdio>
//#include<ctime>

#define N 6

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    srand(unsigned(time(0)));
    cout << 20 << endl;
    int count = 0;
    while (count ++ < 20) {
        short in[N+1][N+1] = {0}; char out[N][N+1] = {0};
        for (short r=0; r<N; ++r) {
            for (short c=0; c<N; ++c) {
                out[r][c] = (rand() & 1) ? '/' : '\\';
                if (out[r][c] == '/') {
                    ++ in[r+1][c];
                    ++ in[r][c+1];
                } else {
                    ++ in[r][c];
                    ++ in[r+1][c+1];
                }
            }
        }
        cout << N << endl;
        for (short r=0; r<=N; ++r) {
            for (short c=0; c<=N; ++c) {
                if (!in[r][c]) {
                    cout << (rand() & 1 ? '0' : '.');
                } else cout << in[r][c];
            }
            cout << endl;
        }
    }
    return 0;
} 