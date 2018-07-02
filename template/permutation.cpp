#include <iostream>
using namespace std;

void permutation(int n, int* a, int cur) {
    if (cur == n) {
        for (int i=0; i<n; ++i)
            cout << a[i] << ' ';
        cout << endl;
    } else for (int i=1; i<=n; ++i) {
        bool ok = true;
        for (int j=0; j<cur; ++j)
            if (a[j] == i) ok = false;
        if (ok) {
            a[cur] = i;
            permutation(n, a, cur+1);
        }
    }
}

int main() {
    int a[10];
    permutation(10, a, 0);
    return 0;
}