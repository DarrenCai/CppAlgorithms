/**
 * UVa1346/LA3303
 * 歌曲
 */

#include <iostream>
#include <algorithm>
using namespace std;

#define N 70000
struct song {
    int id, l; double f;
    bool operator< (const song& rhs) const {
        return rhs.f * l < f * rhs.l;
    }
} songs[N];
int n, s;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n) {
        for (int i=0; i<n; ++i) cin >> songs[i].id >> songs[i].l >> songs[i].f;
        cin >> s;
        sort(songs, songs+n);
        cout << songs[s-1].id << endl;
    }
    return 0;
}
