/**
 * UVa10491
 * 奶牛和轿车
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(5);
    short a, b, c;
    while (cin >> a >> b >> c) {
        double p = 1.0*(a+b-1)*b/(a+b)/(a+b-c-1);
        cout << p << endl;
    }
    return 0;
}