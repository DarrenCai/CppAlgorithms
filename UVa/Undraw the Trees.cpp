/**
 * UVa10562
 * 看图写树
 */

#include <iostream>
#include <vector>
#include <string>


using namespace std;

bool isNode(char c){ return c!='-' && c!='|' && c!=' ' && c!='#'; }

void build(vector<string>& in, short p, short s) {
    cout << in[p][s] << '(';
    if (p+1<in.size() && in[p+1].length()>s && in[p+1][s]=='|') {
// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wempty-body"
        int l=s, r=s; while(l && in[p+2][--l]=='-'); while(in[p+2][++r]=='-');
// #pragma clang diagnostic pop
        for(short i=l+1; i<in[p+3].length() && i<r; ++i) { if(isNode(in[p+3][i])){ build(in, p+3, i); } }
    }
    cout << ')';
}

int main()
{
    short t; cin >> t; cin.get();
    while(t--) {
        cout << '(';vector<string> in; string s;
        while(getline(cin, s) && s[0]!='#') { in.push_back(' ' + s + ' '); }
        for(short i=0; in.size()>0 && i<in[0].length(); ++i)
            if(isNode(in[0][i])) { build(in, 0, i); break; }
        cout << ')' << endl;
    }
    return 0;
}