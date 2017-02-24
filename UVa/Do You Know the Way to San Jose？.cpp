/**
 * UVa511
 * 地图查询
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

map<string, pair<float, float> > locs;
string loc;

struct Map
{
    string name;
    float x1, y1, x2, y2;
    
    Map(const string& loc, const float vx1, const float vy1,
        const float vx2, const float vy2): name(loc)
    {
        x1 = vx1<vx2 ? vx1 : vx2;
        x2 = vx2<vx1 ? vx1 : vx2;
        y1 = vy1<vy2 ? vy1 : vy2;
        y2 = vy2<vy1 ? vy1 : vy2;
    }
    float area() const
    {
        return (x2-x1)*(y2-y1);
    }
    bool contains(const pair<float, float>& point) const
    {
        return point.first>=x1 && point.first<=x2 && point.second>=y1 && point.second<=y2;
    }
};

bool cmp(const Map& a, const Map& b)
{
    const float locx = locs[loc].first;
    const float locy = locs[loc].second;
    const float acx = (a.x1 + a.x2) / 2;
    const float acy = (a.y1 + a.y2) / 2;
    const float bcx = (b.x1 + b.x2) / 2;
    const float bcy = (b.y1 + b.y2) / 2;
	float da = (locx - acx)*(locx - acx) + (locy - acy)*(locy - acy);
	float db = (locx - bcx)*(locx - bcx) + (locy - bcy)*(locy - bcy);
    if(da != db)
    {
		return da < db;
    }
    float ratioa = (a.x1 - a.x2) / (a.y1 - a.y2);
    ratioa -= ratioa > 0.75 ? ratioa-0.75 : 0.75-ratioa;
    float ratiob = (b.x1 - b.x2) / (b.y1 - b.y2);
    ratiob -= ratiob > 0.75 ? ratiob-0.75 : 0.75-ratiob;
    if(ratioa != ratiob)
    {
		return ratioa < ratiob;
    }
	da = (locx - a.x2)*(locx - a.x2) + (locy - a.y1)*(locy - a.y1);
	db = (locx - b.x2)*(locx - b.x2) + (locy - b.y1)*(locy - b.y1);
    if(da != db)
    {
        return da > db;
    }
    return a.x1 < b.x1;
}

int main()
{
    cin >> loc;
	map<float, vector<Map>, greater<float> > maps;
    while(cin>>loc && loc!="LOCATIONS")
    {
        float x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Map m(loc, x1, y1, x2, y2);
        maps[m.area()].push_back(m);
    }
    while(cin>>loc && loc!="REQUESTS")
    {
        float x, y;
        cin >> x >> y;
        locs[loc] = make_pair(x, y);
    }
    map<string, vector<Map> > res;
    while(cin>>loc && loc!="END")
    {
        int lv;
        cin >> lv;
        cout << loc << " at detail level " << lv;
        if(!locs.count(loc))
        {
            cout << " unknown location" << endl;
            continue;
        }
        if(!res.count(loc))
        {
            for(auto& x: maps)
            {
                Map* best = nullptr;
                for(auto& m: x.second)
                {
                    if(m.contains(locs[loc]) && (!best || (best && cmp(m, *best))))
                    {
                        best = &m;
                    }
                }
                if(best)
                {
                    res[loc].push_back(*best);
                }
            }
        }
        if(res.count(loc))
        {
            const int size = res[loc].size();
            if(size < lv)
            {
                cout << " no map at that detail level; using " << res[loc][size-1].name << endl;
            }
            else
            {
                cout << " using " << res[loc][lv-1].name << endl;
            }
        }
        else
        {
            cout << " no map contains that location" << endl;
        }
    }
    return 0;
}