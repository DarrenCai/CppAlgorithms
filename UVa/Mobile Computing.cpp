/**
 * UVa1354/LA3403
 * 天平难题
 */

#include <iostream>
#include <set>
#include <iomanip>
using namespace std;

struct Node {
    short w; set<pair<double, double> > l;
    Node(short w1): w(w1) {}
};

double r, m; short s, w[6], a[5]; bool visit[6];

Node calc(Node& left, Node& right) {
    Node node(left.w + right.w);
    double t1 = 1.0*right.w/node.w;
    double t2 = 1.0*left.w/node.w;
    for (set<pair<double, double> >::iterator it=left.l.begin(); it!=left.l.end(); ++it) {
         for (set<pair<double, double> >::iterator it1=right.l.begin(); it1!=right.l.end(); ++it1) {
             double l1 = it->first + t1, l2 = it1->first - t2; if (l1<l2) l1 = l2;
             double r1 = it1->second + t2, r2 = it->second - t1; if (r1<r2) r1 = r2;
             node.l.insert(pair<double, double>(l1, r1));
         }
    }
    return node;
}

Node split(char f, char l) {
    Node node(0);
    if (l == 1) {
        node = Node(w[a[f]]);
        node.l.insert(pair<double, double>(0, 0));
    } else if (l == 2) {
        node = Node(w[a[f]] + w[a[f+1]]);
        node.l.insert(pair<double, double>(1.0*w[a[f+1]]/node.w, 1.0*w[a[f]]/node.w));
    } else {
        for (char i=1; i<l; ++i) {
            Node left = split(f, i);
            Node right = split(f+i, l-i);
            Node ret = calc(left, right);
            if (!node.w) node.w = ret.w;
            node.l.insert(ret.l.begin(), ret.l.end());
        }
    }
    return node;
}

void dfs(char cur) {
    if (cur == s) {
        for (char i=1; i<s; ++i) {
            Node left = split(0, i);
            Node right = split(i, s-i);
            Node ret = calc(left, right);
            for (set<pair<double, double> >::iterator it=ret.l.begin(); it!=ret.l.end(); ++it) {
                double t = it->first + it->second;
                if (t<=r && t>m) m = t;
            }
        }
    } else for (char i=0; i<s; ++i) {
        if (!visit[i]) {
            visit[i] = true;
            a[cur] = i;
            dfs(cur+1);
            visit[i] = false;
        }
    }
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    cout << setprecision(17); int n; cin>>n;
    while(n--) {
        m = -1; cin >> r >> s;
        for(char i=0; i<s; ++i) cin >> w[i];
        if (s==1) cout << 0 << endl;
        else if (r<1) cout << -1 << endl;
        else if (s == 2) cout << (r<1 ? -1 : 1) << endl;
        else {
            dfs(0);
            cout << m << endl;
        }
    }
    return 0;
}