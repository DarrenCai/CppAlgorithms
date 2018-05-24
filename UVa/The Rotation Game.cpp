/**
 * UVa1343
 * 旋转游戏
 */

#include <iostream>
#include <cstring>
using namespace std;

const short idx[][7] = {
    {0, 2, 6, 11, 15, 20, 22},      // A
    {1, 3, 8, 12, 17, 21, 23},      // B
    {10, 9, 8, 7, 6, 5, 4},         // C
    {19, 18, 17, 16, 15, 14, 13},   // D
    {23, 21, 17, 12, 8, 3, 1},      // E
    {22, 20, 15, 11, 6, 2, 0},      // F
    {13, 14, 15, 16, 17, 18, 19},   // G
    {4, 5, 6, 7, 8, 9, 10}          // H
};
const short c[] = {6, 7, 8, 11, 12, 15, 16, 17};
short s[24], depth; char rota[100];

int IDDFS(const short (&s)[24], short d=0, short pre=-1) {
    if (d == depth) {
        bool isSame = true;
        for (short i=0; isSame && i<7; ++i) if (s[c[i]] != s[c[i+1]]) isSame = false;
        if (isSame) return s[c[0]];
    } else {
        for (short i=0; i<8; ++i) {
            if (pre==-1 || (idx[pre][0]-idx[i][0]!=6 && idx[pre][0]-idx[i][0]!=-6 &&
                    idx[pre][0]-idx[i][0]!=22 && idx[pre][0]-idx[i][0]!=-22)) {
                rota[d] = 'A' + i;
                short ss[24]; memcpy(ss, s, sizeof(s));
                short l = ss[idx[i][0]];
                for (short j=0; j<6; ++j) ss[idx[i][j]] = ss[idx[i][j+1]];
                ss[idx[i][6]] = l;
                short count[4] = {0}, max = 0, ret;
                for (short j=0; j<8; ++j) ++ count[ss[c[j]]];
                for (short j=1; j<4; ++j) if (count[j] > max) max = count[j];
                if (d+9-max<=depth && (ret=IDDFS(ss, d+1, i))) return ret;
            }
        }
    }
    return 0;
}

int main()
{
    while (cin >> s[0] && s[0]) {
        for (short i=1; i<24; ++i) cin>>s[i];
        short ret; memset(rota, 0, 100); depth = 0;
        while (!(ret = IDDFS(s))) ++ depth;
        cout << (depth==0 ? "No moves needed" : rota) << endl << ret << endl;
    }
    return 0;
}