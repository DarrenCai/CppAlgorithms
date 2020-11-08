/**
 * UVa1375
 * 给孩子起名
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define M 825   // 55*15
#define L 25

map<string, int> mp; vector<pair<short, short> > tr[M]; string s[M], d[M][L], empty(""); short t, ll, tt;
struct {short a, b, c;} r[M];
struct cmp {
    bool operator() (short a, short b) const {
        return d[a][ll] < d[b][ll] || (d[a][ll] == d[b][ll] && a<b);
    }
};

short id(const string& ss) {
    if (mp.count(ss)) return mp[ss];
    s[t] = ss;
    return mp[ss] = t++;
}

bool canbeEmpty(const string& ss) {
    for (short i=ss.length()-1; i>=0; --i) if (ss[i]>'Z') return false;
    return true;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    d[0][0] = s[0] = empty;
    for (ll=1; ll<=L; ++ll) d[0][ll] = "~";
    short n, l;
    while (cin >> n >> l && n) {
        mp.clear(); tr[0].clear(); mp[empty] = 0; t = 1; tt = 0;
        for (short i=1; i<M; ++i) {
            tr[i].clear();
            for (ll=0; ll<=l; ++ll) d[i][ll] = "~";
        }
        for (short i=0; i<n; ++i) {
            string e, head=empty, tail=empty; cin >> e; bool term = true;
            for (short j=e.length()-1; j>=2; --j) {
                if (e[j] <= 'Z') {
                    if (!term && head.length()>0) {
                        short b = id(head), c = id(tail), a = id(head+tail); d[b][head.length()] = head;
                        if (canbeEmpty(tail)) tr[b].push_back(pair<short, short>(a, c));
                        r[tt].a = a; r[tt].b = b; r[tt++].c = c;
                    }
                    short c = id(tail = head + tail);
                    if (term && tail.length()>0) d[c][tail.length()] = tail;
                    if (j>2) {
                        short b = id(e[j]+empty), a = id(tail = e[j] + tail);
                        if (a != b) {
                            if (canbeEmpty(tail)) tr[b].push_back(pair<short, short>(a, c));
                            tr[c].push_back(pair<short, short>(a, b));
                            r[tt].a = a; r[tt].b = b; r[tt++].c = c;
                        }
                    }
                    head = empty; term = false;
                } else head = e[j] + head;
            }
            short a = id(e[0]+empty);
            if (term) {
                ll = head.length(); if (head < d[a][ll]) d[a][ll] = head;
            } else {
                if (head.length() > 0) {
                    short b = id(head), c = id(tail); d[b][head.length()] = head;
                    if (canbeEmpty(tail)) tr[b].push_back(pair<short, short>(a, c));
                    r[tt].a = a; r[tt].b = b; r[tt++].c = c;
                } else {
                    short b = id(e[2]+empty), c = id(tail);
                    r[tt].a = a; r[tt].b = b; r[tt++].c = c;
                    tr[c].push_back(pair<short, short>(a, b));
                    if (canbeEmpty(tail)) tr[b].push_back(pair<short, short>(a, c));
                }
            }
        }
        for (ll=0; ll<=l; ++ll) {
            for (short i=0; i<tt; ++i) {
                short a = r[i].a, b = r[i].b, c = r[i].c;
                for (short j=1; j<ll; ++j) if (d[b][j] < "~" && d[c][ll-j] < "~")
                    d[a][ll] = min(d[a][ll], d[b][j] + d[c][ll-j]);
            }
            set<short, cmp> q;
            for (short i=0; i<t; ++i) if(d[i][ll] < "~") q.insert(i);
            while (!q.empty()) {
                short i = *q.begin(); q.erase(q.begin());
                for (short j=tr[i].size()-1; j>=0; --j) {
                    short a = tr[i][j].first, c = tr[i][j].second;
                    if (d[c][0].length() == 0 && d[i][ll] < d[a][ll]) {
                        d[a][ll] = d[i][ll];
                        if (q.count(a)) q.erase(a);
                        q.insert(a);
                    }
                }
            }
        }
        string ans = d[id("S")][l];
        cout << (ans == "~" ? "-" : ans) << endl;
    }
    return 0;
}