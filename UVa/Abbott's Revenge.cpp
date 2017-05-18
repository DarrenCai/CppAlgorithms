/**
 * UVa816
 * Abbott的复仇
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

enum Direction{ E, W, N, S, L=1, R=2, F=4 };
const short travel[4][2] = { {N, S}, {S, N}, {W, E}, {E, W} };
const short delta[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

struct node {
    short r, c;
    node(short r, short c){ this->r=r; this->c=c; }
    bool operator < (const node& b) const { return r<b.r || (r==b.r && c<b.c); }
    bool operator == (const node& b) const { return r==b.r && c==b.c; }
};

struct cross {
    short r, c, d;
    cross(short r, short c, short d){ this->r=r; this->c=c; this->d=d; }
    bool operator < (const cross& b) const { return r<b.r || (r==b.r && c<b.c) || (r==b.r && c==b.c && d<b.d); }
    bool operator == (const cross& b) const { return r==b.r && c==b.c && d==b.d; }
    bool operator == (const node& b) const { return r==b.r && c==b.c; }
};

short convert(const char c) {
    if(c=='E')  return E;
    if(c=='W')  return W;
    if(c=='N')  return N;
    if(c=='S')  return S;
    if(c=='L')  return L;
    if(c=='R')  return R;
    if(c=='F')  return F;
    return -1;
};

int main()
{
    using namespace std;
    string maze; set<cross> visit; vector<cross> q; map<node, short> nodes; vector<vector<node> > path;
    while(cin>>maze && maze!="END"){
        short r0, c0, r1, c1; char c; cin >> r0 >> c0 >> c >> r1 >> c1;
        node start=node(r0, c0), end=node(r1, c1); short d=convert(c); cross sc = cross(r0+delta[d][0], c0+delta[d][1], d);
        visit.insert(sc); q.push_back(sc); path.push_back(vector<node>(1, start)); path[0].push_back(node(sc.r, sc.c));
        while(cin>>r1 && r1) {
            cin >> c1; node t=node(r1, c1); nodes[t] = 0; string s;
            while(d=0, cin>>s && s[0]!='*'){
                for(short i=1; i<s.length(); ++i)   d |= convert(s[i]);
                nodes[t] |= d << 3*convert(s[0]);
            }
        }
        short head=0,tail=1;
        while(head < tail) {
            node t = node(q[head].r, q[head].c);
            if(nodes.count(t)) {
                d = 3*q[head].d; d = (nodes[t] & 7 << d) >> d;
                if(d & L) {
                    cross c = cross(t.r+delta[travel[q[head].d][0]][0], t.c+delta[travel[q[head].d][0]][1], travel[q[head].d][0]);
                    if(!visit.count(c)){ visit.insert(c); q.push_back(c); vector<node> v=path[head]; v.push_back(node(c.r, c.c)); path.push_back(v); }
                    if(c == end) break;
                }
                if(d & R) {
                    cross c = cross(t.r+delta[travel[q[head].d][1]][0], t.c+delta[travel[q[head].d][1]][1], travel[q[head].d][1]);
                    if(!visit.count(c)){ visit.insert(c); q.push_back(c); vector<node> v=path[head]; v.push_back(node(c.r, c.c)); path.push_back(v); }
                    if(c == end) break;
                }
                if(d & F) {
                    cross c = cross(t.r+delta[q[head].d][0], t.c+delta[q[head].d][1], q[head].d);
                    if(!visit.count(c)){ visit.insert(c); q.push_back(c); vector<node> v=path[head]; v.push_back(node(c.r, c.c)); path.push_back(v); }
                    if(c == end) break;
                }
            }
            if(++head==tail) tail=q.size();
        }
        cout << maze; const vector<node>& ans = path[path.size()-1];
        if(*(ans.rbegin()) == end)
            for(int i=0, len=ans.size(); i<len; ++i) {
                if(i%10==0) cout << endl << ' ';
                cout << " (" << ans[i].r << ',' << ans[i].c << ')';
            }
        else   cout << endl << "  No Solution Possible";
        cout << endl; nodes.clear(); visit.clear(); q.clear(); path.clear();
    }
    return 0;
}
