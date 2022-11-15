/**
 * UVa679
 * 小球下落
 */

#include <iostream>

int main()
{
    using namespace std;
    int t; cin>>t;
    while(t--) {
        int d,i,k=1; cin>>d>>i;
        while(--d) {
            k = (k<<1) + 1-(i&1);
            i = (i+1) >> 1;
        }
        cout << k << endl;
    }
    return 0;
}