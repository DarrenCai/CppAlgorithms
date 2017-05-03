/**
 * UVa12657
 * 移动盒子
 */

#include <iostream>

int main()
{
    using namespace std;
    int n, m, count=0;
    while(cin >> n >> m) {
        int *next = new int[n+1]; next[n] = 0;
        int *prev = new int[n+1]; prev[0] = n;
        for(int i=0; i<n; ++i) {
            next[i] = i+1;
            prev[i+1] = i;
        }
        for(int i=0; i<m; ++i) {
            int op, x, y, t;
            cin >> op;
            if(op != 4) cin >> x >> y;
            switch(op) {
                case 1:
                    if(next[x] != y) {
                        next[prev[x]] = next[x];
                        prev[next[x]] = prev[x];
                        next[prev[y]] = x;
                        prev[x] = prev[y];
                        prev[y] = x;
                        next[x] = y;
                    }
                    break;
                case 2:
                    if(next[y] != x) {
                        next[prev[x]] = next[x];
                        prev[next[x]] = prev[x];
                        prev[next[y]] = x;
                        next[x] = next[y];
                        next[y] = x;
                        prev[x] = y;
                    }
                    break;
                case 3:
                    t = prev[y];
                    prev[y] = prev[x];
                    next[prev[x]] = y;
                    next[t] = x;
                    prev[x] = t;
                    t = next[x];
                    next[x] = next[y];
                    prev[next[y]] = x;
                    prev[t] = y;
                    next[y] = t;
                    break;
                case 4:
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wempty-body"
                    for(x=0; next[x]; prev[x]=next[x], x=next[x]); prev[x] = 0;
                    for(x=0; prev[x]; next[prev[x]]=x, x=prev[x]); next[x] = 0;
#pragma clang diagnostic pop
            }
        }
        int sum = 0;
        for(int i=0,x=0; next[x]; ++i,x=next[x]) if(i&1) sum+=next[x];
        cout << "Case " << ++count << ": " << sum << endl;
    }
    return 0;
}