/**
 * UVa11212
 * 编辑书稿
 */

#include <iostream>
#include <queue>
#include <set>
using namespace std;

short n, k = 0; char s[9];
const int p[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

char idx(char a) {
    for (char i=0; i<n; ++i)
        if (s[i] == a) return i;
    return 0;
}

int hash(const char *s) {
    int t = 0;
    for (char i=0; i<n-1; ++i) {
        char c = 0;
        for (char j=i+1; j<n; ++j)
            if (s[j] < s[i]) ++c;
        t += c*p[n-1-i];
    }
    return t;
}

void deHash(int h) {
    bool visit[9] = {false};
    for (char i=n-1; i>0; --i) {
        char t = h / p[i];
        h = h % p[i];
        for (char j=0; j<=t; ++j)
            if (visit[j]) ++ t;
        s[n-1-i] = '1' + t;
        visit[t] = true;
    }
    for (char i=0; i<n; ++i)
        if (!visit[i]) {
            s[n-1] = '1' + i;
            break;
        }
}

void cp(char* s1, char i, char l, char j) {
    for (char k=0; k<i; ++k) s1[k] = s[k];
    for (char k=i+l; k<=j; ++k) s1[k-l] = s[k];
    for (char k=i; k<i+l; ++k) s1[j+1+k-i-l] = s[k];
    for (char k=j+1; k<n; ++k) s1[k] = s[k];
}

short bfs() {
    int h = ::hash(s);
    if (h == 0) return 0;
    queue<int> q; set<int> visit;
    q.push(h); visit.insert(h);
    short step = 0;
    while (!q.empty()) {
        for (int ii=0, t=q.size(); ii<t; ++ii) {
            h = q.front(); q.pop();
            deHash(h);
            for (char i=0; i<n-1; ++i) {
                for (char l=1; l<n-i; ++l) {
                    if ((!i || s[i] != s[i-1] + 1) && s[i+l] != s[i+l-1] + 1) {
                        char a = idx(s[i]-1), b = idx(s[i+l-1]+1)-1;
                        if (a<i+l && b<i+l) {
                            for (char j=i+l; j<n; ++j)
                                if (j==n-1 || s[j+1] != s[j] + 1) {
                                    char s1[9]; cp(s1, i, l, j); h = ::hash(s1);
                                    if (!visit.count(h)) {
                                        if (h == 0) return step+1;
                                        q.push(h); visit.insert(h);
                                    }
                                }
                        } else {
                            if (a>=i+l) {
                                char s1[9]; cp(s1, i, l, a); h = ::hash(s1);
                                if (!visit.count(h)) {
                                    if (h == 0) return step+1;
                                    q.push(h); visit.insert(h);
                                }
                            }
                            if (b>=i+l) {
                                char s1[9]; cp(s1, i, l, b); h = ::hash(s1);
                                if (!visit.count(h)) {
                                    if (h == 0) return step+1;
                                    q.push(h); visit.insert(h);
                                }
                            }
                        }
                    }
                }
            }
        }
        ++ step;
    }
    return step;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin>>n && n) {
        for (short i=0; i<n; ++i)
            cin >> s[i];
        cout << "Case " << ++k << ": " << bfs() << endl;
    }
    return 0;
}