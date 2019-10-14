/**
 * UVa1614
 * 奇怪的股市
 */

#include <iostream>
#include <set>
using namespace std;

#define N 100010
int a[N], n; long long sum;

void solve() {
    if (sum & 1) {
        cout << "No" << endl;
    } else {
        multiset<int> s, ans; sum >>= 1;
        for (int i=0; i<n; ++i) {
            if (a[i] > sum) {
                cout << "No" << endl;
                return;
            } else if (a[i] == sum) {
                s.clear(); ans.insert(a[i]);
                break;
            }
            s.insert(a[i]);
        }
        while (!s.empty()) {
            if (*s.begin() > sum) {
                ans.clear();
                break;
            }
            multiset<int>::iterator it = s.find(sum);
            if (it != s.end()) {
                ans.insert(*it);
                break;
            }
            if (*s.rbegin() > sum) {
                s.erase(*s.rbegin());
            } else {
                ans.insert(*s.rbegin());
                sum -= *s.rbegin();
                s.erase(s.find(*s.rbegin()));
            }
        }
        if (ans.empty()) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
            for (int i=0; i<n; ++i) {
                if (i) cout << ' ';
                multiset<int>::iterator it = ans.find(a[i]);
                if (it != ans.end()) {
                    cout << 1;
                    ans.erase(it);
                } else {
                    cout << -1;
                }
            }
            cout << endl;
        }
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        sum = 0;
        for (int i=0; i<n; ++i) cin >> a[i], sum+=a[i];
        solve();
    }
    return 0;
}