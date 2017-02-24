/**
 * UVa1592
 * 数据库
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

int main()
{
    using namespace std;
    int m, n;
    while(cin>>m>>n)
    {
        cin.get();
        string s;
        map<string, int> IDcache;
        map<pair<int, int>, int> Rows;
        vector<vector<int> > db(m, vector<int>());
        for(int i=0; i<m; ++i)
        {
            getline(cin, s);
            s.append(",");
            int a=0, b;
            while((b = s.find(',', a)) != string::npos)
            {
                string ss = s.substr(a, b-a);
                if(!IDcache.count(ss))
                {
                    IDcache[ss] = IDcache.size();
                }
                db[i].push_back(IDcache[ss]);
                a = b+1;
            }
        }
        bool bPNF = true;
        for(int c1=0; bPNF && c1<n-1; ++c1)
        {
            for(int c2=c1+1; bPNF && c2<n; ++c2)
            {
                Rows.clear();   //遍历完两列清空一次;否则接着上次循环中保存的值,答案会错
                for(int r=0; bPNF && r<m; ++r)
                {
                    pair<int, int> p(db[r][c1], db[r][c2]);
                    if(!Rows.count(p))
                    {
                        Rows[p] = r;
                    }
                    else
                    {
                        cout << "NO" << endl << Rows[p]+1 << ' ' << r+1 << endl << c1+1 << ' ' << c2+1 << endl;
                        bPNF = false;
                    }
                }
            }
        }
        if(bPNF)
        {
            cout << "YES" << endl;
        }
    }
    return 0;
}