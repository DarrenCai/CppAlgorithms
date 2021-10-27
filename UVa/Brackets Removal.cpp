/**
 * UVa1662
 * 括号
 */

#include <iostream>
using namespace std;

#define N 1010
char s[N], ans[N];
struct {short c, p; bool f;} q[N];

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s) {
        short n = 0, t = 0;
        for (short i=0; s[i]; ++i) {
            if (s[i] == '(') {
                q[t].c = i; q[t].p = n; q[t++].f = false; ans[n++] = s[i];
            } else if (s[i] == ')') {
                bool f = q[--t].f;
                if (!f) {
                    --n;
                    short c = q[t].c, a = q[t].p+1, b = q[t].p + i-c;
                    if (c>0 && s[c-1]=='/') {
                        c = 0;
                        for (short j=a; j<=b; ++j) {
                            if (ans[j] == '(') ++c;
                            if (ans[j] == ')') --c;
                            ans[j-1] = c ? ans[j] : (ans[j]=='*' ? '/' : (ans[j]=='/' ? '*' : ans[j]));
                        }
                    } else for (short j=a; j<=b; ++j) ans[j-1] = ans[j];
                } else {
                    short c = q[t].c, a = q[t].p+1, b = q[t].p + i-c;
                    char c1 = s[i+1], c2 = c>0 ? s[c-1] : 0;
                    if (c1=='*' || c1=='/' || c2=='*' || c2=='/') ans[n++] = s[i];
                    else {
                        --n;
                        if (c2 == '-') {
                            c = 0;
                            for (short j=a; j<=b; ++j) {
                                if (ans[j] == '(') ++c;
                                if (ans[j] == ')') --c;
                                ans[j-1] = c ? ans[j] : (ans[j]=='+' ? '-' : (ans[j]=='-' ? '+' : ans[j]));
                            }
                        } else for (short j=a; j<=b; ++j) ans[j-1] = ans[j];
                        if (t>0) q[t-1].f = true;
                    }
                }
            } else {
                ans[n++] = s[i];
                if (s[i]=='+' || s[i]=='-') q[t-1].f = true;
            }
        }
        ans[n] = 0;
        cout << ans << endl;
    }
}