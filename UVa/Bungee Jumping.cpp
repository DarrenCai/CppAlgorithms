/**
 * UVa10868
 * 蹦极
 */

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    long double k, l, s, w;
    while (cin>>k>>l>>s>>w && !(k==0. && l==0. && s==0. && w==0.)) {
        long double v = l>=s ? 19.62*s : 19.62*s-k*(s-l)*(s-l)/w;
        cout << (v < 0. ? "Stuck in the air." : (v > 100. ? "Killed by the impact." : "James Bond survives.")) << endl;
    }
    return 0;
}