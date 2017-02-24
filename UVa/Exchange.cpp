/**
 * UVa 1598
 * 交易所
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;
unordered_map<int, pair<int, int> > buyOrder;
unordered_map<int, pair<int, int> > sellOrder;
struct buyCmp
{
    bool operator()(int a, int b) const
    {
        if (buyOrder[a].first < buyOrder[b].first)
            return false;
        if (buyOrder[a].first > buyOrder[b].first)
            return true;
        return a < b;
    }
};
struct sellCmp
{
    bool operator()(int a, int b) const
    {
        if (sellOrder[a].first < sellOrder[b].first)
            return true;
        if (sellOrder[a].first > sellOrder[b].first)
            return false;
        return a < b;
    }
};

int main()
{
    #define min(a, b) (a < b ? a : b)

    int n, count = 0;
    while(cin >> n)
    {
        if(count ++)
            cout << endl;
        set<int, buyCmp> buyQueue;
        set<int, sellCmp> sellQueue;
        map<int, int> bid;
        map<int, int> ask;

        buyOrder.clear();
        sellOrder.clear();
        ask[99999] = 0;
        bid[0] = 0;

        for (int i = 1; i <= n; ++i)
        {
            string op;
            cin >> op;
            switch (op[0])
            {
                case 'B':
                {
                    int q, p;
                    cin >> q >> p;
                    for (auto it=sellQueue.begin(); it != sellQueue.end();)
                    {
                        int x = *it;
                        if (sellOrder[x].first > p)
                            break;
                        int t = min(q, sellOrder[x].second);
                        cout << "TRADE " << t << " " << sellOrder[x].first << endl;
                        ask[sellOrder[x].first] -= t;
                        if (ask[sellOrder[x].first] == 0)
                            ask.erase(sellOrder[x].first);
                        sellOrder[x].second > t ? (++it, sellOrder[x].second -= t) : (it=sellQueue.erase(it), sellOrder.erase(x));
                        q -= t;
                        if (q == 0)
                            break;
                    }
                    if (q != 0)
                    {
                        bid.count(p) ? bid[p] += q : bid[p] = q;
                        buyOrder[i] = make_pair(p, q);
                        buyQueue.insert(i);
                    }
                    break;
                }
                case 'C':
                {
                    int id;
                    cin >> id;
                    if(buyOrder.count(id))
                    {
                        buyQueue.erase(id);
                        int p = buyOrder[id].first;
                        int q = buyOrder[id].second;
                        buyOrder.erase(id);
                        bid[p] > q ? bid[p] -= q : bid.erase(p);
                    }
                    if(sellOrder.count(id))
                    {
                        sellQueue.erase(id);
                        int p = sellOrder[id].first;
                        int q = sellOrder[id].second;
                        sellOrder.erase(id);
                        ask[p] > q ? ask[p] -= q : ask.erase(p);
                    }
                    break;
                }
                case 'S':
                {
                    int q, p;
                    cin >> q >> p;
                    map<int, int> trade;
                    for (auto it=buyQueue.begin(); it != buyQueue.end();)
                    {
                        int x = *it;
                        if (buyOrder[x].first < p)
                            break;
                        int t = min(q, buyOrder[x].second);
                        cout << "TRADE " << t << " " << buyOrder[x].first << endl;
                        bid[buyOrder[x].first] -= t;
                        if (bid[buyOrder[x].first] == 0)
                            bid.erase(buyOrder[x].first);
                        buyOrder[x].second > t ? (++it, buyOrder[x].second -= t) : (it=buyQueue.erase(it), buyOrder.erase(x));
                        q -= t;
                        if (q == 0)
                            break;
                    }
                    if (q != 0)
                    {
                        ask.count(p) ? ask[p] += q : ask[p] = q;
                        sellOrder[i] = make_pair(p, q);
                        sellQueue.insert(i);
                    }
                    for(auto it=trade.rbegin(); it!=trade.rend(); ++it)
                        cout << "TRADE " << it->second << " " << it->first << endl; 
                }
            }
            cout << "QUOTE " << bid.rbegin()->second << " " << bid.rbegin()->first << " - " << ask.begin()->second << " " << ask.begin()->first << endl;
        }
    }

    return 0;
}