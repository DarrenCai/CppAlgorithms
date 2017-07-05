/**
 * UVa1572
 * 自组合
 */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct molecule{ char e[4];
    bool operator == (const molecule &m) const {return e[0]==m.e[0] && e[1]==m.e[1] && e[2]==m.e[2] && e[3]==m.e[3];}
    char count(const char& edge) const {char t=0; for(char i=0; i<4; ++i) if(e[i]==edge) ++t; return t;}
};
struct mHash { std::size_t operator () (const pair<molecule, char>& me) const { return me.second*7890481 + me.first.e[0]*148877 + me.first.e[1]*2809 + me.first.e[2]*53 + me.first.e[3]; } };
#define SET unordered_set<pair<molecule, char>, mHash>

bool search(const pair<molecule, char>& me, const vector<molecule>& m, const unordered_set<unsigned short> (&em)[52], SET& visit, SET path){
    if(path.count(me)) return true;
    visit.insert(me); path.insert(me); char e = me.second&1 ? me.second+1 : me.second-1;
    for(unsigned short i: em[e-1]){
        for(char j=0; j<4; ++j) if(m[i].e[j] && m[i].e[j] != e && search(pair<molecule, char>(m[i], m[i].e[j]), m, em, visit, path)) return true;
        if(m[i].count(e) > 1 && search(pair<molecule, char>(m[i], e), m, em, visit, path)) return true;
    }
    return false;
}

#include <cstdio>
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
    unsigned short n;
    while(cin >> n){
        vector<molecule> m(n); unordered_set<unsigned short> em[52]; SET visit;
        for(unsigned short i=0; i<n; ++i) for(char j=0; j<4; ++j){char c0, c1; cin >> c0 >> c1; m[i].e[j] = c0=='0' ? 0 : 2*(c0-'A')+(c1=='+' ? 2:1); if(m[i].e[j]) em[m[i].e[j]-1].insert(i);}
        bool bounded = true;
        for(unsigned short i=0; i<n; ++i) for(char j=0; j<4; ++j){ if(!m[i].e[j]) continue; pair<molecule, char> me(m[i], m[i].e[j]);
            if(!visit.count(me) && search(me, m, em, visit, SET())){bounded = false; break;}
        }
        cout << (bounded ? "bounded" : "unbounded") << endl;
    }
    return 0;
}