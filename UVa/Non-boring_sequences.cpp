/**
 * UVa12174
 * Shuffle的播放记录
 */

#include <iostream>
#include <cstring>
#include <map>
using namespace std;

#define N 200005
int pre[N], nex[N], a[N];

bool bored(int s, int n) {
    if (n < 2) return false;
    for (int i=0, m=(n+1)>>1; i<m; ++i) {
        int j = i+s;
        if (pre[j]<s && (nex[j]<0 || nex[j]>=s+n))
            return bored(s, i) || bored(j+1, n-i-1);
        j = s + n-i-1;
        if (pre[j]<s && (nex[j]<0 || nex[j]>=s+n))
            return bored(s, n-i-1) || bored(j+1, i);
    }
    return true;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int d; cin >> d;
    while (d--) {
        bool boring = false; int n; cin >> n; map<int, int> p;
        memset(pre, -1, n*sizeof(int)); memset(nex, -1, n*sizeof(int));
        for (int i=0; i<n; ++i) {
            cin >> a[i];
            if (i && a[i]==a[i-1]) boring=true;
            if (boring) continue;
            if (p.count(a[i])) pre[i] = p[a[i]], nex[pre[i]] = i;
            p[a[i]] = i;
        }
        if (!boring) boring = bored(0, n);
        cout << (boring ? "boring" : "non-boring") << endl;
    }
    return 0;
}