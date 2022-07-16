/**
 * UVa11236
 */

#include <iostream>
using namespace std;

void print(int v) {
    cout << v/100 << '.';
    v %= 100;
    if (v<10) cout << '0';
    cout << v;
}

int main() {
    // freopen("out.txt", "w", stdout);
    int sum = 2000, q = 1000000;
    for (int a=1, m=sum/4; a<=m; ++a)
        for (int b=a, n=(sum-a)/3; b<=n; ++b)
            for (int c=max(b, q/a/b+1), p=(sum-a-b)/2; c<=p; ++c) {
                int d = (a+b+c)*q / (a*b*c-q);
                if (d<c || a+b+c+d>sum || (a+b+c+d)*q!=a*b*c*d) continue;
                print(a);
                cout << ' ';
                print(b);
                cout << ' ';
                print(c);
                cout << ' ';
                print(d);
                cout << endl;
            }
    return 0;
}