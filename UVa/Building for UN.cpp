/**
 * UVa1605
 * 联合国大楼
 */

#include <iostream>

int main()
{
    using namespace std;
    short n, k=0;
    while (cin >> n) {
        if (k++) cout << endl;
        cout << 2 << ' ' << n << ' ' << n << endl;
        for (short i=0; i<n; ++i) {
            char c = i<26 ? 'A'+i : 'a' + i - 26;
            for (short j=0; j<n; ++j) cout << c;
            cout << endl;
        }
        cout << endl;
        for (short i=0; i<n; ++i) {
            for (short j=0; j<n; ++j) {
                char c = j<26 ? 'A'+j : 'a' + j - 26;
                cout << c;
            }
            cout << endl;
        }
    }
    return 0;
}