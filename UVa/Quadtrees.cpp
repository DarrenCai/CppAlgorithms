/**
 * UVa297
 * 四分树
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

short sum(string& img, short s=1024) {
    char v = img.back(); img.pop_back();
    if(v == 'e')   return 0;
    if(v == 'f')   return s;
    s>>=2; return sum(img, s) + sum(img, s) + sum(img, s) + sum(img, s);
}

short add(string& img1, string& img2, short s=1024) {
    char v1 = img1.back(); img1.pop_back();
    char v2 = img2.back(); img2.pop_back();
    if(v1=='f' || v2=='f')    return s;
    s >>= 2;
    if(v1=='p' && v2=='p')    return add(img1, img2, s) + add(img1, img2, s) + add(img1, img2, s) + add(img1, img2, s);
    if(v1 == 'p')      return sum(img1, s);
    if(v2 == 'p')      return sum(img2, s);
    return 0;
}

int main()
{
    int t; cin >> t;
    while(t--) {
        string img1, img2; cin >> img1 >> img2;
        reverse(img1.begin(), img1.end()); reverse(img2.begin(), img2.end());
        cout << "There are " << add(img1, img2) << " black pixels." << endl;
    }
    return 0;
}