/**
 * UVa817
 * 数字表达式
 */

#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

int k=0, len, val; char s[11], ss[19]; stack<int> operand; stack<char> op; bool noAns;

void calc() {
    bool hasOp = false; int i;
    for (val=0, i=0; ss[i]; ++i) {
        if (ss[i] == '=' || ss[i] == '+' || ss[i] == '-') {
            while (!op.empty()) {
                char oper = op.top(); op.pop();
                int left = operand.top(); operand.pop();
                val = oper=='*' ? left*val : (oper=='+' ? left+val : left-val);
            }
            if (hasOp && ss[i] == '=' && val == 2000) {
                noAns = false; cout << "  " << ss << endl;
            }
        }
        if (ss[i]>='0' && ss[i]<='9') {
            val = val*10 + ss[i]-'0';
        } else {
            if (ss[i] != '=') {
                hasOp = true; operand.push(val); op.push(ss[i]);
            }
            val = 0;
        }
    }
}

void change(short cur=0) {
    if (ss[cur] == '=') return calc();
    if (ss[cur] == '*') {
        change(cur+1);
        ss[cur] = '+'; change(cur+1);
        ss[cur] = '-'; change(cur+1);
        ss[cur] = '*';
    } else change(cur+1);
}

void search(short p=0, short cur=0, short pre=0) {
    if (s[pre]=='0' && cur > pre) return;
    ss[p] = s[cur];
    if (cur+1 == len) {
        ss[p+1] = '='; ss[p+2] = 0;
        change();
        return;
    }
    ss[p+1] = '*'; search(p+2, cur+1, cur+1);
    search(p+1, cur+1, pre);
}

int main()
{
    while (cin >> s && s[0]!='=') {
        cout << "Problem " << ++k << endl;
        for (len=0; s[len]!='='; ++len);
        memset(ss, 0, sizeof(ss)); noAns = true;
        search(); if (noAns) cout << "  IMPOSSIBLE" << endl;
    }
    return 0;
}