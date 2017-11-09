/**
 * UVa12118
 * 检查员的难题
 */

#include <iostream>
#include <vector>
#include <set>

int main()
{
    using namespace std;
    short v, t; int e, k=0;
    while(cin >> v >> e >> t && v != 0) {
        vector<int> es(e); short d[1001]={0};
        for (int i=0; i<e; ++i) {
            short a, b; cin >> a >> b;
            ++ d[a]; ++ d[b];
            es[i] = a<<10|b;
        }
        vector<set<short> > bs; short c[500]={0}, s=0, r=0;
        for (int i=0; i<es.size(); ++i) {
            short a = es[i]>>10, b = es[i]&1023;
            bool contain = false;
            for (short j=0; j<s; ++j) {
                if (bs[j].count(a) || bs[j].count(b)) {
                    bs[j].insert(a); bs[j].insert(b);
                    ++c[j]; contain = true; break;
                }
            }
            if(!contain) {
                bs.push_back(set<short>()); ++c[s];
                bs[s].insert(a); bs[s++].insert(b);
            }
            for(vector<int>::iterator it = es.begin()+i+1; it != es.end();) {
                a = *it>>10, b = *it&1023;
                bool contain = false;
                for (short j=0; j<s; ++j) {
                    if (bs[j].count(a) || bs[j].count(b)) {
                        bs[j].insert(a); bs[j].insert(b);
                        ++c[j]; it = es.erase(it);
                        contain = true; break;
                    }
                }
                if(!contain) ++it;
            }
        }
        for (short i=0; i<s; ++i) {
            const set<short>& b = bs[i]; short odd = 0;
            for (set<short>::iterator it = b.begin(); it != b.end(); ++it)
                if (d[*it] & 1) ++odd;
            r += c[i] + (odd > 2 ? (odd-2)>>1 : 0);
        }
        if (s > 1) r += s-1;
        cout << "Case " << ++k << ": " << r*t << endl;
    }
    return 0;
}