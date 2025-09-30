/**
 * UVa10838
 * 迷你象棋
 */

#include <iostream>
using namespace std;

int minimax(unsigned int s, int p) {
    int a = 0, b = 16;
    for (int i=0, k=0; i<4; ++i) for(int j=0; j<4; ++j, k += 2) {
        int x = s>>k & 3;
        if (x == p) {
            if (p && i > 0) {
                if ((s>>k-8 & 3) == 2) {
                    if (i == 1) return 1;
                    int v = minimax(s + (255<<k-8), 0);
                    v & 1 ? a = max(a, v+1) : b = min(b, v+1);
                }
                if (j>0 && (s>>k-10 & 3) == 0) {
                    if (i == 1) return 1;
                    int v = minimax(s + (1025<<k-10), 0);
                    v & 1 ? a = max(a, v+1) : b = min(b, v+1);
                }
                if (j<3 && (s>>k-6 & 3) == 0) {
                    if (i == 1) return 1;
                    int v = minimax(s + (65<<k-6), 0);
                    v & 1 ? a = max(a, v+1) : b = min(b, v+1);
                }
            } else if (!p && i<3) {
                if ((s>>k+8 & 3) == 2) {
                    if (i == 2) return 1;
                    int v = minimax(s - (510<<k), 1);
                    v & 1 ? a = max(a, v+1) : b = min(b, v+1);
                }
                if (j>0 && (s>>k+6 & 3) == 1) {
                    if (i == 2) return 1;
                    int v = minimax(s - (62<<k), 1);
                    v & 1 ? a = max(a, v+1) : b = min(b, v+1);
                }
                if (j<3 && (s>>k+10 & 3) == 1) {
                    if (i == 2) return 1;
                    int v = minimax(s - (1022<<k), 1);
                    v & 1 ? a = max(a, v+1) : b = min(b, v+1);
                }
            }
        }
    }
    return b&1 ? b : a;
}

void solve() {
    unsigned int s = 0;
    for (int i=0, k=0; i<4; ++i) for(int j=0; j<4; ++j, k += 2) {
        char ch; cin >> ch;
        s |= (ch == 'P' ? 1 : (ch == 'p' ? 0 : 2)) << k;
    }
    int v = minimax(s, 1);
    v&1 ? cout << "white (" << v << ')' << endl : cout << "black (" << v << ')' << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}