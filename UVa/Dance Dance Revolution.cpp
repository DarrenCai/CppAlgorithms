/**
 * UVa1291/LA2031
 * Shanghai 2000
 */

#include <iostream>
using namespace std;

int d[2][5][5];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int x;
    while (cin>>x && x) {
        for (int i=0; i<5; ++i) for (int j=0; j<5; ++j) d[0][i][j] = -1;
        d[0][0][x] = 2;
        int a = 0, b = 1;
        while (cin>>x && x) {
            for (int i=0; i<5; ++i) for (int j=0; j<5; ++j) d[b][i][j] = -1;
            for (int i=0; i<5; ++i) for (int j=0; j<5; ++j) if (d[a][i][j] >= 0) {
                if (i==x || j==x) {
                    d[b][i][j] = d[b][i][j]==-1 ? d[a][i][j] + 1 : min(d[b][i][j], d[a][i][j] + 1);
                } else {
                    int v = d[a][i][j] + (i==0 ? 2 : (abs(x-i)==2 ? 4 : 3));
                    d[b][x][j] = d[b][x][j]==-1 ? v : min(v, d[b][x][j]);
                    v = d[a][i][j] + (j==0 ? 2 : (abs(x-j)==2 ? 4 : 3));
                    d[b][i][x] = d[b][i][x]==-1 ? v : min(v, d[b][i][x]);
                }
            }
            a = 1^a; b = 1^b;
        }
        int ans = -1;
        for (int i=0; i<5; ++i) for (int j=0; j<5; ++j) if (d[a][i][j] > 0)
            ans = ans==-1 ? d[a][i][j] : min(d[a][i][j], ans);
        cout << ans << endl;
    }
    return 0;
}