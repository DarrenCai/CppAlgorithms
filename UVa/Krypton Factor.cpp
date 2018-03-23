/**
 * UVa129
 * 困难的串
 */

#include <iostream>
#include <vector>
using namespace std;
int n, t; short l; vector<char> s;

bool dfs(int cur) {
    const int len = s.size() + 1;
    for (char i=0; i<l; ++i) {
        if (len>1 && i==s.back()) continue;
        bool ok = true; s.push_back(i);
        for (int j=2; ok && (j<<1) <= len; ++j) {
            bool eq = true;
            for (int k=len-j; eq && k<len; ++k)
                if (s[k] != s[k-j]) eq = false;
            if (eq) ok = false;
        }
        if (ok) {
            if (++t == n) {
                for (int j=0; j<len; ++j) {
                    if (j && !(j&3)) j&63 ? cout << ' ' : cout << endl;
                    cout << char(s[j]+'A');
                }
                cout << endl << len << endl;
                return true;
            } else if (dfs(cur+1))
                return true;
        }
        s.pop_back();
    }
    return false; 
}

int main()
{
    while (cin >> n >> l && n) {
        t = 0;
        dfs(0);
        s.clear();
    }
    return 0;
}