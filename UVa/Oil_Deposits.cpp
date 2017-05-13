/**
 * UVa572
 * 油田
 */

#include <iostream>

void search(char s[100][100], int m, int n, int i, int j) {
    s[i][j] = '*';
    if(i-1 >= 0) {
        if(s[i-1][j] == '@')    search(s, m, n, i-1, j);
        if(j-1 >= 0 && s[i-1][j-1] == '@')    search(s, m, n, i-1, j-1);
        if(j+1 <n && s[i-1][j+1] == '@')      search(s, m, n, i-1, j+1);
    }
    if(j-1 >= 0 && s[i][j-1] == '@')    search(s, m, n, i, j-1);
    if(j+1 < n && s[i][j+1] == '@')     search(s, m, n, i, j+1);
    if(i+1 < m) {
        if(s[i+1][j] == '@')    search(s, m, n, i+1, j);
        if(j-1 >= 0 && s[i+1][j-1] == '@')    search(s, m, n, i+1, j-1);
        if(j+1 <n && s[i+1][j+1] == '@')      search(s, m, n, i+1, j+1);
    }
}

int main()
{
    using namespace std;
    int m, n;
    while(cin>>m>>n && m && n) {
        char s[100][100]={0}; int t=0;
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)  cin >> s[i][j];
        for(int i=0; i<m; ++i)
            for(int j=0; j<n; ++j)  
                if(s[i][j] == '@') { ++t; search(s, m, n, i, j); }
        cout << t << endl;
    }
    return 0;
}