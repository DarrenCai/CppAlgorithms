/**
 * UVa10881
 * 蚂蚁
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 10200
int x[N], d[N], L, T, n;
struct node {
    int p, x, t; bool d;
    bool operator< (const node& rhs) const {
        return x < rhs.x;
    }
} a[N]; 

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    for (int kase=1; kase<=t; ++kase) {
        cout << "Case #" << kase << ':' << endl;
        cin >> L >> T >> n;
        for (int i=0; i<n; ++i) {
            a[i].p = i; a[i].t = 0;
            cin >> a[i].x;
            char c; cin >> c;
            a[i].d = c=='R';
        }
        sort(a, a+n);
        for (int i=0, h=0; i<n; ++i) {
            int j = i;
            while (j>h && !a[j].d && a[j-1].d) {
                int t = abs(a[j].t-a[j-1].t);
                a[j-1].t < a[j].t ? (a[j-1].x += t, a[j-1].t +=t) : (a[j].x -= t, a[j].t += t); t = a[j].t;
                int s = a[j].x - a[j-1].x, c = s>>1, cc = c + (s&1);
                if (t+cc > T) {
                    t = T-t; a[j-1].x += t; a[j].x -= t; a[j-1].t = a[j].t = T; h = j+1;
                } else {
                    bool turn = a[j-1].x+cc >= a[j].x-cc;
                    a[j-1].x += c; a[j].x -= c; a[j-1].t = a[j].t = t+cc;
                    if (turn) {
                        a[j-1].d = 0; a[j].d = 1;
                        j-1==h || !a[j-2].d ? h = j : --j;
                    } else h = j+1;
                }
            }
        }
        for (int i=0; i<n; ++i) if (a[i].t < T) a[i].d ? a[i].x += T-a[i].t : a[i].x -= T-a[i].t;
        for (int i=0; i<n; ++i) {
            int t = x[a[i].p] = a[i].x;
            d[a[i].p] = (t<0 || t>L) ? 2 : (((i>0 && a[i-1].x==t) || (i+1<n && a[i+1].x==t)) ? 3 : a[i].d);
        }
        for (int i=0; i<n; ++i) {
            if (d[i] == 2) cout << "Fell off" << endl;
            else cout << x[i] << (d[i]==3 ? " Turning" : (d[i] ? " R" : " L")) << endl;
        }
        cout << endl;
    }
    return 0;
}