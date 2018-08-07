/**
 * UVa12107
 * 数字谜
 */

#include <iostream>
#include <string>
using namespace std;

string s; char bit[] = "*0123456789", buf[5]; unsigned short l, a, b, n, maxd, k=0;

bool check() {
    unsigned short x = 0, y = 0;
    for (short i=0; i<a; ++i) x = 10*x + (s[i]-'0');
    for (short i=a+1; i<b; ++i) y = 10*y + (s[i]-'0');
    sprintf(buf, "%u", x*y);
    short len = 0; while(buf[len]) ++len;
    if (len != l-b-1) return false;
    for (short i=0,p; i<len; ++i) {
        if (s[p=i+b+1] == '*') continue;
        if (s[p] != buf[i]) return false;
    }
    return true;
}

void judge(short cur=0) {
    if (n>1) return;
    if (cur == b) {
        if (check()) ++n;
        return;
    }
    if (s[cur] == '*') {
        for (int i=1; i<11; ++i) {
            if (i==1 && (cur==0 || cur==a+1)) continue;
            s[cur] = bit[i];
            judge(cur+1);
            s[cur] = '*';
        }
    } else judge(cur+1);
}

bool iddfs(short d=0, short cur=0) {
    if (d>=maxd) {
        string ss = s; n = 0;
        judge();
        if (n==1) return true;
        s = ss;
        return false;
    } else if (cur == l) return false;
    if (s[cur] == ' ') {
        if (iddfs(d, cur+1)) return true;
    } else {
        char c = s[cur];
        for (short i=0; i<11; ++i) {
            if (i==1 && (cur==0 || cur==a+1)) continue;
            if (c == bit[i]) {
                if (iddfs(d, cur+1)) return true;
            } else {
                s[cur] = bit[i];
                if (iddfs(d+1, cur+1)) return true;
                s[cur] = c;
            }
        }
    }
    return false;
}

int main()
{
    while (getline(cin, s)) {
        if (s[0]=='0') return 0;
        l = s.length();
        for (a=0; s[a] != ' '; ++a);
        for (b=a+1; s[b] != ' '; ++b);
        for (maxd=0; !iddfs(); ++maxd);
        cout << "Case " << ++k << ": " << s << endl;
    }
    return 0;
}