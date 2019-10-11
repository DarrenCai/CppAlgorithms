/**
 * UVa11925
 * 生成排列
 */

#include <iostream>
#include <deque>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short n, a[301];
    while (cin >> n && n) {
        deque<short> q; short s=0;
        for (short i=1; i<=n; ++i) cin >> a[i], q.push_back(i);
        for (short i=n; i>=1; --i)
            for (short j=0; j<n; ++j) if (q[j] == a[i]) {
                while (q[0] != a[i]) q.push_back(q[0]), q.pop_front(), cout << '2';
                q.pop_front();
                for (short k=j+1; k<n; ++k) q.push_back(q[0]), q.pop_front(), cout << "12";
                q.push_front(a[i]);
                break;
            }
        cout << endl;
    }
    return 0;
}