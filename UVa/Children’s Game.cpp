/**
 * UVa10905
 * 孩⼦们的游戏
 */

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define M 1020
#define N 60
char s[N][M], ss[M]; short len[N], a[N], n;

bool cmp(short i, short j) {
    short l = min(len[i], len[j]), c = strncmp(s[i], s[j], l);
    if (c != 0 || len[i] == len[j]) return c > 0;
    short k = max(len[i], len[j]) - l;
    strncpy(ss, (len[i]>len[j] ? s[i] : s[j]) + l, k);
    strcpy(ss+k, len[i]>len[j] ? s[j] : s[i]);
    return strcmp(len[i]>len[j] ? ss : s[j], len[i]>len[j] ? s[i] : ss) > 0;
}

void solve() {
    for (short i=0; i<n; ++i) cin >> s[i], a[i] = i, len[i] = strlen(s[i]);
    sort(a, a+n, cmp);
    for (short i=0; i<n; ++i) cout << s[a[i]];
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) solve();
    return 0;
}