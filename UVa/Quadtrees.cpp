/**
 * UVa297
 * 四分树
 */

#include <iostream>
#include <string>

using namespace std;

struct quadrant {
    private: string s; int p;
    public: quadrant():p(0){ cin >> s; }
    char cur(){ return s[p++]; }
    void skip(){ if(s[p++] == 'p')    skip(), skip(), skip(), skip(); }
};

short sum(quadrant& img, short s=1024) {
    char v = img.cur();
    if(v == 'e')   return 0;
    if(v == 'f')   return s;
    s>>=2; return sum(img, s) + sum(img, s) + sum(img, s) + sum(img, s);
}

short add(quadrant& img1, quadrant& img2, short s=1024) {
    char v1 = img1.cur(); char v2 = img2.cur();
    if(v1=='f' || v2=='f') {
        if(v1 == 'p')     img1.skip(), img1.skip(), img1.skip(), img1.skip();
        if(v2 == 'p')     img2.skip(), img2.skip(), img2.skip(), img2.skip();
        return s;
    }
    s >>= 2;
    if(v1=='p' && v2=='p')    return add(img1, img2, s) + add(img1, img2, s) + add(img1, img2, s) + add(img1, img2, s);
    if(v1 == 'p')      return sum(img1, s) + sum(img1, s) + sum(img1, s) + sum(img1, s);
    if(v2 == 'p')      return sum(img2, s) + sum(img2, s) + sum(img2, s) + sum(img2, s);
    return 0;
}

int main()
{
    int t; cin >> t;
    while(t--) {
        quadrant img1 = quadrant(), img2 = quadrant();
        cout << "There are " << add(img1, img2) << " black pixels." << endl;
    }
    return 0;
}