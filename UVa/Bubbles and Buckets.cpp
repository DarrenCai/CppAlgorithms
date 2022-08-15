/**
 * UVa11495
 * 逆序数问题，可以在归并排序的过程中实现统计。
 */

#include <iostream>
using namespace std;

#define N 100100
int a[N], t[N], ans, n;

void merge(int l, int m, int r) {
    int i=l, j=m+1, k=l;
    while (i<=m && j<=r) {
        if (a[i] <= a[j]) {
            t[k++] = a[i++];
        } else {
            ans ^= (j-k)&1;
            t[k++] = a[j++];
        }
    }
    while (i<=m) t[k++] = a[i++];
    while (j<=r) t[k++] = a[j++];
    for (int i=l; i<=r; ++i) a[i] = t[i];
}

void merge_sort(int l, int r) {
    if (l == r) return;
    int m = (l+r)>>1;
    merge_sort(l, m);
    merge_sort(m+1, r);
    merge(l, m, r);
}

bool solve() {
    for (int i=ans=0; i<n; ++i) cin >> a[i];
    merge_sort(0, n-1);
    return ans;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin>>n && n) cout << (solve() ? "Marcelo" : "Carlos") << endl;
    return 0;
}