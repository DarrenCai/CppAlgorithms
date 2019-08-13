/**
 * UVa12174
 * Shuffle的播放记录
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 100005
int pre[N]; bool ill[N];

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int d; cin >> d;
    while (d--) {
        int s, n, ans=0; cin >> s >> n;
        memset(pre, -1, sizeof(int)*(s+1));
        memset(ill, 0, s);
        for (int i=0; i<n; ++i) {
            int r; cin >> r;
            if (pre[r]>-1 && i-pre[r]<s){
                int a = i<s-1 ? i+1:(i-s+1)%s, b = pre[r]%s;
                if (a>b) {
                    while (b>=0) ill[b--] = true;
                    while (a<s) ill[a++] = true;
                } else while (a<=b) ill[a++] = true;
            }
            pre[r] = i;
        }
        for (int i=0, m=s>n?n:s; i<m; ++i) if (!ill[i]) ++ans;
        if (s>n && ans==n) ans += s-n;
        cout << ans << endl;
    }
    return 0;
}