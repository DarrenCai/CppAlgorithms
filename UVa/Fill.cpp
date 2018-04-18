/**
 * UVa10603
 * 倒水问题
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define min(a,b) (a<b ? a:b)

short water[8120602], a, b, c, d, a1, b1, c1, m, w; queue<int> q;

void bfs() {
    while (!q.empty()) {
        int t = q.front(); q.pop();
        a1 = t/40401; b1 = (t%40401)/201; c1 = t%201;
        if (a1) {
            short w1 = min(a1, b-b1);
            if (w1) {
                short a2 = a1-w1, b2 = b1+w1;
                int t1 = a2*40401 + b2*201 + c1;
                short w2 = water[t] + w1;
                if (t1!=c && (!water[t1] || water[t1]>w2)) {
                    if (a2<=d && (a2>m || (a2==m && w2<w))) {
                        m = a2; w = w2;
                    }
                    if (b2<=d && (b2>m || (b2==m && w2<w))) {
                        m = b2; w = w2;
                    }
                    water[t1] = w2;
                    q.push(t1);
                }
            }
            w1 = min(a1, c-c1);
            if (w1) {
                short a2 = a1-w1, c2 = c1+w1;
                int t1 = a2*40401 + b1*201 + c2;
                short w2 = water[t] + w1;
                if (t1!=c && (!water[t1] || water[t1]>w2)) {
                    if (a2<=d && (a2>m || (a2==m && w2<w))) {
                        m = a2; w = w2;
                    }
                    if (c2<=d && (c2>m || (c2==m && w2<w))) {
                        m = c2; w = w2;
                    }
                    water[t1] = w2;
                    q.push(t1);
                }
            }
        }
        if (b1) {
            short w1 = min(b1, a-a1);
            if (w1) {
                short a2 = a1+w1, b2 = b1-w1;
                int t1 = a2*40401 + b2*201 + c1;
                short w2 = water[t] + w1;
                if (t1!=c && (!water[t1] || water[t1]>w2)) {
                    if (a2<=d && (a2>m || (a2==m && w2<w))) {
                        m = a2; w = w2;
                    }
                    if (b2<=d && (b2>m || (b2==m && w2<w))) {
                        m = b2; w = w2;
                    }
                    water[t1] = w2;
                    q.push(t1);
                }
            }
            w1 = min(b1, c-c1);
            if (w1) {
                short b2 = b1-w1, c2 = c1+w1;
                int t1 = a1*40401 + b2*201 + c2;
                short w2 = water[t] + w1;
                if (t1!=c && (!water[t1] || water[t1]>w2)) {
                    if (b2<=d && (b2>m || (b2==m && w2<w))) {
                        m = b2; w = w2;
                    }
                    if (c2<=d && (c2>m || (c2==m && w2<w))) {
                        m = c2; w = w2;
                    }
                    water[t1] = w2;
                    q.push(t1);
                }
            }
        }
        if (c1) {
            short w1 = min(c1, a-a1);
            if (w1) {
                short a2 = a1+w1, c2 = c1-w1;
                int t1 = a2*40401 + b1*201 + c2;
                short w2 = water[t] + w1;
                if (t1!=c && (!water[t1] || water[t1]>w2)) {
                    if (a2<=d && (a2>m || (a2==m && w2<w))) {
                        m = a2; w = w2;
                    }
                    if (c2<=d && (c2>m || (c2==m && w2<w))) {
                        m = c2; w = w2;
                    }
                    water[t1] = w2;
                    q.push(t1);
                }
            }
            w1 = min(c1, b-b1);
            if (w1) {
                short b2 = b1+w1, c2 = c1-w1;
                int t1 = a1*40401 + b2*201 + c2;
                short w2 = water[t] + w1;
                if (t1!=c && (!water[t1] || water[t1]>w2)) {
                    if (b2<=d && (b2>m || (b2==m && w2<w))) {
                        m = b2; w = w2;
                    }
                    if (c2<=d && (c2>m || (c2==m && w2<w))) {
                        m = c2; w = w2;
                    }
                    water[t1] = w2;
                    q.push(t1);
                }
            }
        }
    }
}

int main()
{
    int n; cin>>n;
    while (n--) {
        cin >> a >> b >> c >> d;
        memset(water, 0, sizeof(water));
        m = 0; w = 0;
        if (c>m && c<=d) m = c;
        q.push(c);
        bfs();
        cout << w << ' ' << m << endl;
    }
    return 0;
}