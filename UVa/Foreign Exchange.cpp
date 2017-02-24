/**
 * UVa10763
 * 交换学生
 */

#include <iostream>
#include <map>

int main()
{
    using namespace std;
    int n;
    while(cin>>n && n)
    {
        map<pair<int, int>, int> p;
        while(n--)
        {
            int a, b;
            cin >> a >> b;
            pair<int, int> e1(a, b), e2(b, a);
            if(p.count(e2))
            {
                p[e2]>1 ? --p[e2] : p.erase(e2);
            }
            else
            {
                p.count(e1) ? ++p[e1] : p[e1]=1;
            }
        }
        cout << (p.size() ? "NO":"YES") << endl;
    }
    return 0;
}