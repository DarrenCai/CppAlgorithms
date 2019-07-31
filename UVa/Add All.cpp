/**
 * UVa10954
 * 全部相加
 */

#include <iostream>
#include <functional>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    while (cin >> n && n) {
        priority_queue<int, vector<int>, greater<int> > q; int c, m=0;
        for (int i=0; i<n; ++i) cin >> c, q.push(c);
        while (q.size() > 1) {
            int a = q.top(); q.pop();
            int b = q.top(); q.pop();
            m += a + b; q.push(a+b);
        }
        cout << m << endl;
    }
    return 0;
}