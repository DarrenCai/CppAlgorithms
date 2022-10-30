#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <set>
using namespace std;

// #define N 15
#define N 100
short x0[N+1], x1[N+1];

void generate() {
    short xa = rand()%(N-5)+1, ya = rand()%(N-5)+1, yb = rand()%(N-ya) + ya+1;
    x0[ya] = xa; x1[ya] = rand()%(N-xa) + xa+1;
    for (short i=ya+1; i<yb; ++i) {
        x0[i] = rand()%(x1[i-1]-x0[i-1]) + x0[i-1];
        x1[i] = x1[i-1]==N ? N : rand()%(N-x1[i-1]) + x1[i-1];
    }
    x0[yb] = x0[yb-1]; x1[yb] = x1[yb-1];
    cout << ya << ' ' << xa << endl << ya << ' ' << x1[ya] << endl;
    short x = x1[ya], y = ya, r0 = ya, r1 = ya+1;
    while (x!=xa || y!=ya) {
        if (r0 < r1) {
            if (x < x1[r1]) {
                cout << r1 << ' ' << x << endl << r1 << ' ' << x1[r1] << endl;
                x = x1[r1]; y = r1;
                if (y == yb) {
                    r0 = r1; r1 = r0-1;
                } else r0 = r1++;
            } else {
                y = r1;
                if (y == yb) {
                    cout << y << ' ' << x << endl << y << ' ' << x0[y] << endl;
                    x = x0[y];
                    r0 = r1--;
                } else r0 = r1++;
            }
        } else if (x > x0[r1]) {
            cout << y << ' ' << x << endl << y << ' ' << x0[r1] << endl;
            x = x0[r1]; y = r1;
            if (y > ya) r0 = r1--;
        } else {
            y = r1;
            if (y > ya) r0 = r1--;
        }
    }
    cout << "0 0" << endl << endl;
}

int main() {
    freopen("in.txt", "w", stdout);
    srand(time(NULL));
    for (int i=0; i<600; ++i) generate();
    cout << "0 0" << endl;
    return 0;
}