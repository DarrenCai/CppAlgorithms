/**
 * UVa712
 * S树
 */

#include <iostream>

int main()
{
    using namespace std;
    char x[8], vva[8], v[129]; int k=0, n;
    while(cin>>n && n){ cout << "S-Tree #" << ++k << ':' << endl;
        for(char i=0; i<n; ++i){char c; while((c=cin.get())!='x'); cin >> x[i]; x[i]-='1';}
        cin >> v; int m; cin >> m;
        while(m--){ cin>>vva; char i=0; for(char j=0; j<n; ++j) i=i<<1|vva[x[j]]-'0'; cout << v[i]; }
        cout << endl << endl;
    }
    return 0;
}