/**
 * UVa679
 * 小球下落
 */

#include <iostream>

int main()
{
    using namespace std;
    int s[1048576]={0}, *r[20]={0}; s[1]=1;
    for(int i=1,l=1; i<20; ++i,l<<=1) {
        int n = l<<1;
        r[i] = new int[n+1];
        for(int j=l; j<n; ++j) {
            int p = j<<1;
            s[p] = s[j];
            r[i][s[j]] = p;
            s[p+1] = s[j]+l;
            r[i][s[j]+l] = p+1;
        }
    }
    int t; cin>>t;
    while(t--) {
        int d,i; cin>>d>>i;
        cout << r[d-1][i] << endl;
    }
    return 0;
}