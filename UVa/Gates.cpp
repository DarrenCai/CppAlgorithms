/**
 * UVa1607
 * 与非门电路
 */

#include <iostream>
using namespace std;

#define M 200005
int net[M][2], n, m, mid; bool out[M];

void calc() {
    for (int i=1; i<=m; ++i) {
        bool a = net[i][0] < 0 ? net[i][0]+mid>=0 : out[net[i][0]];
        bool b = net[i][1] < 0 ? net[i][1]+mid>=0 : out[net[i][1]];
        out[i] = !(a&&b);
    }
}

int main()
{
    int d; cin >> d;
    while (d--) {
        cin >> n >> m;
        for (int i=1; i<=m; ++i) cin >> net[i][0] >> net[i][1];
        int low = mid = 0; calc(); bool a = out[m];
        int high = mid = n+1; calc(); bool b = out[m];
        if (a != b) while (low <= high) {
            mid = (low + high) / 2; calc();
            out[m] == b ? high = mid - 1 : low = mid + 1;
        }
        for (int i=1; i<=n; ++i) i==low ? cout << 'x' : cout << (i<low ? 1 : 0);
        cout << endl;
    }
    return 0;
}