/**
 * UVa1587
 * 盒子
 * 注意sort函数operator<的签名（返回值为bool，而不是int）
 */

#include <iostream>
#include <algorithm>

struct Rect
{
    int w, h;
    Rect()
    {
        w = 0;
        h = 0;
    }
    Rect(int a, int b)
    {
        if(a > b)
        {
            w = a;
            h = b;
        }
        else
        {
            w = b;
            h = a;
        }
    }
    bool operator<(const Rect& b) const
    {
        if(w > b.w)
        {
            return true;
        }
        if(h > b.h)
        {
            return true;
        }
        return false;
    }
    bool operator==(const Rect& b) const
    {
        return w==b.w && h==b.h;
    }
};

int main()
{
    using namespace std;
    Rect rect[6];
    int a, b, t=0;
    while(cin >> a >> b)
    {
        rect[t++] = Rect(a, b);
        if(t == 6)
        {
            sort(rect, rect+6);
            if(rect[0]==rect[1] && rect[2]==rect[3] && rect[4]==rect[5]
               && rect[0].w == rect[2].w && Rect(rect[0].h, rect[2].h) == rect[4])
            {
                cout << "POSSIBLE" << endl;
            }
            else
            {
                cout << "IMPOSSIBLE" << endl;
            }
            t = 0;
        }
    }
    return 0;
}