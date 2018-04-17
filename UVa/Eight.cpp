/**
 * UVa652
 * 8数码问题
 */

#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

string path[362880]={""}; bool visit[362880] = {false}; queue<int> q;
const int p[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320}; int h;
char *s, s1[]={1, 2, 3, 4, 5, 6, 7, 8, 9}, map[362880][9], x[362880];

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

void expand(char n, char d) {
    memcpy(s1, s, 9);
    s1[n] = s[x[h]];
    s1[x[h]] = s[n];
    int next = ::hash();
    if (!visit[next]) {
        path[next] = d + path[h];
        memcpy(map[next], s1, 9);
        x[next] = n;
        q.push(next);
        visit[next] = true;
    }
}

void bfs() {
    while (!q.empty()) {
        h = q.front();
        q.pop();
        s = map[h];
        char r = x[h]/3, c=x[h]%3;
        if (r) expand(3*(r-1)+c, 'd');
        if (r<2) expand(3*(r+1)+c, 'u');
        if (c) expand(x[h]-1, 'r');
        if (c<2) expand(x[h]+1, 'l');
    }
}

int main()
{
    q.push(0);
    visit[0] = 1;
    memcpy(map[0], s1, 9);
    x[0] = 8;
    bfs();
    int n; cin>>n;
    while (n--) {
        for (char i=0; i<9; ++i)
            cin >> s1[i];
        h = ::hash();
        if (h==0) {
            cout << endl;
        } else if (path[h].length()) {
            cout << path[h] << endl;
        } else {
            cout << "unsolvable" << endl;
        }
        if (n) cout << endl;
    }
    return 0;
}