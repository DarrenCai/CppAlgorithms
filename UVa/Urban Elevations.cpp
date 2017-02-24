/**
 * UVa221
 * 城市正视图
 * 开始时代码提交结果总是RE，增加测试数据后调试定位在operator<这里。注意：自定义sort的比较函数时，要求比较函数必须是strict weak ordering。
 * 其英文解释为A Strict Weak Ordering is a Binary Predicate that compares two objects, returning true if the first precedes the second。
 * 也就是说，只有当第一个参数在第二个参数前的时候才返回真，其他均为假。因此要注意：在两个参数相等时，必须返回假。
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct b
{
    int id;
    float x, y, w, d, h;
    bool operator< (const b& o) const
    {
        return h>o.h || (h==o.h && y<o.y);      // 原来为优化而这样写 return h>o.h || (h==o.h && y<o.y+o.d); 仔细分析会发现这不满足strict weak ordering
    }
};

bool cmp(const b& e1, const b& e2)
{
    return e1.x<e2.x || (e1.x==e2.x && e1.y<e2.y);
}

int main()
{
    using namespace std;
    int n, count=0;
    while(cin>>n && n)
    {
        vector<b> s(n), r;
        vector<float> xs(n<<1);
        for(int i=0; i<n; ++i)
        {
            s[i].id = i+1;
            cin >> s[i].x >> s[i].y >> s[i].w >> s[i].d >> s[i].h;
            xs[i<<1] = s[i].x;
            xs[(i<<1)+1] = s[i].x+s[i].w;
        }
        sort(s.begin(), s.end());
        sort(xs.begin(), xs.end());
        const int m = unique(xs.begin(), xs.end()) - xs.begin();     // x坐标排序后去重，得到m个坐标
        if(count)
        {
            cout << endl;
        }
        cout << "For map #" << ++count << ", the visible buildings are numbered as follows:" << endl;
        for(int i=0; i<n; ++i)
        {
            bool visible = false;
            for(int j=0; !visible && j<m-1; ++j)
            {
                const float x = (xs[j] + xs[j+1]) / 2;
                if(x>=s[i].x && x<=s[i].x+s[i].w)
                {
                    bool flag = true;
                    for(int k=0; flag && k<i; ++k)
                    {
                        if(s[i].y>=s[k].y+s[k].d && x>=s[k].x && x<=s[k].x+s[k].w)
                        {
                            flag = false;
                        }
                    }
                    if(flag)
                    {
                        visible = true;
                    }
                }
            }
            if(visible)
            {
                r.push_back(s[i]);
            }
        }
        sort(r.begin(), r.end(), cmp);
        cout << r[0].id;
        const int size = r.size();
        for(int i=1; i<size; ++i)
        {
            cout << ' ' << r[i].id;
        }
        cout << endl;
    }
    return 0;
}