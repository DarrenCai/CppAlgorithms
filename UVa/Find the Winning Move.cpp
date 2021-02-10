/**
 * UVa10111
 * #字棋游戏
 */

#include <iostream>
using namespace std;

char s[5]; short cnt[65536], t; int x, y, w[] = {15, 240, 3840, 61440, 4369, 8738, 17476, 34952, 33825, 4680};

int solve() {
    for (short i=0; i<16; ++i) {
        if (!(x&(1<<i)) && !(y&(1<<i))) {
            x ^= 1<<i;
            for (short j=0; j<10; ++j) if ((x&w[j]) == w[j]) return i;
            if (t > 1) {
                bool win = true;
                for (short a=0; win && a<16; ++a) if (!(x&(1<<a)) && !(y&(1<<a))) {
                    y ^= 1<<a;
                    bool ok = false;
                    for (short j=0; !ok && j<10; ++j) if (!(w[j]&y) && cnt[w[j]&x] == 3) ok = true;
                    if (!ok) win = false;
                    y ^= 1<<a;
                }
                if (win) return i;
            }
            if (t > 2) {
                bool win = true;
                for (short a=0; win && a<16; ++a) if (!(x&(1<<a)) && !(y&(1<<a))) {
                    y ^= 1<<a;
                    for (short b=a+1; win && b<16; ++b) if (!(x&(1<<b)) && !(y&(1<<b))) {
                        y ^= 1<<b;
                        bool ok = false;
                        for (short j=0; !ok && j<10; ++j) if (!(w[j]&y) && cnt[w[j]&x] == 2) ok = true;
                        if (!ok) win = false;
                        y ^= 1<<b;
                    }
                    y ^= 1<<a;
                }
                if (win) return i;
            }
            if (t > 3) {
                bool win = true;
                for (short a=0; win && a<16; ++a) if (!(x&(1<<a)) && !(y&(1<<a))) {
                    y ^= 1<<a;
                    for (short b=a+1; win && b<16; ++b) if (!(x&(1<<b)) && !(y&(1<<b))) {
                        y ^= 1<<b;
                        for (short c=b+1; win && c<16; ++c) if (!(x&(1<<c)) && !(y&(1<<c))) {
                            y ^= 1<<c;
                            bool ok = false;
                            for (short j=0; !ok && j<10; ++j) if (!(w[j]&y) && cnt[w[j]&x] == 1) ok = true;
                            if (!ok) win = false;
                            y ^= 1<<c;
                        }
                        y ^= 1<<b;
                    }
                    y ^= 1<<a;
                }
                if (win) return i;
            }
            if (t > 4) {
                bool win = true;
                for (short a=0; win && a<16; ++a) if (!(x&(1<<a)) && !(y&(1<<a))) {
                    y ^= 1<<a;
                    for (short b=a+1; win && b<16; ++b) if (!(x&(1<<b)) && !(y&(1<<b))) {
                        y ^= 1<<b;
                        for (short c=b+1; win && c<16; ++c) if (!(x&(1<<c)) && !(y&(1<<c))) {
                            y ^= 1<<c;
                            for (short d=c+1; win && d<16; ++d) if (!(x&(1<<d)) && !(y&(1<<d))) {
                                y ^= 1<<d;
                                bool ok = false;
                                for (short j=0; !ok && j<10; ++j) if (!(w[j]&y) && (w[j]&x) == w[j]) ok = true;
                                if (!ok) win = false;
                                y ^= 1<<d;
                            }
                            y ^= 1<<c;
                        }
                        y ^= 1<<b;
                    }
                    y ^= 1<<a;
                }
                if (win) return i;
            }
            x ^= 1<<i;
        }
    }
    return -1;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    for (short a=0; a<16; ++a) {
        cnt[1<<a] = 1;
        for (short b=a+1; b<16; ++b) {
            cnt[1<<a | 1<<b] = 2;
            for (short c=b+1; c<16; ++c) {
                cnt[1<<a | 1<<b | 1<<c] = 3;
                for (short d=c+1; d<16; ++d) cnt[1<<a | 1<<b | 1<<c | 1<<d] = 4;
            }
        }
    }
    while (cin>>s && s[0]!='$') {
        x = y = 0; t = 16;
        for (short i=0; i<4; ++i) {
            cin >> s;
            for (short j=0; j<4; ++j) {
                if (s[j] == 'x') --t, x |= 1<<((i<<2)+j);
                else if (s[j] == 'o') --t, y |= 1<<((i<<2)+j);
            }
        }
        t >>= 1;
        int ans = solve();
        if (ans < 0) {
            cout << "#####" << endl;
        } else {
            cout << '(' << (ans>>2) << ',' << (ans&3) << ')' << endl;
        }
    }
    return 0;
}