/**
 * UVa10976
 * 分数拆分
 */

#include <iostream>
#include <vector>

int main() {
    using namespace std;
    short k;
    while(cin >> k) {
        vector<pair<int, short> > v; short m=k<<1;
        for(short y=k+1; y<=m; ++y) {
            int p = k*y; short s = y-k;
            if (p % s == 0)
                v.push_back(pair<int, short>(p / s, y));
        }
        cout << v.size() << endl;
        for(short i=0; i<v.size(); ++i)
            cout << "1/" << k << " = 1/" << v[i].first << " + 1/" << v[i].second << endl;
    }
    return 0;
}