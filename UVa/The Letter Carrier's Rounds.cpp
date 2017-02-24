/**
 * UVa814
 * 邮件传输代理的交互
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main()
{
    map<string, set<string> > mtaMap;
    string s;
    while(cin>>s && s[0]!='*')
    {
        set<string> users;
        cin >> s;
        int n;
        cin >> n;
        while(n--)
        {
            string user;
            cin >> user;
            mtaMap[s].insert(user+'@'+s);
        }
    }
    string sender;
    while(cin>>sender && sender[0]!='*')
    {
        string sMTA = sender.substr(sender.find('@')+1);
        vector<string> rMTA;
        map<string, vector<string> > rMTAmap;
        set<string> recivers;
        while(cin>>s && s[0]!='*')
        {
            string mta = s.substr(s.find('@')+1);
            if(!rMTAmap.count(mta))
            {
                rMTA.push_back(mta);
            }
            if(!recivers.count(s))
            {
                rMTAmap[mta].push_back(s);
                recivers.insert(s);
            }
        }
        cin.get();
        string msg = "";
        while(getline(cin, s) && s[0]!='*')
        {
            msg += "     " + s + '\n';
        }
        msg += "     .";
        for(auto x: rMTA)
        {
            cout << "Connection between " << sMTA << " and " << x << "\n     HELO " << sMTA
                 << "\n     250\n     MAIL FROM:<" << sender << ">\n     250" << endl;
            bool flag = false;
            for(auto usr: rMTAmap[x])
            {
                const int f = mtaMap[x].count(usr);
                if(f)
                {
                    flag = true;
                }
                cout << "     RCPT TO:<" << usr << ">\n     " << (f ? 250 : 550) << endl;
            }
            if(flag)
            {
                cout << "     DATA\n     354\n" << msg << "\n     250" << endl;
            }
            cout <<"     QUIT\n     221" << endl;
        }
    }
    return 0;
}