/**
 * UVa512
 * 跟踪电子表格中的单元格
 * 思路：将所有操作保存，然后对于每个查询重新执行每个操作，但不需要计算整个电子表格的变化，而只需关注所查询的单元格的位置变化
 */

#include <iostream>
#include <sstream>

int main()
{
    using namespace std;
    int R, C, count=0;
    while(cin >> R >> C && R && C)
    {
        if(count)
        {
            cout << endl;
        }
        cout << "Spreadsheet #" << ++count << endl;
        int n;
        cin >> n;
        const int N = n;
        string op[N];
        cin.get();
        for(int i=0; i<N; ++i)
        {
            getline(cin, op[i]);
        }
        cin >> n;
        while(n--)
        {
            int r, c, r1, c1;
            cin >> r >> c;
            r1 = r;
            c1 = c;
            for(int i=0; i<N; ++i)
            {
                stringstream ss(op[i]);
                string cmd;
                ss >> cmd;
                if(cmd[0] == 'E')
                {
                    int ra, ca, rb, cb;
                    ss >> ra >> ca >> rb >> cb;
                    if(r1==ra && c1==ca)
                    {
                        r1 = rb;
                        c1 = cb;
                    }
                    else if(r1==rb && c1==cb)
                    {
                        r1 = ra;
                        c1 = ca;
                    }
                }
                else
                {
                    int step = cmd[0]=='D' ? -1:1;
                    int A, rt=r1, ct=c1;
                    ss >> A;
                    while(A--)
                    {
                        int x;
                        ss >> x;
                        if(cmd[1]=='R' && x<=r1)
                        {
                            x==r1 && step==-1 ? rt=0 : rt+=step;
                        }
                        if(cmd[1]=='C' && x<=c1)
                        {
                            x==c1 && step==-1 ? ct=0 : ct+=step;
                        }
                    }
                    r1 = rt;
                    c1 = ct;
                }
            }
            cout << "Cell data in (" << r << ',' << c << ") ";
            if(r1<=0 || c1<=0)
            {
                cout << "GONE" << endl;
            }
            else
            {
                cout << "moved to (" << r1 << ',' << c1 << ')' << endl;
            }
        }
    }
    return 0;
}