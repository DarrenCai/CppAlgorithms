/**
 * UVa255
 */

#include <iostream>
using namespace std;

bool notAllowed(short k, short n) {
    return (k&7 && k-1==n) || ((k&7)<7 && k+1==n) || k-8==n || k+8==n;
}

bool locked(short k, short q) {
    return (!(k&7) || notAllowed(q, k-1)) && ((k&7)==7 || notAllowed(q, k+1))
        && (k<8 || notAllowed(q, k-8)) && (k>55 || notAllowed(q, k+8));
}

int main()
{
    short k, q, n;
    while (cin >> k >> q >> n) {
        if (k == q) {
            cout << "Illegal state" << endl;
        } else if (q==n || ((q&7)!=(n&7) && (q>>3)!=(n>>3)) || (k>=min(q,n) && k<=max(q,n) 
            && (((k&7)==(q&7) && (q&7)==(n&7)) || ((k>>3)==(q>>3) && (q>>3)==(n>>3))))) {
            cout << "Illegal move" << endl;
        } else if (notAllowed(k, n)) {
            cout << "Move not allowed" << endl;
        } else if (locked(k, n)) {
            cout << "Stop" << endl;
        } else cout << "Continue" << endl;
    }
    return 0;
}