/**
 * UVa11694
 * Gokigen Naname谜题
 */

#include <iostream>
#include <queue>
using namespace std;

short n, t[8][8]; char ans[7][8];

bool cycle(short r, short c) {
    if (c > 0 && ans[r][c-1] == '\\') {
        bool visit[7][7] = {0}; visit[r][c] = visit[r][c-1] = true;
        queue<short> q; q.push(r<<3 | c-1);
        while (!q.empty()) {
            short e = q.front(), rr = e>>3, cc = e&7; q.pop();
            if (ans[rr][cc]=='\\') {
                if (rr && cc && !visit[rr-1][cc-1] && ans[rr-1][cc-1]=='\\') {
                    visit[rr-1][cc-1] = true; q.push((rr-1)<<3 | cc-1);
                }
                if (rr && !visit[rr-1][cc] && ans[rr-1][cc]=='/') {
                    visit[rr-1][cc] = true; q.push((rr-1)<<3 | cc);
                }
                if (cc && !visit[rr][cc-1] && ans[rr][cc-1]=='/') {
                    if (rr+1==r && cc-2==c) return true;
                    visit[rr][cc-1] = true; q.push(rr<<3 | cc-1);
                }
                if (rr<n && cc<n && !visit[rr+1][cc+1] && ans[rr+1][cc+1]=='\\') {
                    if (rr+2==r && cc+1==c) return true;
                    visit[rr+1][cc+1] = true; q.push((rr+1)<<3 | cc+1);
                }
                if (rr<n && !visit[rr+1][cc] && ans[rr+1][cc]=='/') {
                    if (rr+2==r && cc-1==c) return true;
                    visit[rr+1][cc] = true; q.push((rr+1)<<3 | cc);
                }
                if (cc<n && !visit[rr][cc+1] && ans[rr][cc+1]=='/') {
                    visit[rr][cc+1] = true; q.push(rr<<3 | cc+1);
                }
            } else if (ans[rr][cc]=='/') {
                if (rr && cc<n && !visit[rr-1][cc+1] && ans[rr-1][cc+1]=='/') {
                    visit[rr-1][cc+1] = true; q.push((rr-1)<<3 | cc+1);
                }
                if (rr && !visit[rr-1][cc] && ans[rr-1][cc]=='\\') {
                    visit[rr-1][cc] = true; q.push((rr-1)<<3 | cc);
                }
                if (cc<n && !visit[rr][cc+1] && ans[rr][cc+1]=='\\') {
                    if (rr+1==r && cc+1==c) return true;
                    visit[rr][cc+1] = true; q.push(rr<<3 | cc+1);
                }
                if (rr<n && !visit[rr+1][cc-1] && cc && ans[rr+1][cc-1]=='/') {
                    if (rr+2==r && cc-2==c) return true;
                    visit[rr+1][cc-1] = true; q.push((rr+1)<<3 | cc-1);
                }
                if (rr<n && !visit[rr+1][cc] && ans[rr+1][cc]=='\\') {
                    if (rr+2==r && cc==c) return true;
                    visit[rr+1][cc] = true; q.push((rr+1)<<3 | cc);
                }
                if (cc && !visit[rr][cc-1] && ans[rr][cc-1]=='\\') {
                    visit[rr][cc-1] = true; q.push(rr<<3 | cc-1);
                }
            }
        }
    }
    return false;
}

bool ok(short r, short c) {
    if (t[r][c]>0 && t[r][c]<5) return false;
    if (c==n-1 && t[r][c+1]>0 && t[r][c+1]<5) return false;
    if (r==n-1 && t[r+1][c]>0 && t[r+1][c]<5) return false;
    if (r==n-1 && c==n-1 && t[r+1][c+1]>0 && t[r+1][c+1]<5) return false;
    return true;
}

bool dfs(short r=0, short c=0) {
    if (c >= n) ++r, c=0;
    if (r >= n) return true;
    if (t[r][c] && t[r+1][c+1]) {
        ans[r][c] = '\\'; --t[r][c]; --t[r+1][c+1];
        if (ok(r, c) && dfs(r, c+1)) return true;
        ++t[r][c]; ++t[r+1][c+1];
        if (t[r][c] < 5) return false;
    }
    if (t[r+1][c] && t[r][c+1]) {
        ans[r][c] = '/'; --t[r+1][c]; --t[r][c+1];
        if (!cycle(r, c) && ok(r, c) && dfs(r, c+1)) return true;
        ++t[r+1][c]; ++t[r][c+1];
    }
    return false;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    short k; cin>>k;
    while (k--) {
        cin >> n;
        for (short r=0; r<=n; ++r) {
            for (short c=0; c<=n; ++c) {
                ans[r][c] = 0; char ch; cin >> ch;
                if (ch == '.') t[r][c] = 9;
                else t[r][c] = ch - '0';
            }
            ans[r][n] = 0;
        }
        dfs();
        for (short i=0; i<n; ++i) cout << ans[i] << endl;
    }
    return 0;
}