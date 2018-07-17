/**
 * UVa12113
 * 重叠的正方形
 */

#include <iostream>
#include <queue>
#include <set>
using namespace std;

queue<long long> q; set<long long> s;

void bfs() {
    for (char n=0; n<6; ++n)
        for (int i=q.size(); i; --i) {
            long long f = q.front(); q.pop();
            for (char r=0; r<3; ++r)
                for (char c=0; c<3; ++c) {
                    long long ff = f, one = 1, o = (r<<3)+r+c;
                    ff |= one<<o; ff |= one<<(o+1);
                    ff |= one<<(o+4); ff |= one<<(o+13);
                    ff |= one<<(o+18); ff |= one<<(o+19);
                    ff |= one<<(o+6); ff |= one<<(o+15);
                    ff ^= ff & (one<<(o+5));
                    ff ^= ff & (one<<(o+14));
                    ff ^= ff & (one<<(o+9));
                    ff ^= ff & (one<<(o+10));
                    if (!s.count(ff)) q.push(ff), s.insert(ff);
                }
        }
}

int main()
{
    q.push(0);
    bfs();
    short k = 0;
    while (true) {
        long long f = 0, one = 1;
        for (char r=0; r<5; ++r) {
            for (char c=0; c<10; ++c) {
                char ch = cin.get();
                if (ch == '0') return 0;
                if (ch == '_')
                    f |= c&1 ? one<<((r<<3)+r+(c>>1)) : 0x10000000000;
                if (ch == '|')
                    f |= !r || c&1 ? 0x10000000000 : one<<((r<<3)+r+(c>>1)-5);
            }
            cin.get();
        }
        cout << "Case " << ++k << ": " << (s.count(f) ? "Yes" : "No") << endl;
    }
    return 0;
}