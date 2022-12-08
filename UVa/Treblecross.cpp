/**
 * UVa10561
 * Treblecross 游戏
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 210
int sg[N][N], g, n; char s[210]; bool ok[N], f[N];

int SG(int l, int i) {
    if (l <= 0) return 0;
    if (sg[i][l] >= 0) return sg[i][l];
    bool f[N] = {false};
    for (int j=i, k=i+l; j<k; ++j) if (s[j]=='.' && (j==i || s[j-1]=='.') && 
        (j<i+2 || s[j-2]=='.') && (j+1>=k || s[j+1]=='.') && (j+2>=k || s[j+2]=='.'))
        f[SG(j-i-2, i) ^ SG(k-j-3, j+3)] = true;
    for (int j=0; j<N; ++j) if (!f[j]) return sg[i][l] = j;
}

void win() {
    cout << "WINNING" << endl;
    for (int i=0, c=0; i<n; ++i) if (ok[i]) {
        if (c++) cout << ' ';
        cout << i+1;
    }
    cout << endl;
}

void lose() {
    cout << "LOSING" << endl << endl;
}

void solve() {
    cin >> s; n = strlen(s);
    memset(ok, g = 0, sizeof(ok));
    for (int i=0; i<n; ++i) if (s[i]=='.' && ((i+2<n && s[i+1]=='X' && s[i+2]=='X') ||
        (i>0 && i+1<n && s[i-1]=='X' && s[i+1]=='X') || (i>1 && s[i-1]=='X' && s[i-2]=='X'))) g = ok[i] = true;
    if (g) return win();
    memset(sg, -1, sizeof(sg)); memset(f, g = 0, sizeof(f));
    for (int i=0, j; i<n; ++i) if (s[i]=='.' && (i<1 || s[i-1]=='.') && 
        (i<2 || s[i-2]=='.') && (i+1>=n || s[i+1]=='.') && (i+2>=n || s[i+2]=='.'))
        f[j = SG(i-2, 0) ^ SG(n-i-3, i+3)] = true, ok[i] = !j;
    for (int i=0; i<N; ++i) if (!f[i]) {
        g = i; break;
    }
    return g ? win() : lose();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}