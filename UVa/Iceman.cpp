/**
 * UVa12112/LA3789
 * 冰人
 * Xi’an 2006
 */

#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;

int b[10], m, n, p, kase = 0; map<string, string> ans; queue<string> q;

void fall(string& s) {
    int m1 = m-1, n1 = n-1;
    for (int i=0; i<m; ++i) b[i] = n1-1;
    for (int i=n1-1; i>0; --i) for (int j=1; j<m1; ++j) {
        int k = i*m+j; char c = s[k];
        if (c == 'O' || c == '@') s[k] = '.', s[b[j]*m+j] = c, --b[j];
        else if (c == '[') for (int r = 1, x = b[j]; j+r < m; ++r) {
            x = min(x, b[j+r]);
            if (s[k+r] == 'X' || s[k+r] == ']') {
                j += r;
                if (s[k+r] == 'X') while (r >= 0) b[j - r--] = i-1;
                else for (int y = x*m + j; r >= 0; --r) c = s[k + r], s[k + r] = '.', s[y--] = c, b[j - r] = x-1;
                break;
            }
        } else if (c != '.') b[j] = i-1;
    }
}

void addi(string& s, int p) {
    bool l = true, r = true; char cl = s[p-1], cr = s[p+1];
    if (cl == 'X' || cl == 'O' || cl == ']') {
        s[p-1] = cl == 'X' ? 'X' : (cl == 'O' ? '[' : '=');
        l = false;
    }
    if (cr == 'X' || cr == 'O' || cr == '[') {
        s[p+1] = cr == 'X' ? 'X' : (cr == 'O' ? ']' : '=');
        r = false;
    }
    s[p] = l ? (r ? 'O' : '[') : (r ? ']' : '=');
}

void deli(string& s, int p) {
    char cl = s[p-1], cr = s[p+1];
    if (cl == '[' || cl == '=') s[p-1] = cl == '[' ? 'O' : ']';
    if (cr == ']' || cr == '=') s[p+1] = cr == ']' ? 'O' : '[';
    s[p] = '.';
}

void movei(string& s, int p, int d) {
    if (s[p+d] != '.') return;
    s[p+d] = 'O'; s[p] = '.';
    if (s[p+d+m] != '.') movei(s, p+d, d);
}

bool check(const string& s, const string& t) {
    int a = s.find('@');
    if (a == p) {
        cout << t << endl;
        return true;
    }
    if (!ans.count(s) && max(max(1, a/m - p/m), abs(a%m - p%m)) + t.size() < 16) ans[s] = t, q.push(s);
    return false;
}

bool solve(const string& s) {
    int a = s.find('@'); char c = s[a+m-1];
    if (c == '.') {
        string t = s; addi(t, a+m-1); fall(t);
        if (check(t, ans[s] + '<')) return true;
    } else if (c == 'O' || c == '[' || c == ']' || c == '=') {
        string t = s; deli(t, a+m-1); fall(t);
        if (check(t, ans[s] + '<')) return true;
    }
    c = s[a+m+1];
    if (c == '.') {
        string t = s; addi(t, a+m+1); fall(t);
        if (check(t, ans[s] + '>')) return true;
    } else if (c == 'O' || c == '[' || c == ']' || c == '=') {
        string t = s; deli(t, a+m+1); fall(t);
        if (check(t, ans[s] + '>')) return true;
    }
    c = s[a-1];
    if (c == '.') {
        string t = s; t[a] = '.'; t[a-1] = '@'; fall(t);
        if (check(t, ans[s] + 'L')) return true;
    } else {
        string t = s;
        if (c == 'O') movei(t, a-1, -1);
        if (t[a-1] != '.' && t[a-m] == '.' && t[a-m-1] == '.') t[a-m-1] = '@', t[a] = '.';
        fall(t);
        if (check(t, ans[s] + 'L')) return true;
    }
    c = s[a+1];
    if (c == '.') {
        string t = s; t[a] = '.'; t[a+1] = '@'; fall(t);
        if (check(t, ans[s] + 'R')) return true;
    } else {
        string t = s;
        if (c == 'O') movei(t, a+1, 1);
        if (t[a+1] != '.' && t[a-m] == '.' && t[a-m+1] == '.') t[a-m+1] = '@', t[a] = '.';
        fall(t);
        if (check(t, ans[s] + 'R')) return true;
    }
    return false;
}

void solve() {
    cin >> m;
    cout << "Case " << ++kase << ": ";
    string s(m*n, 'X');
    for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) cin >> s[i*m+j];
    if ((p = s.find('#')) < 0 || int(s.find('@')) < 0) return;
    s[p] = '.'; ans.clear(); while (!q.empty()) q.pop();
    ans[s] = ""; q.push(s);
    while (!q.empty()) {
        s = q.front(); q.pop();
        if (solve(s)) return;
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> n && n) solve();
    return 0;
}