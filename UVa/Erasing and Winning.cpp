/**
 * UVa11491
 * 奖品的价值
 */

#include <iostream>
#include <set>
using namespace std;

#define N 100005
char s[N];

struct cmp {
    bool operator() (int i, int j) const {
        if (s[i] == s[j]) return i<j;
        return s[i] > s[j];
    }
};
set<int, cmp> a;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int n, d;
    while (cin >> n >> d && n) {
        int pre=0, l=d+1; cin >> s; for (int i=0; i<=d; ++i) a.insert(i);
        for (int i=n-d; i>0; --i) {
            int v = *a.begin(); a.erase(a.begin());
            while (pre < v) a.erase(pre++); pre = v+1;
            cout << s[v];
            int j=l; l=n-i+2; while (j<l) a.insert(j++);
        }
        a.clear();
        cout << endl;
    }
    return 0;
}