/**
 * UVa1368
 * DNA序列
 */

#include <iostream>
#include <string>

int main()
{
    using namespace std;
    int t;
    cin >> t;
    while(t--)
    {
        int m,n;
        cin >> m;
        cin >> n;
        const int M = m;
        const int N = n;
        const char* DNA = "ACGT";
        string s[M], r;
        for(int i=0; i<m; ++i)
        {
            cin >> s[i];
        }
        int d = 0;
        for(int i=0; i<n; ++i)
        {
            int count[4] = { 0 };
            for(int j=0; j<m; ++j)
            {
                switch(s[j][i])
                {
                    case 'A':
                        ++ count[0];
                        break;
                    case 'C':
                        ++ count[1];
                        break;
                    case 'G':
                        ++ count[2];
                        break;
                    case 'T':
                        ++ count[3];
                }
            }
            int p = 0;
            for(int k=1; k<4; ++k)
            {
                if(count[k] > count[p])
                {
                    p = k;
                }
            }
            r += DNA[p];
            d += m - count[p];
        }
        cout << r << endl << d << endl;
    }
    return 0;
}