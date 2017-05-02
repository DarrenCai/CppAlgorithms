/**
 * UVa11988
 * 破损的键盘
 */

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    string s;
    while(cin >> s) {
        int cur=0, last=0, len=s.length(), next[100005]={0};
        for(int i=0; i<len; ++i) {
            if(s[i] == '[') cur = 0;
            else if(s[i] == ']') cur = last;
            else {
                next[i+1] = next[cur];
                next[cur] = i+1;
                if(cur == last) last = i+1;
                cur = i+1;
            }
        }
        for(int i=next[0]; i; i=next[i]) cout << s[i-1];
        cout << endl;
    }
    return 0;
}