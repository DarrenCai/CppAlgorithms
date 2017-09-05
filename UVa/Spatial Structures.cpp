/**
 * UVa806
 * 空间结构
 * 再次验证了题目给的数据范围不可尽信，特别是<、>这种，至少要把等号考虑进去，变成<=、>=来处理
 */

#include <iostream>
#include <set>
char img[64][64];

int main()
{
    using namespace std;
    const short weight[] = {1, 5, 25, 125, 625, 3125};
    const short len[] = {1, 4, 16, 64, 256, 1024};
    const short idx[] = {0, 1, 5, 21, 85, 341};
    short serial[1365] = {0};
    for (short i=0; i<5; ++i) {
        for (short j=0; j<len[i]; ++j) {
            short t = j << 2;
            serial[idx[i+1]+t] = serial[idx[i]+j] + weight[i];
            serial[idx[i+1]+t+1] = serial[idx[i]+j] + 2*weight[i];
            serial[idx[i+1]+t+2] = serial[idx[i]+j] + 3*weight[i];
            serial[idx[i+1]+t+3] = serial[idx[i]+j] + 4*weight[i];
        }
    }
    int n, kase=0;
    while (cin >> n && n) {
        if (kase) cout << endl;
        cout << "Image " << ++kase << endl;
        if (n > 0) {
            for (short i = 0; i < n; ++i)
                for (short j = 0; j < n; ++j) cin >> img[i][j];
            short lv = 0, t=n; while(t>1) t>>=1, ++lv;
            if (lv==0) {
                if (img[0][0]=='1') cout << 0 << endl;
                cout << "Total number of black nodes = " << (img[0][0]=='1' ? 1 : 0) << endl;
                continue;
            }
            bool b[3125]={0}; set<short> black;
            for (short i=0; i<len[lv-1]; ++i) {
                short d=5, w=4, r=0, c=0, index=idx[lv-1]+i, v=serial[index];
                do {
                    short k = v / weight[w];
                    if (k) {
                        short t = n >> d;
                        if (k==2 || k==4) c += t;
                        if (k>2) r += t;
                    }
                    v%=weight[w]; --w; --d;
                } while(v);
                if (img[r][c]=='1' && img[r][c+1]=='1' && img[r+1][c]=='1' && img[r+1][c+1]=='1') {
                    b[serial[index]] = true;
                } else {
                    if (img[r][c]=='1') black.insert(serial[index]+weight[lv-1]);
                    if (img[r][c+1]=='1') black.insert(serial[index]+2*weight[lv-1]);
                    if (img[r+1][c]=='1') black.insert(serial[index]+3*weight[lv-1]);
                    if (img[r+1][c+1]=='1') black.insert(serial[index]+4*weight[lv-1]);
                }
            }
            for (short i=lv-2; i>=0; --i)
                for (short j=0; j<len[i]; ++j) {
                    short index=idx[i]+j, k1=serial[index]+weight[i], k2=serial[index]+2*weight[i],
                          k3=serial[index]+3*weight[i], k4=serial[index]+4*weight[i];
                    if (b[k1] && b[k2] && b[k3] && b[k4]) {
                        b[serial[index]] = true;
                    } else {
                        if (b[k1]) black.insert(k1);
                        if (b[k2]) black.insert(k2);
                        if (b[k3]) black.insert(k3);
                        if (b[k4]) black.insert(k4);
                    }
                }
            if (b[0]) black.insert(0);
            if (!black.empty()) {
                short i=0;
                cout << *black.begin();
                set<short>::iterator it = black.begin();
                while(++it != black.end()) {
                    if (++i % 12 == 0) cout << endl << *it;
                    else cout << ' ' << *it;
                }
                cout << endl;
            }
            cout << "Total number of black nodes = " << black.size() << endl;
        } else {
            n = -n;
            for (short i=0; i<n; ++i)
                for (short j=0; j<n; ++j) img[i][j] = '.';
            short v, d, w, r, c, l;
            while (cin>>v && v!=-1) {
                d=6, w=5, r=c=0, l=n;
                do {
                    short k = v / weight[w];
                    if (k) {
                        short t = n >> d;
                        if (l==n) l = t;
                        if (k==2 || k==4) c += t;
                        if (k>2) r += t;
                    }
                    v%=weight[w]; --w; --d;
                } while(v);
                for (short i=0; i<l; ++i)
                    for (short j=0; j<l; ++j) img[r+i][c+j] = '*';
            }
            for (short i=0; i<n; ++i) {
                for (short j=0; j<n; ++j) cout << img[i][j];
                cout << endl;
            }
        }
    }
    return 0;
}