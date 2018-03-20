#include <iostream>
using namespace std;

void subset(int n, int* a, int cur) {       // 增量法
    for(int i=0; i<cur; ++i)
        cout << a[i] << ' ';
    cout << endl;
    for(int i = cur ? a[cur-1]+1 : 1; i<=n; ++i) {      // cur ? a[cur-1]+1 : 1; 定序
        a[cur] = i;
        subset(n, a, cur+1);
    }
}

void subset2(int n, int* b, int cur) {      // 位向量法
    if (cur == n) {
        for(int i=0; i<cur; ++i)
            if (b[i]) cout << i+1 << ' ';
        cout << endl;
    } else {
        b[cur] = 1;
        subset2(n, b, cur+1);
        b[cur] = 0;
        subset2(n, b, cur+1);
    }
}

int main() {
    int a[10];
    subset(10, a, 0);
    cout << endl << endl << endl;
    subset2(10, a, 0);
}