/**
 * UVa12520
 * 方形花园
 */

#include <iostream>
using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    long long l, n;
    while (cin>>l>>n && l) {
        long long v = (l*l+1)>>1, c = (l-1) << 1;
        if (n <= v) {
            cout << (n<<2) << endl;
        } else if (l&1) {
            if (n < v+3) {
                cout << 6*v - (n<<1) << endl;
            } else if (n < v+c) {
                cout << 6*v - (n<<1) + 2 << endl;
            } else cout << (v<<3) + (c<<1) - (n<<2) << endl;
        } else {
            if (n <= v+2) {
                cout << (v<<2) << endl;
            } else if (n <= v+c) {
                cout << 6*v - (n<<1) + 4 << endl;
            } else cout << (v<<3) + (c<<1) - (n<<2) + 4 << endl;
        }
    }
    return 0;
}
