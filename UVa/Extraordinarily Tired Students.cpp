/**
 * UVa12108
 * 特别困的学生
 */

#include <iostream>

int main()
{
    using namespace std;
    int n, count=0;
    while(cin>>n && n)
    {
        const int N = n;
        int a[N], b[N], c[N], c0[N], s=0, t;
        while(n--)
        {
            cin >> a[n] >> b[n] >> c[n];
            c0[n] = c[n];
            if(c[n] > a[n])
            {
                ++ s;
            }
        }
        for(t=1; s>0; ++t)
        {
            for(int i=0; i<N; ++i)
            {
                if(c[i]==a[i]+b[i] || (c[i]==a[i] && s<=N-s))
                {
                    c[i] = 0;
                }
                ++ c[i];
            }
            bool flag = true;
            s = 0;
            for(int i=0; i<N; ++i)
            {
                if(c[i] > a[i])
                {
                    ++ s;
                }
                if(c[i] != c0[i])
                {
                    flag = false;
                }
            }
            if(flag)
            {
                break;
            }
        }
        cout << "Case " << ++count << ": " << (s==0 ? t:-1) << endl;
    }
    return 0;
}