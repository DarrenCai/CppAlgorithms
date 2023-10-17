/**
 * UVa1401/LA3942
 * strcmp()函数
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 4005000
#define L 1005
char s[L]; int n, t, x, kase = 0;
struct node {int c[63], s;} trie[N];

int cvt(char c) {
    return c>96 ? c-61 : (c>64 ? c-55 : (c>47 ? c-48 : 62));
}

void solve() {
    long long ans = 0;
    memset(&(trie[0]), t=0, sizeof(node));
    while (n--) {
        cin >> s;
        ans += trie[0].s++;
        for (int i = x = 0; ;) {
            int c = cvt(s[i++]);
            int &k = trie[x].c[c];
            if (!k) memset(&(trie[k = ++t]), 0, sizeof(node));
            x = k;
            if (c == 62) break;
            ans += trie[x].s++ << 1;
        }
        ans += trie[x].s++;
    }
    cout << "Case " << ++kase << ": " << ans << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    while (cin>>n && n) solve();
    return 0;
}