/**
 * UVa1533
 * 移动小球
 * 注意：题目没交代找字典序最小，但实际要找字典序最小
 */

#include <iostream>
using namespace std;

short depth, dir,
    len[][6] = {{},
        {4, 4, 0, 0, 0, 0},
        {3, 3, 1, 1, 0, 0},
        {3, 3, 1, 1, 0, 0},
        {2, 2, 2, 2, 0, 0},
        {2, 2, 1, 1, 1, 1},
        {2, 2, 2, 2, 0, 0},
        {3, 3, 1, 1, 0, 0},
        {2, 2, 1, 1, 1, 1},
        {2, 2, 1, 1, 1, 1},
        {3, 3, 1, 1, 0, 0},
        {4, 4, 0, 0, 0, 0},
        {3, 3, 1, 1, 0, 0},
        {2, 2, 2, 2, 0, 0},
        {3, 3, 1, 1, 0, 0},
        {4, 4, 0, 0, 0, 0}
    },
    reach[][6][4] = {{},
        {{2, 4, 7, 11}, {3, 6, 10, 15}},
        {{4, 7, 11}, {5, 9, 14}, {1}, {3}},
        {{5, 8, 12}, {6, 10, 15}, {1}, {2}},
        {{2, 1}, {5, 6}, {7, 11}, {8, 13}},
        {{8, 12}, {9, 14}, {2}, {3}, {4}, {6}},
        {{3, 1}, {5, 4}, {9, 13}, {10, 15}},
        {{4, 2, 1}, {8, 9, 10}, {11}, {12}},
        {{5, 3}, {9, 10}, {4}, {13}, {12}, {7}},
        {{5, 2}, {8, 7}, {6}, {10}, {14}, {13}},
        {{6, 3, 1}, {9, 8, 7}, {14}, {15}},
        {{7, 4, 2, 1}, {12, 13, 14, 15}},
        {{8, 5, 3}, {13, 14, 15}, {11}, {7}},
        {{12, 11}, {8, 4}, {9, 6}, {14, 15}},
        {{9, 5, 2}, {13, 12, 11}, {15}, {10}},
        {{10, 6, 3, 1}, {14, 13, 12, 11}}};
unsigned short h, path[20];

bool iddfs(unsigned short cur, short step = 0);

bool move(const unsigned short& cur, const short& step, const short& p, const short (&s)[4], const short& l, short i=1) {
    if (i == l) return false;
    if (!(cur & 1<<s[i])) {
        path[step] = p<<4 | s[i];
        unsigned short cc = cur ^ 1<<p;
        for (short j=0; j<=i; ++j) cc ^= 1<<s[j];
        return iddfs(cc, step+1);
    } else return move(cur, step, p, s, l, i+1);
}

bool iddfs(unsigned short cur, short step) {
    if (step < depth)
        for (unsigned short i=1, cc, j; i<16; ++i)
            if (cur & 1<<i)
                for (unsigned short j=0; j<6 && len[i][j]>1; ++j)
                    if (cur & 1<<reach[i][j][0] && move(cur, step, i, reach[i][j], len[i][j])) return true;
    return cur == 1<<h;
}

int main()
{
    short t; cin >> t;
    while (t--) {
        unsigned short s = 0xfffe; cin>>h; s ^= 1<<h; for (depth=6; !iddfs(s); ++depth);
        cout << depth << endl; for (short i=0; i<depth-1; ++i) cout << (path[i]>>4) << ' ' << (path[i]&15) << ' ';
        cout << (path[depth-1]>>4) << ' ' << (path[depth-1]&15) << endl;
    }
    return 0;
}