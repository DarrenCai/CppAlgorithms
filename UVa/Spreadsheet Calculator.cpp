/**
 * UVa215
 * 电子表格计算器
 */

#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
using namespace std;

struct Node {
    short type, val; // type 0:值 1:加号 2:减号 3:引用其它单元格
    Node(short t):type(t) {}
    Node(short t, short v):type(t),val(v) {}
};

string s[200]; short r, c, t, v[200]; bool f[200];

void de(short p, short p1, bool (&d)[200][200], bool (&inv)[200][200]) {
    for(short j=0; j<t; ++j) {
        if(inv[p][j] && !d[j][p1]) {
            d[j][p1] = true, inv[p1][j] = true;
            if (d[p1][p1]) d[j][j] = true;
            if(j != p1) de(j, p1, d, inv);
        }
        if(d[p1][j] && !d[p][j]) {
            d[p][j] = true, inv[j][p] = true;
            if (d[j][j]) d[p][p] = true;
            if(p != j) de(p, j, d, inv);
        }
    }
}

void de(short p, bool (&d)[200][200], bool (&inv)[200][200]) {
    short size = s[p].size(), i=0;
    while(i<size) {
        if (s[p][i] == '+' || s[p][i] == '-')
            ++ i;
        else if(s[p][i]>='A' && s[p][i]<='T') {
            short p1 = (s[p][i]-'A')*c + s[p][i+1]-'0';
            d[p][p1] = true;
            inv[p1][p] = true;
            if (d[p1][p1]) d[p][p] = true;
            if(p != p1) de(p, p1, d, inv);
            i += 2;
        } else {
            for(++i; s[p][i]>='0' && s[p][i]<='9'; ++i);
        }
    }
}

void calc(short p) {
    short size = s[p].size(), i=0; queue<Node> q;
    while(i<size) {
        if (s[p][i] == '+' || s[p][i] == '-')
            q.push(Node(s[p][i++]=='+' ? 1 : 2));
        else if(s[p][i]>='A' && s[p][i]<='T') {
            short p1 = (s[p][i]-'A')*c + s[p][i+1]-'0';
            q.push(Node(3, p1));
            i += 2;
        } else {
            short val = 0;
            while(s[p][i]>='0' && s[p][i]<='9')
                val = val*10 + s[p][i++] - '0';
            q.push(Node(0, val));
        }
    }
    v[p]=0; short op=1;
    while(!q.empty()) {
        Node node = q.front(); q.pop();
        if(node.type == 3) {
            calc(node.val);
            op==1 ? v[p] += v[node.val] : v[p] -= v[node.val];
        }
        if(node.type == 0) 
            op==1 ? v[p] += node.val : v[p] -= node.val;
        else op = node.type;
    }
    f[p] = true;
}

int main()
{
    cout << setiosflags(ios::right);
    while(cin >> r >> c && r) {
        bool d[200][200] = {false}, inv[200][200] = {false}; t = r*c;
        for(short p=0; p<t; ++p) {
            cin >> s[p];
            f[p] = false;
            de(p, d, inv);
        }
        bool circle = false;
        for(short i=0; i<r; ++i)
            for(short j=0; j<c; ++j) {
                short p = i*c + j;
                if(d[p][p]) {
                    circle = true;
                    cout << setw(1) << char('A'+i) << char('0'+j) << ": " << s[p] << endl;
                }
            }
        if(!circle) {
            for(short p=0; p<t; ++p) if(!f[p]) calc(p);
            cout << setw(1) << ' ';
            for (short i=0; i<c; ++i) cout << setw(6) << i;
            cout << endl;
            for(short i=0; i<r; ++i) {
                cout << setw(1) << char('A' + i);
                for(short j=0; j<c; ++j) {
                    short p = i*c + j;
                    cout << setw(6) << v[p];
                }
                cout << endl;
            }
        }
        cout << endl;
    }
    return 0;
}