/**
 * UVa10954
 * 全部相加
 */

#include <iostream>
#include <set>
using namespace std;

int main()
{
    int n;
    while (cin >> n && n) {
        multiset<int> s; int c, m=0;
        for (int i=0; i<n; ++i) cin >> c, s.insert(c);
        while (s.size() > 1) {
            int a = *s.begin(); s.erase(s.begin());
            int b = *s.begin(); s.erase(s.begin());
            m += a + b; s.insert(a+b);
        }
        cout << m << endl;
    }
    return 0;
}