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
    cout << 500 << endl;
    int count = 0;
    while(count++ < 500)
    {
        cout << endl;
        int m = rand()%10 + 1;
        int t0 = rand()%100 + 1;
        int q = t0;
        int t1 = rand()%100 + 1;
        if(t1 > q) q = t1;
        int t2 = rand()%100 + 1;
        if(t2 > q) q = t2;
        int t3 = rand()%100 + 1;
        if(t3 > q) q = t3;
        int t4 = rand()%100 + 1;
        if(t4 > q) q = t4;
        q += rand();
        cout << m << ' ' << t0 << ' ' << t1 << ' ' << ' ' << t2 << ' ' << t3 << ' ' << t4 << q << endl;
        for(int i=0; i<m; ++i){
            int t = rand()%25+1, unlock = t;
            for(int j=0; j<t-1 && j<=unlock; ++j){
                int op = rand()%4, a;
                char v;
                while(op == 2 && j==t-2) op = rand()%4;
                if(op == 2) {
                    unlock = rand()%(t-1-j) + j;
                }
                switch(op){
                    case 0:
                        v = 'a' + rand()%26;
                        a = rand()%100;
                        cout << v << " = " << a << endl;
                        break;
                    case 1:
                        v = 'a' + rand()%26;
                        cout << "print " << v << endl;
                        break;
                    case 2:
                        cout << "lock" << endl;
                        break;
                    case 3:
                        cout << "unlock" << endl;
                }
            }
            cout << "end" << endl;
        }
    }
    return 0;
} 