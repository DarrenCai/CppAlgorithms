/**
 * UVa652
 * 8数码问题的Ẵ解法
 * Ẵ算法的估价函数可表示为：f'(n) = g'(n) + h'(n) 这里，f'(n)是估价函数，g'(n)是起点到n的最短路径值，
 * h'(n)是n到目标的最断路经的启发值。由于这个f'(n)其实是无法预先知道的，所以我们用估价函数f(n)做近似，用
 * g(n)代替g'(n)，但要g(n)>=g'(n)（大多数情况都是满足的，可不考虑），h(n)代替h'(n)。如果要求最短路径，
 * 则一定要选择h(n)<=h'(n)；如果不一定求解最优解，而是要速度快，则可以选择h(n)>h'(n)。
 */

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

#define abs(x) (x>0 ? x : -(x))

unsigned char *s, s1[9], map[362880][9]={0}, x[362880], g[362880], h[362880]={0}, c[]="ulrd";
struct cmp {
    bool operator() (int a, int b) const {
        return g[a]+h[a] < g[b]+h[b] || (g[a]+h[a] == g[b]+h[b] && a<b);
    }
};
int parent[362880]; set<int> close; set<int, cmp> open;
const int p[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320}; int ha;

int hash() {
    int t = 0;
    for (char i=0; i<8; ++i) {
        char c = 0;
        for (char j=i+1; j<9; ++j)
            if (s1[j] < s1[i]) ++c;
        t += c*p[8-i];
    }
    return t;
}

char invN() {
    char t = 0;
    for (char i=0; i<8; ++i) {
        for (char j=i+1; s1[i]!='x' && j<9; ++j)
            if (s1[j]<s1[i] && s1[j]!='x') ++t;
    }
    return t;
}

char diff() {
    char t = 0;
    for (char i=0; i<9; ++i)
        if (s1[i]!='x' && s1[i]!='1'+i)
            t += abs((s1[i]-'1')/3 - i/3) + abs((s1[i]-'1')%3 - i%3);
    return t<<2; // 因为最大的曼哈顿距离是4，4*8也不过32。题目不求最优解，diff放大4倍可快速求解(实际上不放大也能AC,而且得出的是最短路径)
}

bool expand(char n, int t) {
    memcpy(s1, s, 9);
    s1[n] = s[x[t]];
    s1[x[t]] = s[n];
    int next = ::hash();
    x[next] = n;
    if (!close.count(next)) {
        if (!open.count(next)) {
            g[next] = g[t] + 1;
            parent[next] = t;
            if (next == 0)
                return false;
            if (!map[next][0])
                memcpy(map[next], s1, 9);
            if (!h[next])
                h[next] = diff();
            open.insert(next);
        } else if (g[t]+1<g[next]) {
            g[next] = g[t] + 1;
            parent[next] = t;
            open.erase(next);
            open.insert(next);
        }
    }
    return true;
}

void AStar() {
    while (!open.empty()) {
        int t = *open.begin(); open.erase(open.begin()); s = map[t];
        char r = x[t]/3, c = x[t]%3;
        if (r && !expand(3*(r-1)+c, t)) return;
        if (r<2 && !expand(3*(r+1)+c, t)) return;
        if (c && !expand(x[t]-1, t)) return;
        if (c<2 && !expand(x[t]+1, t)) return;
        close.insert(t);
    }
}

void print(int t) {
    if (parent[t] != ha) print(parent[t]);
    cout << c[(3+x[t]-x[parent[t]])>>1];
}

int main() {
    int n; cin>>n;
    while (n--) {
        char sp = 0;
        for (char i=0; i<9; ++i) {
            cin >> s1[i];
            if (s1[i] == 'x') sp = i;
        }
        ha = ::hash();
        if (ha==0) {
            cout << endl;
        } else if (invN()&1) {
            cout << "unsolvable" << endl;
        } else {
            if (!map[ha][0])
                memcpy(map[ha], s1, 9);
            x[ha] = sp;
            g[ha] = 0;
            open.insert(ha);
            AStar();
            print(0);
            cout << endl;
            open.clear();
            close.clear();
        }
        if (n) cout << endl;
    }
    return 0;
}