/**
 * UVa11572
 * 唯一的雪花
 */

#include <iostream>
#include <map>
using namespace std;

#define N 1000010
#define max(a, b) (a>b ? a:b)

int main()
{
    int t, n, ans; map<int, int> p;
    cin >> t;
    while (t--) {
        p.clear(); ans = 0; cin>>n;
        for (int i=0, prev=-1, s; i<n; ++i) {
            cin >> s;
            if (p.count(s) && p[s]>prev) {
                ans = max(ans, i-1-prev); prev = p[s];
            } else {
                ans = max(ans, i-prev);
            }
            p[s] = i;
        }
        cout << ans << endl;
    }
    return 0;
}