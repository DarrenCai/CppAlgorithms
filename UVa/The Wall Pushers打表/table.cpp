#include <iostream>
#include <algorithm>

using namespace std;

#define dis(a, b) (a>b ? a-b:b-a)

struct cell {
    short r, c;
};

int main() {
    freopen("table.txt", "w", stdout);
    cout << '{';
    for (short r=0; r<4; ++r) {
        cout << '{';
        for (short c=0; c<6; ++c) {
            cout << '{';
            cell s[] = {{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{1,0},{1,5},{2,0},{2,5},{3,0},{3,1},{3,2},{3,3},{3,4},{3,5}};
            sort(s, s+16, [&r, &c](cell &a, cell &b){
                short da = dis(a.r, r) + dis(a.c, c), db = dis(b.r, r) + dis(b.c, c);
                if (da < db) return true;
                if (da == db) return a.r < b.r || (a.r==b.r && a.c<b.c);
                return false;
            });
            for (short i=0; i<16; ++i) {
                if (i) cout << ','; cout << '{' << s[i].r << ',' << s[i].c << '}';
            }
            cout << '}'; if (c<5) cout << ',' << endl;
        }
        cout << '}'; if (r<3) cout << ',' << endl;
    }
    cout << '}' << endl;
    return 0;
}