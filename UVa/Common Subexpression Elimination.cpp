/**
 * UVa12219
 * 公共表达式消除
 */

#include <iostream>
#include <cstring>
#include <map>
using namespace std;

#define N 50010
#define M 300010
char s[M];

struct node {
    char s[5]; int l, r;
    bool operator< (const node& rhs) const {
        return l<rhs.l || (l==rhs.l && r<rhs.r) || (l==rhs.l && r==rhs.r && strcmp(s, rhs.s) < 0);
    }
};

node stack[N]; map<node, int> ids; int t; bool visit[N];

int build(int i=0) {
    int n = 0, m = ++t; node& p = stack[t]; p.l = p.r = 0;
    while (s[i] && s[i] != '(' && s[i] != ',' && s[i] != ')') p.s[n++] = s[i++];
    while (s[i] == ')') ++i;
    p.s[n] = 0;
    if (s[i] == '(') {
        node& l = stack[t+1];
        i = build(i+1) + 1;
        p.l = ids[l];
        node& r = stack[t+1];
        i = build(i);
        p.r = ids[r];
    }
    if (ids.count(p)) --t;
    else ids[p] = m;
    return i;
}

void print(int i = 1) {
    node& p = stack[i];
    if (visit[i]) {
        cout << i;
        return;
    }
    cout << p.s;
    if (p.l) {
        cout << '(';
        print(p.l);
        cout << ',';
        print(p.r);
        cout << ')';
    }
    visit[i] = true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short c; cin >> c;
    while (c--) {
        cin >> s;
        ids.clear();
        t = 0;
        build();
        memset(visit, 0, sizeof(visit));
        print();
        cout << endl;
    }
}