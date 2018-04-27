/**
 * UVa1601
 * 万圣节后的早晨
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>  // gcc编译器一定要加上,clang可以不要

const char d[]={0, -16, 16, -1, 1}; short dist[3][256];

short h(int s, short n) {
    short max = 0;
    for (char i=0; i<n; ++i) {
        max = std::max(max, dist[i][s & 0xff]); s>>=8;
    }
    return max;
}

int main()
{
    using namespace std;
    short w, h, n;
    while (cin >> w >> h >> n && w) {
        char s[16][16];
        int a = 0, b = 0, bp[3];
        for (char i = 0; i < h; ++i) {
            cin.ignore();
            for (char j = 0; j < w; ++j) {
                s[i][j] = cin.get();
                if (s[i][j] >= 'a' && s[i][j] < 'd')
                    a |= (i<<4 | j) << ((s[i][j]-'a') << 3);
                else if (s[i][j] >= 'A' && s[i][j] < 'D') {
                    char p = s[i][j]-'A';
                    short k = i<<4 | j;
                    dist[p][k] = 0;
                    bp[p] = k;
                    b |= k << (p << 3);
                }
            }
        }
        if (a == b) {
            cout << 0 << endl;
        } else {
            vector<char> m[256];
            for (char i = 0; i < h; ++i)
                for (char j = 0; j < w; ++j) {
                    if (s[i][j] != '#') {
                        short k = i<<4 | j; m[k].push_back(0);
                        if (i && s[i-1][j]!='#') m[k].push_back(1);
                        if (i<h-1 && s[i+1][j]!='#') m[k].push_back(2);
                        if (j && s[i][j-1]!='#') m[k].push_back(3);
                        if (j<w-1 && s[i][j+1]!='#') m[k].push_back(4);
                    }
                }
            for (char i=0; i<n; ++i) {
                bool visit[256] = {false}; queue<short> q; q.push(bp[i]); visit[bp[i]] = true;
                while (!q.empty()) {
                    short k = q.front(); q.pop();
                    for (char j=m[k].size()-1; j>0; --j) {
                        short next = k + d[m[k][j]];
                        if (!visit[next]) {
                            dist[i][next] = dist[i][k] + 1;
                            q.push(next); visit[next] = true;
                        }
                    }
                }
            }
            if (n==1) {
                cout << dist[0][a] << endl;
                continue;
            }
            static unsigned short g[16777216]; memset(g, 0xff, sizeof(g)); g[a] = 0;
            priority_queue<pair<short, int>, vector<pair<short, int> >, greater<pair<short, int> > > q;
            q.push(make_pair(::h(a, n), a));
            while (!q.empty()) {
                short f = q.top().first; int c = q.top().second; q.pop();
                if (c == b) {
                    cout << f << endl; break;
                }
                const short d = f - ::h(c, n);
                if (d > g[c]) continue;
                if (n==2) {
                    short c0 = c&0xff, c1 = c>>8;
                    for (char i=m[c0].size()-1; i>=0; --i) {
                        short a0 = c0 + ::d[m[c0][i]];
                        for (char j=m[c1].size()-1; j>=0; --j) {
                            short a1 = c1 + ::d[m[c1][j]];
                            if (a0==a1 || (a0==c0 && a1==c1) || (a0==c1 && a1==c0)) continue;
                            int next = a1<<8 | a0;
                            if (d+1 < g[next]) {
                                g[next] = d + 1;
                                q.push(make_pair(g[next]+::h(next, n), next));
                            }
                        }
                    }
                } else {
                    short c0 = c&0xff, c1 = c>>8 & 0xff, c2 = c>>16;
                    for (char i=m[c0].size()-1; i>=0; --i) {
                        short a0 = c0 + ::d[m[c0][i]];
                        for (char j=m[c1].size()-1; j>=0; --j) {
                            short a1 = c1 + ::d[m[c1][j]];
                            if (a0==a1 || (a0==c1 && a1==c0)) continue;
                            for (char k=m[c2].size()-1; k>=0; --k) {
                                short a2 = c2 + ::d[m[c2][k]];
                                if (a0==a2 || a1==a2 || (a0==c0 && a1==c1 && a2==c2) ||
                                    (a0==c2 && a2==c0) || (a1==c2 && a2==c1)) continue;
                                int next = a2<<16 | a1<<8 | a0;
                                if (d+1 < g[next]) {
                                    g[next] = d + 1;
                                    q.push(make_pair(g[next]+::h(next, n), next));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}