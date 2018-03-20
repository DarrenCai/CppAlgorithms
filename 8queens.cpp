#include <iostream>
using namespace std;

const short n = 8;
short a[n]; int t = 0;
void search(short cur) {
    for (short i = 1; i <= n; i++) {
        bool ok = true; a[cur] = i;
        for (short j = 0; j < cur && ok; j++)
            if (i == a[j] || cur-j == i-a[j] || cur-j == a[j]-i) ok = false;
        if (ok) {
            if (cur == n-1) {
                t ++;
                for (short j=0; j<n-1; ++j) cout << a[j] << ' ';
                cout << a[n-1] << endl;
            } else search(cur + 1);
        }
    }
}

int main()
{
    search(0);
    cout << t << endl;
    return 0;
}