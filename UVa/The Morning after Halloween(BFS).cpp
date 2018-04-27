/**
 * UVa1601
 * 万圣节后的早晨
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

int main()
{
    using namespace std;
    const char d[]={0, -16, 16, -1, 1}; short w, h, n;
    while (cin >> w >> h >> n && w) {
        char s[16][16];
        int a = 0, b = 0;
        for (char i = 0; i < h; ++i) {
            cin.ignore();
            for (char j = 0; j < w; ++j) {
                s[i][j] = cin.get();
                if (s[i][j] >= 'a' && s[i][j] < 'd')
                    a |= (i<<4 | j) << ((s[i][j]-'a') << 3);
                else if (s[i][j] >= 'A' && s[i][j] < 'D')
                    b |= (i<<4 | j) << ((s[i][j]-'A') << 3);
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
            static short dd[16777216]; memset(dd, 0, sizeof(dd)); dd[a] = 1;
            queue<int> q; q.push(a);
            while (!q.empty()) {
                int f = q.front(); q.pop();
                if (n==1) {
                    for (char k=m[f].size()-1; k>0; --k) {
                        int next = f + d[m[f][k]];
                        if (!dd[next]) {
                            dd[next] = dd[f] + 1;
                            if (next == b) goto OUT;
                            q.push(next);
                        }
                    }
                } else if (n==2) {
                    short f0 = f & 0xff, f1 = f>>8;
                    for (char k=m[f0].size()-1; k>=0; --k) {
                        short a0 = f0 + d[m[f0][k]];
                        for (char l=m[f1].size()-1; l>=0; --l) {
                            short a1 = f1 + d[m[f1][l]];
                            if (a0==a1 || (a0==f0 && a1==f1) || (a0==f1 && a1==f0)) continue;
                            int next = a1<<8 | a0;
                            if (!dd[next]) {
                                dd[next] = dd[f] + 1;
                                if (next == b) goto OUT;
                                q.push(next);
                            }
                        }
                    }
                } else {
                    short f0 = f & 0xff, f1 = f>>8 & 0xff, f2 = f>>16;
                    for (char k=m[f0].size()-1; k>=0; --k) {
                        short a0 = f0 + d[m[f0][k]];
                        for (char l=m[f1].size()-1; l>=0; --l) {
                            short a1 = f1 + d[m[f1][l]];
                            if (a0==a1 || (a0==f1 && a1==f0)) continue;
                            for (char p=m[f2].size()-1; p>=0; --p) {
                                short a2 = f2 + d[m[f2][p]];
                                if (a0==a2 || a1==a2 || (a0==f0 && a1==f1 && a2==f2) ||
                                    (a0==f2 && a2==f0) || (a1==f2 && a2==f1)) continue;
                                int next = a2<<16 | a1<<8 | a0;
                                if (!dd[next]) {
                                    dd[next] = dd[f] + 1;
                                    if (next == b) goto OUT;
                                    q.push(next);
                                }
                            }
                        }
                    }
                }
            }
            OUT: cout << dd[b] -1 << endl;
        }
    }
    return 0;
}