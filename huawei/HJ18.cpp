/**
 * HJ18 识别有效的IP地址和掩码并进行分类统计
 */

#include <iostream>
#include <sstream>
using namespace std;

int a = 0, b = 0, c = 0, d = 0, e = 0, err = 0, p = 0; istringstream s;

bool solve_item() {
    if (cin.eof() || cin.peek()<0) return false; 
    int nip = 0, ip[] = {-1, -1, -1, -1};
    while (cin.peek() != '~') {
        if (cin.peek() == '.') {
            cin.get();
            ++nip;
        } else cin >> ip[nip];
    }
    cin.get();
    long long mask = 0; bool er = false;
    while (cin.peek() != '\n') {
        if (cin.peek() == '.') cin.get();
        else {
            long long v; cin >> v;
            if (v>255) er = true;
            mask = mask<<8 | v;
        }
    }
    if (ip[0]!=0 && ip[0]!=127) {
        if (ip[0]<0 || ip[1]<0 || ip[2]<0 || ip[3]<0 || ip[0]>255 || ip[1]>255 || ip[2]>255 || ip[3]>255) er = true;
        if (mask==0 || mask==0xffffffff) {
            er = true;
        } else {
            long long f = 0xffffffff ^ ((mask & (-mask)) - 1);
            if ((f&mask) != f) er = true;
        }
        if (er)  {
            ++err;
        } else if (ip[0]>0 && ip[0]!=127) {
            if (ip[0]>0 && ip[0]<127) ++a;
            if (ip[0]>127 && ip[0]<192) ++b;
            if (ip[0]>191 && ip[0]<224) ++c;
            if (ip[0]>223 && ip[0]<240) ++d;
            if (ip[0]>239) ++e;
            if (ip[0]==10 || (ip[0]==172 && ip[1]>15 && ip[1]<32) || (ip[0]==192 && ip[1]==168)) ++p;
        }
    }
    cin.get();
    return true;
}

int main() {
    // freopen("in.txt", "r", stdin);
    while (solve_item());
    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << err << ' ' << p << endl;
}