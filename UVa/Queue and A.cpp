/**
 * UVa822
 * 客户中心模拟
 */

#include <iostream>
#include <set>
#include <tuple>
#include <vector>
#include <unordered_map>

#define max(a, b) (a>b ? a:b)

int main()
{
    using namespace std;
    int m, count = 0;
    while(cin>>m && m)
    {
        set<int> time;      // requests arriving time set
        unordered_map<int, tuple<int, int, int, int> > req;   // requests
        while(m--)
        {
            int id, n, t0, s, i;
            cin >> id >> n >> t0 >> s >> i;
            time.insert(t0);
            req[id] = tie(n, t0, s, i);
        }
        unordered_map<int, vector<int> > sr;      // staff-requests map
        unordered_map<int, int> savil;        // staff available time map
        unordered_map<int, int> saloc;        // staff alloc time map
        cin >> m;
        while(m--)
        {
            int id, n, tid;
            cin >> id >> n;
            while(n--)
            {
                cin >> tid;
                sr[id].push_back(tid);
            }
            savil[id] = 0;
            saloc[id] = -1;
        }
        bool fnsh = false;
        while(!fnsh)
        {
            int t = *time.begin();
            unordered_map<int, int> scr;      // staff choose request
            unordered_map<int, int> scn;      // staff needs to choose new request
            unordered_map<int, int> rs;       // request allocated to staff
            unordered_map<int, int> rrs;      // request re alloc to staff
            for(auto& s: savil)
            {
                if(s.second <= t)
                {
                    for(auto& r: sr[s.first])
                    {
                        if(req.count(r) && get<1>(req[r])<=t)
                        {
                            scr[s.first] = r;
                            break;
                        }
                    }
                }
            }
            do
            {
                rrs = rs;
                for(auto& x: scr)
                {
                    if(!rs.count(x.second))
                    {
                        rs[x.second] = x.first;
                    }
                    else
                    {
                        const int t1 = saloc[x.first];
                        const int t2 = saloc[rs[x.second]];
                        if(t1<t2 || (t1==t2 && x.first<rs[x.second]))
                        {
                            scn[rs[x.second]] = x.second;
                            rs[x.second] = x.first;
                        }
						else
						{
							scn[x.first] = x.second;
						}
                    }
                }
                scr.clear();
                for(auto& s: scn)
                {
                    auto iter = sr[s.first].begin();
                    while(*iter != s.second)
                    {
                        ++ iter;
                    }
                    while(++iter, iter!=sr[s.first].end())
                    {
                        if(req.count(*iter) && get<1>(req[*iter])<=t)
                        {
                            scr[s.first] = *iter;
                            break;
                        }
                    }
                }
                scn.clear();
            }while(!scr.empty() && rs!=rrs);
            for(auto& x: rs)
            {
                saloc[x.second] = t;
				savil[x.second] = t + get<2>(req[x.first]);
				get<1>(req[x.first]) += get<3>(req[x.first]);
                time.insert(get<1>(req[x.first]));
                time.insert(savil[x.second]);
                if(--get<0>(req[x.first]) == 0)
                {
				    req.erase(x.first);
                }
            }
            time.erase(time.begin());
            fnsh = req.empty();
        }
        int t = 0;
        for(auto& s: savil)
        {
            t = max(s.second, t);
        }
        cout << "Scenario " << ++count << ": All requests are serviced within " << t <<" minutes." << endl;
    }
    return 0;
}