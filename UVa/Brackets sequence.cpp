/**
 * UVa1626
 * 括号序列
 */

#include <iostream>
#include <cstring>
using namespace std;

#define N 105
char s[N];
int d[N][N] = {0}, k[N][N], n;

void print(int i, int j) {
    if (j < i) return;
    if (i == j) {
        cout << (s[i]=='[' || s[i]==']' ? "[]" : "()");
    } else if (d[i][j] == d[i+1][j-1] && ((s[i]=='(' && s[j]==')') || (s[i]=='[' && s[j]==']'))) {
        cout << s[i];
        print(i+1, j-1);
        cout << s[j];
    } else {
        print(i, k[i][j]);
        print(k[i][j]+1, j);
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    int t; cin >> t;
    cin.get();
    while (t--) {
        cin.get();
        cin.getline(s, N);
        n = strlen(s);
        for (int i=0; i<n; ++i) d[i][i] = 1, k[i][i] = i;
        for (int l=1; l<n; ++l) for (int i=0, j; (j=i+l)<n; ++i) {
            d[i][j] = N;
            if ((s[i]=='(' && s[j]==')') || (s[i]=='[' && s[j]==']')) d[i][j] = d[i+1][j-1], k[i][j] = k[i+1][j-1];
            for (int k1=i, v; k1<j; ++k1) if ((v = d[i][k1] + d[k1+1][j]) < d[i][j]) d[i][j] = v, k[i][j] = k1;
        }
        print(0, n-1);
        cout << endl;
        if (t) cout << endl;
    }
    return 0;
}