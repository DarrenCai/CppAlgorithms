/**
 * UVa506
 * 系统依赖
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

void install(string& s, map<string, vector<string> >& dep, set<string>& ins){
    const int l = dep[s].size();
    for(int i=0; i<l; ++i) if(!ins.count(dep[s][i])) install(dep[s][i], dep, ins);
    cout << "   Installing " << s << endl;
}

void remove(string& s, map<string, set<string> >& r, set<string>& ins){
    if(r.count(s) && !r[s].empty()) for(set<string>::iterator it=r[s].begin(); it!=r[s].end(); ++it)
            if(ins.count(*it)) return void(cout << "   " << s << " is still needed." << endl);
    cout << "   Removing " << s << endl;
}

int main()
{
    stringstream ss; string cmd;
    while(getline(cin, cmd) && cmd!="END"){ cout << cmd << endl; ss.str(cmd); ss.clear();
        map<string, vector<string> > dep; map<string, set<string> > r; set<string> ins; ss >> cmd;
        if(cmd == "DEPEND"){ string s; ss >> s;
            while(cin >> cmd) dep[s].push_back(cmd); r[cmd].insert(s);
        }else if(cmd == "INSTALL"){ string s; ss >> s;
            if(!ins.count(s)) install(s, dep, ins);
            else cout << "   " << s << " is already installed." << endl;
        }else if(cmd == "REMOVE"){ string s; ss >> s;
            if(ins.count(s)) remove(s, r, ins);
            else cout << "   " << s << " is not installed." << endl;
        }
    }
    return 0;
}