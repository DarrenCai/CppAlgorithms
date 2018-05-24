/**
 * UVa1374
 * 快速幂计算
 */

#include <iostream>

#define abs(x) (x>0 ? x : -(x))

short n, maxd, s[50];

bool IDDFS(short cur = 0) {
    if (cur == maxd) {
        if (s[cur] == n) return true;
    } else {
        short next=cur+1, m=0;
        for (short i=0; i<=cur; ++i) if (s[i] > m) m = s[i];
        if (m << (maxd-cur) < n) return false;
        for (short i=cur; i>=0; --i) {
            s[next] = s[cur] + s[i];
            if (IDDFS(next)) return true;
            s[next] = abs(s[cur] - s[i]);
            if (IDDFS(next)) return true;
        }
    }
    return false;
}

int main()
{
    s[0] = 1;
    using namespace std;
    while (cin>>n && n) {
        if (n==1) {
            cout << 0 << endl;
        } else {
            for (maxd = 1; !IDDFS(); ++maxd);
            cout << maxd << endl;
        }
    }
    return 0;
}