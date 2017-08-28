/**
 * UVa804
 * Petri网模拟
 */

 #include <iostream>
 #include <map>
 #include <vector>
 using namespace std;
 
int main()
{
    int n, k=0;
    while(cin>>n && n) {
        vector<int> p(n);
        for(int i=0; i<n; ++i) cin >> p[i];
        int m; cin>>m;
        vector<map<int, int> > ip(m), op(m);
        for(int i=0; i<m; ++i) {
            int e;
            while(cin>>e && e) {
                if(e<0) {
                    e = -e - 1;
                    if(ip[i].count(e)) ++ip[i][e];
                    else ip[i][e] = 1;
                } else {
                    --e;
                    if(op[i].count(e)) ++op[i][e];
                    else op[i][e] = 1;
                }
            }
        }
        int t, i, j; cin>>t;
        for(i=0; i<=t; ++i) {
            for(j=0; j<m; ++j) {
                bool sufficient = true;
                for(map<int, int>::iterator it=ip[j].begin(); it!=ip[j].end(); ++it) {
                    if(it->second > p[it->first]) {
                        sufficient = false;
                        break;
                    }
                }
                if (sufficient) {
                    for(map<int, int>::iterator it=ip[j].begin(); it!=ip[j].end(); ++it)
                        p[it->first] -= it->second;
                    for(map<int, int>::iterator it=op[j].begin(); it!=op[j].end(); ++it)
                        p[it->first] += it->second;
                    break;
                }
            }
            if(j == m) break;
        }
        cout << "Case " << ++k << (i==t ? ": still live" : ": dead") << " after " << i << " transitions" << endl;
        cout << "Places with tokens:";
        for(int i=0; i<n; ++i) 
            if(p[i] > 0) cout << ' ' << (i+1) << " (" << p[i] << ")";
        cout << endl << endl;
    }
    return 0;
}