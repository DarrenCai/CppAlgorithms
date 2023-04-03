/**
 * UVa1300/LA2344
 * Tehran 2001
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <set>
using namespace std;

#define M 30
#define N 12
string va[M], al[M], ar[M], vb[M], bl[M], br[M]; char oa[M], ob[M];
struct cmd {int var, op1, op2; bool num1, num2, add;} cmda[M], cmdb[M];
struct ex {double v[N], ra1, ra2, rb1, rb2, p;} f[M<<2][M<<2][2];

void read(string& s, char& op) {
    char c; cin >> c;
    if (c == ':') cin >> c >> c;
    if (c == '+' || c == '-') op = c, cin >> c;
    s = tolower(c);
    while (c = cin.get()) {
        if (c == '+' || c == '-') {
            op = c;
            return;
        }
        if (c == ' ' || c == '\t' || c == '\n') return;
        if (c == ':') {
            cin >> c;
            return;
        }
        s += tolower(c);
    }
}

void solve() {
    set<string> vars; bool isa = true; int m = 0, n = 0;
    while (true) {
        string& s = isa ? va[m] : vb[n];
        read(s, isa ? oa[m] : ob[n]);
        if (s == "end") {
            if (isa) isa = false;
            else break;
            continue;
        }
        vars.insert(s);
        string& sl = isa ? al[m] : bl[n];
        read(sl, isa ? oa[m] : ob[n]);
        if (isalpha(sl[0])) vars.insert(sl);
        string& sr = isa ? ar[m] : br[n];
        read(sr, isa ? oa[m] : ob[n]);
        if (isalpha(sr[0])) vars.insert(sr);
        isa ? ++m : ++n;
    }
    for (int i=0; i<m; ++i) {
        cmda[i].var = distance(vars.begin(), vars.find(va[i]));
        cmda[i].num1 = !isalpha(al[i][0]);
        cmda[i].op1 = cmda[i].num1 ? atoi(al[i].c_str()) : distance(vars.begin(), vars.find(al[i]));
        cmda[i].add = oa[i] == '+';
        cmda[i].num2 = !isalpha(ar[i][0]);
        cmda[i].op2 = cmda[i].num2 ? atoi(ar[i].c_str()) : distance(vars.begin(), vars.find(ar[i]));
    }
    for (int i=0; i<n; ++i) {
        cmdb[i].var = distance(vars.begin(), vars.find(vb[i]));
        cmdb[i].num1 = !isalpha(bl[i][0]);
        cmdb[i].op1 = cmdb[i].num1 ? atoi(bl[i].c_str()) : distance(vars.begin(), vars.find(bl[i]));
        cmdb[i].add = ob[i] == '+';
        cmdb[i].num2 = !isalpha(br[i][0]);
        cmdb[i].op2 = cmdb[i].num2 ? atoi(br[i].c_str()) : distance(vars.begin(), vars.find(br[i]));
    }
    int t = vars.size(), a = m<<2, b = n<<2;
    for (int i=0; i<=a; ++i) for (int j=0; j<=b; ++j) {
        if (i > 0) {
            ex &e0 = f[i-1][j][0], &e1 = f[i-1][j][1], &e = f[i][j][0];
            double p = j==b ? 1. : .5, q = e0.p + e1.p; cmd &c = cmda[(i-1)>>2];
            for (int k=0; k<t; ++k) e.v[k] = (e0.p*e0.v[k] + e1.p*e1.v[k]) / q;
            e.ra1 = (e0.p*e0.ra1 + e1.p*e1.ra1) / q; e.ra2 = (e0.p*e0.ra2 + e1.p*e1.ra2) / q;
            e.rb1 = (e0.p*e0.rb1 + e1.p*e1.rb1) / q; e.rb2 = (e0.p*e0.rb2 + e1.p*e1.rb2) / q;
            e.p = p * q;
            switch (i&3) {
                case 0:
                    e.v[c.var] = e.ra1;
                    break;
                case 1:
                    e.ra1 = c.num1 ? c.op1 : e.v[c.op1];
                    break;
                case 2:
                    e.ra2 = c.num2 ? c.op2 : e.v[c.op2];
                    break;
                case 3:
                    e.ra1 += c.add ? e.ra2 : -e.ra2;
                    break;
            }
        } else {
            ex &e = f[i][j][0];
            for (int k=0; k<t; ++k) e.v[k] = 0.;
            e.ra1 = e.ra2 = e.rb1 = e.rb2 = e.p = 0.;
            if (j == 0) e.p = 1.;
        }
        if (j > 0) {
            ex &e0 = f[i][j-1][0], &e1 = f[i][j-1][1], &e = f[i][j][1];
            long double p = i==a ? 1. : .5, q = e0.p + e1.p; cmd &c = cmdb[(j-1)>>2];
            for (int k=0; k<t; ++k) e.v[k] = (e0.p*e0.v[k] + e1.p*e1.v[k]) / q;
            e.ra1 = (e0.p*e0.ra1 + e1.p*e1.ra1) / q; e.ra2 = (e0.p*e0.ra2 + e1.p*e1.ra2) / q;
            e.rb1 = (e0.p*e0.rb1 + e1.p*e1.rb1) / q; e.rb2 = (e0.p*e0.rb2 + e1.p*e1.rb2) / q;
            e.p = p * q;
            switch (j&3) {
                case 0:
                    e.v[c.var] = e.rb1;
                    break;
                case 1:
                    e.rb1 = c.num1 ? c.op1 : e.v[c.op1];
                    break;
                case 2:
                    e.rb2 = c.num2 ? c.op2 : e.v[c.op2];
                    break;
                case 3:
                    e.rb1 += c.add ? e.rb2 : - e.rb2;
                    break;
            }
        } else {
            ex &e = f[i][j][1];
            for (int k=0; k<t; ++k) e.v[k] = 0.;
            e.ra1 = e.ra2 = e.rb1 = e.rb2 = e.p = 0.;
        }
    }
    ex &e0 = f[a][b][0], &e1 = f[a][b][1];
    for (int i=0; i<t; ++i) cout << e0.p*e0.v[i] + e1.p*e1.v[i] << endl;
    cout << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    cout << fixed << setprecision(4);
    int t; cin >> t;
    while (t--) solve();
}