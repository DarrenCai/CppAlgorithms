/**
 * UVa12099
 * 书架
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define min(a, b) (a<b ? a:b)
#define max(a, b) (a>b ? a:b)
#define N 80
#define V 4000

struct book{
    short h, w;
    bool operator< (const book& rhs) const {
        return h>rhs.h;
    }
} books[N];

short w[N][N], b[N], d[N][V], r[N][V];

bool cmp(short i, short j) {
    return books[i].w > books[j].w;
}

void knapsack(short vm, short n) {
    memset(d, 0, sizeof(d)); memset(r, -1, sizeof(r));
    for (short i=0; i<n; ++i) {
        if (i > 0) memcpy(d[i], d[i-1], sizeof(d[i])), memcpy(r[i], r[i-1], sizeof(d[i]));
        for (short v=vm; v>=books[b[i]].w; --v)
            if (i==0) {
                d[i][v] = books[b[i]].w; r[i][v] = i;
            } else {
                short w1 = d[i-1][v], w2 = d[i-1][v-books[b[i]].w] + books[b[i]].w;
                if (w1 >= w2) {
                    d[i][v] = w1; r[i][v] = i-1;
                } else {
                    d[i][v] = w2; r[i][v] = i;
                }
            }
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short t; cin >> t;
    while (t--) {
        short n, wm=0; cin >> n;
        for (short i=0; i<n; ++i) cin >> books[i].h >> books[i].w, wm += books[i].w;
        sort(books, books+n);
        for (short i=0; i<n; ++i) for (short j=i+1; j<n; ++j)
            w[i][j] = j==i+1 ? books[i].w : w[i][j-1]+books[j-1].w;
        int ans = 1e8; short wi = (wm+2) / 3;
        for (short i=1; i<n-1; ++i) for (short j=i+1; j<n; ++j) {
            short w1 = w[0][i], w2 = w[i][j], w3 = wm-w1-w2; int h = books[0].h+books[i].h+books[j].h;
            if (h*w1 >= ans || h*wi >= ans) continue;
            if (w1>=w2 && w1>=w3) {
                ans = h*w1;
            } else {
                ans = min(h*max(max(w1, w2), w3), ans);
                if (w3 <= wi) {
                    if (w1 >= w2) {
                        ans = min(h*max(w1, w3), ans);
                    } else {
                        // 2给1凑(w1+w2)/2 得一可能最小值
                        short v = (w1+w2)/2;
                        if (h*max(max(v, w1+w2-v), w3) < ans && j>i+1) {
                            short vt, s = 0; for (short k=i+1; k<j; ++k) b[s++] = k;
                            if (v >= books[i].w) {
                                knapsack(vt = v-books[i].w, s);
                                ans = min(h*max(w1+w2-books[i].w-d[s-1][vt], w3), ans);
                            }
                            if (h*max(max(v, w1+w2-v), w3) < ans) {
                                knapsack(vt = v-w1, s);
                                ans = min(h*max(w2-d[s-1][vt], w3), ans);
                            }
                        }
                    }
                } else {
                    // 必定w1 < w3
                    if (wi >= books[j].w) {
                        // 3采取01背包凑wi，1、2尽量均分得一可能最小值
                        short s = 0; for (short k=j+1; k<n; ++k) b[s++] = k; sort(b, b+s, cmp);
                        short vt = wi-books[j].w; knapsack(vt, s);
                        short v3 = d[s-1][vt]+books[j].w, v = (wm-v3)/2;
                        if (w1 >= v) {
                            ans = min(h*max(max(w1, wm-v3-w1), v3), ans);
                        } else if (h*max(wm-v3-v, v3) < ans) {
                            bool used[N] = {false};
                            for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                            }
                            short s1 = 0; for (short k=j+1; k<n; ++k) if (!used[k]) b[s1++] = k;
                            for (short k=i+1; k<j; ++k) b[s1++] = k;
                            knapsack(vt=v-w1, s1); ans = min(h*max(wm-v3-w1-d[s1-1][vt], v3), ans);
                            if (v >= books[i].w && h*max(wm-v3-v, v3) < ans) {
                                knapsack(vt=v-books[i].w, s1);
                                ans = min(h*max(wm-v3-books[i].w-d[s1-1][vt], v3), ans);
                            }
                        }
                    }
                    if (wi >= books[i].w && h*wi < ans && (j>i+1 || n>j+1)) {
                        // 2、3放一起给2用采取01背包凑wi，1、3尽量均分得一可能最小值
                        short s = 0; for (short k=i+1; k<j; ++k) b[s++] = k; for (short k=j+1; k<n; ++k) b[s++] = k;
                        sort(b, b+s, cmp); short vt = wi - books[i].w; knapsack(vt, s);
                        short v1=w1, v2 = d[s-1][vt]+books[i].w, v=(wm-v2)/2;
                        if (h*max(v2, wm-v2-v) < ans) {
                            bool used[N] = {false};
                            for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                            }
                            for (short k=i+1; k<j; ++k) if (!used[k]) v1 += books[k].w;
                            if (v1 < wm-v2-v1) {
                                if (h*max(v2, wm-v2-v) < ans) {
                                    s = 0; for (short k=j+1; k<n; ++k) if (!used[k]) b[s++] = k;
                                    if (s > 0) {
                                        knapsack(vt = v-v1, s); ans = min(h*max(v2, wm-v2-v1-d[s-1][vt]), ans);
                                        if (v >= books[j].w && h*max(v2, wm-v2-v) < ans) {
                                            knapsack(vt = v-books[j].w, s);
                                            ans = min(h*max(wm-v2-d[s-1][vt]-books[j].w, v2), ans);
                                        }
                                    } else ans = min(h*max(v2, books[j].w), ans);
                                }
                            } else ans = min(h*max(v1, v2), ans);
                        }
                        if (h*wi < ans) {
                            // 2全自用（多出给1）采取01背包凑wi，不足wi继续拿3凑，1、3尽量均分得一可能最小值
                            bool used[N] = {false}; v1=w1; v2 = w2; s = 0; for (short k=i+1; k<j; ++k) b[s++] = k;
                            if (s > 0) {
                                knapsack(vt = wi-books[i].w, s);
                                for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                    while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                                }
                                v2 = books[i].w + d[s-1][vt];
                                for (short k=i+1; k<j; ++k) if (!used[k]) v1 += books[k].w;
                            }
                            s = 0; for (short k=j+1; k<n; ++k) b[s++] = k; sort(b, b+s, cmp);
                            if (v2 < wi && s > 0) {
                                knapsack(vt = wi-v2, s); v2 += d[s-1][vt];
                                for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                    while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                                }
                            }
                            if (v1 < wm-v1-v2) {
                                v = (wm-v2)/2;
                                if (h*max(v2, wm-v2-v) < ans) {
                                    s = 0; for (short k=j+1; k<n; ++k) if (!used[k]) b[s++] = k;
                                    if (s > 0) {
                                        knapsack(vt = v-v1, s); ans = min(h*max(wm-v2-v1-d[s-1][vt], v2), ans);
                                        if (v >= books[j].w && h*max(v2, wm-v2-v) < ans) {
                                            knapsack(vt = v-books[j].w, s);
                                            ans = min(h*max(wm-v2-books[j].w-d[s-1][vt], v2), ans);
                                        }
                                    } else ans = min(h*max(wm-v1-v2, v2), ans);
                                }
                            } else ans = min(h*max(v1, v2), ans);
                        }
                    }
                    if (w1 < wi && h*wi < ans) {
                        if (j > i+1) {
                            // 优先把2给1用采取01背包凑wi，不足wi继续拿3凑，2、3尽量均分得一可能最小值
                            bool used[N] = {false}; short s = 0; for (short k=i+1; k<j; ++k) b[s++] = k;
                            short v1 = w1, v2 = w2, vt = wi-w1; knapsack(vt, s); v1 += d[s-1][vt]; v2 -= d[s-1][vt];
                            if (v1 < wi && n > j+1) {
                                short s = 0; for (short k=j+1; k<n; ++k) b[s++] = k; sort(b, b+s, cmp);
                                knapsack(vt = wi-v1, s); v1 += d[s-1][vt];
                                for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                    while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                                }
                            }
                            if (v2 < wm-v1-v2) {
                                short v = (wm-v1)/2;
                                if (h*max(v1, wm-v1-v) < ans) {
                                    s = 0; for (short k=j+1; k<n; ++k) if (!used[k]) b[s++] = k;
                                    if (s > 0) {
                                        knapsack(vt = v-v2, s); ans = min(h*max(wm-v1-v2-d[s-1][vt], v1), ans);
                                        if (v >= books[j].w && h*max(v1, wm-v1-v) < ans) {
                                            knapsack(vt = v-books[j].w, s);
                                            ans = min(h*max(wm-v1-books[j].w-d[s-1][vt], v1), ans);
                                        }
                                    } else ans = min(h*max(wm-v1-v2, v2), ans);
                                }
                            } else ans = min(h*max(v1, v2), ans);
                        }
                        if (h*wi < ans && n > j+1) {
                            // 优先把3给1用采取01背包凑wi，不足wi继续拿2凑，2、3尽量均分得一可能最小值
                            bool used[N] = {false}; short s = 0; for (short k=j+1; k<n; ++k) b[s++] = k; sort(b, b+s, cmp);
                            short v1 = w1, v2 = w2, v3 = w3, vt = wi-w1; knapsack(vt, s); v1 += d[s-1][vt]; v3 -= d[s-1][vt];
                            for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                            }
                            if (v1 < wi && j > i+1) {
                                short s = 0; for (short k=i+1; k<j; ++k) b[s++] = k;
                                knapsack(vt = wi-v1, s); v1 += d[s-1][vt]; v2 -= d[s-1][vt];
                            }
                            if (v2 < v3) {
                                short v = (wm-v1)/2;
                                if (h*max(v1, wm-v1-v) < ans) {
                                    s = 0; for (short k=j+1; k<n; ++k) if (!used[k]) b[s++] = k;
                                    if (s > 0) {
                                        knapsack(vt = v-v2, s); ans = min(h*max(wm-v1-v2-d[s-1][vt], v1), ans);
                                        if (v >= books[j].w && h*max(v1, wm-v1-v) < ans) {
                                            knapsack(vt = v-books[j].w, s);
                                            ans = min(h*max(wm-v1-books[j].w-d[s-1][vt], v1), ans);
                                        }
                                    } else ans = min(h*max(v1, v3), ans);
                                }
                            } else ans = min(h*max(v1, v2), ans);
                        }
                        if (h*wi < ans && j > i+1 && n > j+1) {
                            // 把2、3全部给1用采取01背包凑wi，2、3尽量均分得一可能最小值
                            bool used[N] = {false}; short s = 0, v1 = w1, v2 = books[i].w, v3 = books[j].w, vt = wi-w1;
                            for (short k=i+1; k<j; ++k) b[s++] = k; for (short k=j+1; k<n; ++k) b[s++] = k;
                            sort(b, b+s, cmp); knapsack(vt, s);
                            for (short k=s-1, w=d[k][vt]; k>=0 && r[k][w] > -1; w-=books[b[k]].w, --k) {
                                while (r[k][w] != k) k = r[k][w]; used[b[k]] = true;
                            }
                            v1 += d[s-1][vt];
                            for (short k=i+1; k<j; ++k) if (!used[k]) v2 += books[k].w;
                            for (short k=j+1; k<n; ++k) if (!used[k]) v3 += books[k].w;
                            if (v2 < v3) {
                                short v = (wm-v1)/2;
                                if (h*max(v1, wm-v1-v) < ans) {
                                    s = 0; for (short k=j+1; k<n; ++k) if (!used[k]) b[s++] = k;
                                    if (s > 0) {
                                        knapsack(vt = v-v2, s); ans = min(h*max(wm-v1-v2-d[s-1][vt], v1), ans);
                                        if (v >= books[j].w && h*max(v1, wm-v1-v) < ans) {
                                            knapsack(vt = v-books[j].w, s);
                                            ans = min(h*max(wm-v1-books[j].w-d[s-1][vt], v1), ans);
                                        }
                                    } else ans = min(h*max(v1, v3), ans);
                                }
                            } else ans = min(h*max(v1, v2), ans);
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}