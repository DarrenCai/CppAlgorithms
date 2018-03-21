/**
 * UVa524
 * 素数环
 */

#include <iostream>
using namespace std;

const bool isPrim[] = {false, false, true, true, false, true, false, true, false, false, false, 
                       true, false, true, false, false, false, true, false, true, false, false,
                       false, true, false, false, false, false, false, true, false, true, false};
short n, a[17];
void dfs(bool (&visit)[17], short cur) {
    for (short i=2; i<=n; ++i) {
        if (!visit[i] && isPrim[a[cur-1]+i] && (cur!=n || isPrim[i+a[1]])) {
            if (cur == n) {
                for (short j=1; j<n; ++j) 
                    cout << a[j] << ' ';
                cout << i << endl;
            } else {
                visit[i] = true; a[cur] = i;
                dfs(visit, cur+1);
                visit[i] = false;
            }
        }
    }
}

int main()
{
    int k=0; a[1] = 1;
    while (cin >> n) {
        if (k++) cout << endl;
        cout << "Case " << k << ':' << endl;
        bool visit[17] = {false};
        dfs(visit, 2);
    }
    return 0;
}