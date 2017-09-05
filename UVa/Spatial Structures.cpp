/**
 * UVa806
 * 空间结构
 */

#include <iostream>
#include <set>
char img[32][32];

int main()
{
    using namespace std;
    const short weight[5] = {1, 5, 25, 125, 625};
    const short len[5] = {1, 4, 16, 64, 256};
    short* serial[5];
    serial[0] = new short[1]();
    for (char i=1, w=1; i<5; ++i, w*=5) {
        serial[i] = new short[len[i]];
        for (short j=0; j<len[i-1]; ++j) {
            short t = j << 2;
            serial[i][t] = serial[i-1][j] + w;
            serial[i][t+1] = serial[i-1][j] + 2*w;
            serial[i][t+2] = serial[i-1][j] + 3*w;
            serial[i][t+3] = serial[i-1][j] + 4*w;
        }
    }
    int n, c=0;
    while (cin >> n && n) {
        if (c) cout << endl;
        cout << "Image " << ++c << endl;
        if (n > 0) {
            for (char i = 0; i < n; ++i)
                for (char j = 0; j < n; ++j) cin >> img[i][j];
            char lv = 0, t=n; while(t>1) t>>=1, ++lv;
            if (lv==0) {
                if (img[0][0]=='1') cout << 0 << endl;
                cout << "Total number of black nodes = " << (img[0][0]=='1' ? 1 : 0) << endl;
                continue;
            }
            bool b[625]={0}; set<short> black;
            for (short i=0; i<len[lv-1]; ++i) {
                short d=4, w=125, r=0, c=0, v=serial[lv-1][i];
                do {
                    short k = v / w;
                    if (k) {
                        short t = n >> d;
                        if (k==2 || k==4) c += t;
                        if (k>2) r += t;
                    }
                    v%=w; w/=5; --d;
                } while(v);
                if (img[r][c]=='1' && img[r][c+1]=='1' && img[r+1][c]=='1' && img[r+1][c+1]=='1') {
                    b[serial[lv-1][i]] = true;
                } else {
                    if (img[r][c]=='1') black.insert(serial[lv-1][i]+weight[lv-1]);
                    if (img[r][c+1]=='1') black.insert(serial[lv-1][i]+2*weight[lv-1]);
                    if (img[r+1][c]=='1') black.insert(serial[lv-1][i]+3*weight[lv-1]);
                    if (img[r+1][c+1]=='1') black.insert(serial[lv-1][i]+4*weight[lv-1]);
                }
            }
            for (char i=lv-2; i>=0; --i)
                for (short j=0; j<len[i]; ++j) {
                    short k1=serial[i][j]+weight[i], k2=serial[i][j]+2*weight[i],
                          k3=serial[i][j]+3*weight[i], k4=serial[i][j]+4*weight[i];
                    if (b[k1] && b[k2] && b[k3] && b[k4]) {
                        b[serial[i][j]] = true;
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
            for (char i=0; i<n; ++i)
                for (char j=0; j<n; ++j) img[i][j] = '.';
            short v, d, w, r, c, l;
            while (cin>>v && v!=-1) {
                d=5, w=625, r=c=0, l=n;
                do {
                    short k = v / w;
                    if (k) {
                        short t= n >> d;
                        if (l==n) l = t;
                        if (k==2 || k==4) c += t;
                        if (k>2) r += t;
                    }
                    v%=w; w/=5; --d;
                } while(v);
                for (char i=0; i<l; ++i)
                    for (char j=0; j<l; ++j) img[r+i][c+j] = '*';
            }
            for (char i=0; i<n; ++i) {
                for (char j=0; j<n; ++j) cout << img[i][j];
                cout << endl;
            }
        }
    }
    for (char i=0; i<5; ++i) delete[] serial[i];
    return 0;
}