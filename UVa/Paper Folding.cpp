/**
 * UVa177
 * 折纸痕
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define N 13+1
#define M 250
string s[N]; char a[M][M]; short n;

void gen() {
    s[0] = "R";
    for (short i=1; i<N; ++i) {
        string& ss = s[i]; ss = s[i-1] + s[i-1];
        for (short k=s[i-1].length(), j=k-1; j>=0; --j, ++k) {
            if (ss[j] == 'L') ss[k] = 'D';
            else if (ss[j] == 'R') ss[k] = 'U';
            else if (ss[j] == 'U') ss[k] = 'L';
            else ss[k] = 'R';
        }
    }
}

void print(const string& ss) {
    short x=0, y=0, minX=0, minY=0, maxC[M]={0}, maxR=0, i, l;
    for (i=1, l=ss.length(); i<l; ++i) {
        if (ss[i] == 'L' || ss[i] == 'R') {
            ss[i] == 'R' ? ++x : --x;
            if (ss[i-1] == 'U') --y; 
        } else {
            ss[i-1] == 'R' ? ++x : --x;
            if (ss[i] == 'D') ++y;
        }
        if (x < minX) minX = x;
        if (y < minY) minY = y;
    }
    for (x=0, y=0, i=1, l=ss.length(); i<l; ++i) {
        if (ss[i] == 'L' || ss[i] == 'R') {
            ss[i] == 'R' ? ++x : --x;
            if (ss[i-1] == 'U') --y; 
        } else {
            ss[i-1] == 'R' ? ++x : --x;
            if (ss[i] == 'D') ++y;
        }
        short rx = x - minX, ry = y - minY;
        if (rx > maxC[ry]) maxC[ry] = rx;
        if (ry > maxR) maxR = ry;
    }
    for (i=0; i<=maxR; ++i) {
        memset(a[i], ' ', maxC[i]);
        a[i][maxC[i]+1] = '\0';
    }
    for (x=0, y=0, i=1, l=ss.length(); i<l; ++i) {
        if (ss[i] == 'L' || ss[i] == 'R') {
            ss[i] == 'R' ? ++x : --x;
            if (ss[i-1] == 'U') --y; 
        } else {
            ss[i-1] == 'R' ? ++x : --x;
            if (ss[i] == 'D') ++y;
        }
        short rx = x - minX, ry = y - minY;
        a[ry][rx] = ss[i] == 'L' || ss[i] == 'R' ? '_' : '|';
    }
    a[-minY][-minX] = '_';
    for (i=0; i<=maxR; ++i) cout << a[i] << endl;
    cout << '^' << endl;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    gen();
    while (cin >> n && n) print(s[n]);
    return 0;
}