/**
 * UVa10561
 * Treblecross 游戏
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define N 210
int sg[N], p[N], n, c; char s[210];

int mex(vector<int> &s) {
    sort(s.begin(), s.end());
    if (s.size() == 0 || s[0]) return 0;
    for (int i=0, j=s.size()-1; i<j; ++i) if (s[i]!=s[i+1] && s[i+1]>s[i]+1) return s[i]+1;
    return s.back()+1;
}

void init() {
    sg[0] = 0; sg[1] = sg[2] = sg[3] = 1;
    for (int i=4; i<N; ++i) {
        vector<int> s; s.push_back(sg[i-3]); s.push_back(sg[i-4]);
        if (i >= 5) s.push_back(sg[i-5]);
        for (int j=(i+1)>>1; j>3; --j) s.push_back(sg[j-3] ^ sg[i-j-2]);
        sg[i] = mex(s);
    }
}

void judge(int x) {
    int t = 0, g = 0;
    for (int i=0; i<=n; ++i) {
        bool f = i==n || s[i]=='X' || (i>0 && s[i-1]=='X') ||
            (i>1 && s[i-2]=='X') || (i+1<n && s[i+1]=='X') || (i+2<n && s[i+2]=='X');
        if (f && i>t) g ^= sg[i-t];
        if (f) t = i+1;
    }
    if (!g) p[c++] = x;
}

void win() {
    cout << "WINNING" << endl << p[0];
    for (int i=1; i<c; ++i) cout << ' ' << p[i];
    cout << endl;
}

void lose() {
    cout << "LOSING" << endl << endl;
}

void solve() {
    cin >> s; n = strlen(s);
    for (int i=c=0; i<n; ++i) if (s[i]=='.' && ((i+2<n && s[i+1]=='X' && s[i+2]=='X') ||
        (i>0 && i+1<n && s[i-1]=='X' && s[i+1]=='X') || (i>1 && s[i-1]=='X' && s[i-2]=='X'))) p[c++] = i+1;
    if (c) return win();
    for (int i=0, j; i<n; ++i) if (s[i]=='.' && (i<1 || s[i-1]=='.') && 
        (i<2 || s[i-2]=='.') && (i+1>=n || s[i+1]=='.') && (i+2>=n || s[i+2]=='.')) s[i] = 'X', judge(i+1), s[i] = '.';
    return c ? win() : lose();
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    init();
    int t; cin >> t;
    while (t--) solve();
    return 0;
}