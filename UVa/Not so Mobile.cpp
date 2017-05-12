/**
 * UVa839
 * 天平
 */

#include <iostream>
// #include <cstdio>

using namespace std;

int build(bool& eq) {
    int Wl,Wr,Dl,Dr;
    cin >> Wl >> Dl >> Wr >> Dr;
    if(!Wl)     Wl = build(eq);
    if(!Wr)     Wr = build(eq);
    if(Wl*Dl != Wr*Dr)    eq = false;
    return Wl+Wr;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    while(t--) {
        bool eq = true; build(eq);
        cout << (eq ? "YES" : "NO") << endl;
        if(t)   cout << endl;
    }
    return 0;
}