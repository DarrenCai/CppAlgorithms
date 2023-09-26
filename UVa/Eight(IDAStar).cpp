/**
 * UVa652
 * 8数码问题的IDẴ解法
 */

#include <iostream>
#include <cstring>
using namespace std;

#define abs(x) (x>0 ? x : -(x))

char s[9], path[60], depth;
const char m[4][2] = {{-1,0},{0,-1},{0,1},{1,0}}, d[]="ulrd";

bool isAns(const char *s) {
    for(char i=0; i<8; ++i)
        if(s[i] != '1'+i) return false;
    return true;
}

char invN() {
    char t = 0;
    for (char i=0; i<8; ++i) {
        for (char j=i+1; s[i]!='x' && j<9; ++j)
            if (s[j]<s[i] && s[j]!='x') ++t;
    }
    return t;
}

char diff(const char *s) {
    char t = 0;
    for (char i=0; i<9; ++i)
        if (s[i]!='x' && s[i]!='1'+i)
            t += abs((s[i]-'1')/3 - i/3) + abs((s[i]-'1')%3 - i%3);
    return t;
}

bool IDAStar(const char *s, char sp, char d=0, char pre=-1) {
    if (isAns(s)) {
        path[d] = '\0';
        cout << path << endl;
        return true;
    } else if (d<depth)
        for (char i=0; i<4; ++i) {
            if (pre+i == 3) continue;   // 重要剪支
            char r = sp/3+m[i][0], c = sp%3+m[i][1];
            if (r<0 || r>2 || c<0 || c>2) continue;
            path[d] = ::d[i];
            char n = 3*r + c;
            char s1[9]; memcpy(s1, s, 9);
            s1[n] = s[sp];
            s1[sp] = s[n];
            if (d+diff(s1)<depth && IDAStar(s1, n, d+1,i))   // 重要剪支
                return true;
        }
    return false;
}

int main() {
    int n; cin>>n;
    while (n--) {
        char sp = 0;
        for (char i=0; i<9; ++i) {
            cin >> s[i];
            if (s[i] == 'x') sp = i;
        }
        if (isAns(s)) {
            cout << endl;
        } else if (invN()&1) {
            cout << "unsolvable" << endl;
        } else {    //  不求最短路径时，IDẴ同样可以象Ẵ那样加快速度，放大估价函数，调大步长
            char d = diff(s);
            depth = d<<2;
            d>>=1; if (d<4) d=4;
            while(!IDAStar(s, sp)) depth += d;
        }
        if (n) cout << endl;
    }
    return 0;
}