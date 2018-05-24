/**
 * UVa11212
 * 编辑书稿
 */

#include <iostream>

short n; char p[9], ops;

char idx(const char *s, char a) {
    for (char i=0; i<n; ++i)
        if (s[i] == a) return i;
    return 0;
}

bool expand(const char *s, char d, char i, char l, char j);

bool IDDFS(const char* s, char d=0) {
    bool isAns = true;
    for (char i=0; isAns && i<n; ++i)
        if (s[i] != '1'+i) isAns = false;
    if (isAns) {
        return true;
    } else if (d < ops) {
        for (char i=0; i<n-1; ++i) {
            for (char l=1; l<n-i; ++l) {
                if ((!i || s[i] != s[i-1] + 1) && s[i+l] != s[i+l-1] + 1) {
                    char a = idx(s, s[i]-1), b = idx(s, s[i+l-1]+1)-1;
                    if (a<i+l && b<i+l) {
                        for (char j=i+l; j<n; ++j)
                            if ((j==n-1 || s[j+1] != s[j] + 1) && expand(s, d+1, i, l, j))
                                return true;
                    } else {
                        if (a>=i+l && expand(s, d+1, i, l, a)) return true;
                        if (b>=i+l && expand(s, d+1, i, l, b)) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool expand(const char *s, char d, char i, char l, char j) {
    char s1[9], t=0;
    for (char k=0; k<i; ++k) s1[k] = s[k];
    for (char k=i+l; k<=j; ++k) s1[k-l] = s[k];
    for (char k=i; k<i+l; ++k) s1[j+1+k-i-l] = s[k];
    for (char k=j+1; k<n; ++k) s1[k] = s[k];
    for (char k=0; k<n-1; ++k)
        if (s1[k]+1 != s1[k+1]) ++t;
    if (3*d + t <= 3*ops && IDDFS(s1, d))
        return true;
    return false;
}

int main()
{
    using namespace std;
    short k=0;
    while (cin>>n && n) {
        for (short i=0; i<n; ++i)
            cin >> p[i];
        ops = 0;
        while (!IDDFS(p)) ++ ops;
        cout << "Case " << ++k << ": " << short(ops) << endl;
    }
    return 0;
}