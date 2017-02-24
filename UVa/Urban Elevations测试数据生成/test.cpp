/*
 * 假定矩形是用一对点表达的(minx, miny) (maxx, maxy)，那么两个矩形
 *     rect1{(minx1, miny1)(maxx1, maxy1)}
 *     rect2{(minx2, miny2)(maxx2, maxy2)}  
 * 相交的结果一定是个矩形，构成这个相交矩形rect{(minx, miny) (maxx, maxy)}的点对坐标是：  
 *     minx   =   max(minx1,   minx2)  
 *     miny   =   max(miny1,   miny2)  
 *     maxx   =   min(maxx1,   maxx2)  
 *     maxy   =   min(maxy1,   maxy2)  
 *  
 * 如果两个矩形不相交，那么计算得到的点对坐标必然满足：  
 *    （ minx  >  maxx ） 或者 （ miny  >  maxy ） 
 *
 * 判定是否相交，以及相交矩形是什么都可以用这个方法一体计算完成。
 *
 * 从这个算法的结果上，我们还可以简单的生成出下面的两个内容：
 *     ㈠ 相交矩形：  (minx, miny) (maxx, maxy)
 *     ㈡ 面积： 面积的计算可以和判定一起进行
 *        if ( minx>maxx ) return 0;
 *        if ( miny>maxy ) return 0;
 *        return (maxx-minx)*(maxy-miny)
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
//#include<ctime>

#define max(a, b) (a>b ? a:b)
#define min(a, b) (a<b ? a:b)

struct b
{
    int x, y, w, d, h;
    b():x(0), y(0), w(0), d(0), h(0) {}
};

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    //srand(unsigned(time(0)));
    int count = 0;
    while(count++ < 500)
    {
        int n = 0;
        while(n == 0)
        {
            n = rand() % 101;
        }
        cout << n << endl;
        vector<b> s;
        while(s.size() < n)
        {
            b x;
            x.x = rand();
            x.y = rand();
            while(x.w == 0)
            {
                x.w = rand();
            }
            while(x.d == 0)
            {
                x.d = rand();
            }
            while(x.h == 0)
            {
                x.h = rand();
            }
            bool flag = true;
            for(auto t: s)
            {
                auto minx = max(x.x, t.x);
                auto miny = max(x.y, t.y);
                auto maxx = min(x.x+x.w, t.x+t.w);
                auto maxy = min(x.y+x.d, t.y+t.d);
                if(minx<maxx && miny<maxy)
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                s.push_back(x);
                cout << x.x << ' ' << x.y << ' ' << x.w << ' ' << x.d << ' ' << x.h << endl;
            }
        }
        cout << endl;
    }
    cout << 0 << endl;
    return 0;
} 