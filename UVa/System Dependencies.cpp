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
// #include <cstdio>
using namespace std;

int find(vector<string>& ins, string s){
    const int l = ins.size(); for(int i=0; i<l; ++i) if(ins[i]==s) return i;
    return -1;
}

void install(string s, map<string, vector<string> >& dep, vector<string>& ins){
    if(dep.count(s) && !dep[s].empty()) for(int i=0,l=dep[s].size(); i<l; ++i)
            if(find(ins, dep[s][i]) == -1) install(dep[s][i], dep, ins);
    ins.push_back(s); cout << "   Installing " << s << endl;
}

void remove(int i, string s, map<string, vector<string> >& dep, map<string, set<string> >& r, vector<string>& ins, set<string>& ex){
    if(r.count(s) && !r[s].empty()) for(set<string>::iterator it=r[s].begin(); it!=r[s].end(); ++it)
            if(find(ins, *it) > -1) return;
    ins.erase(ins.begin()+i); cout << "   Removing " << s << endl;
    if(dep.count(s) && !dep[s].empty()) for(int j=0,l=dep[s].size(); j<l; ++j)
            if(!ex.count(dep[s][j]) && (i = find(ins, dep[s][j])) > -1) remove(i, dep[s][j], dep, r, ins, ex);
}

void remove(string s, int i, map<string, vector<string> >& dep, map<string, set<string> >& r, vector<string>& ins, set<string>& ex){
    if(r.count(s) && !r[s].empty()) for(set<string>::iterator it=r[s].begin(); it!=r[s].end(); ++it)
            if(find(ins, *it) > -1) return void(cout << "   " << s << " is still needed." << endl);
    ins.erase(ins.begin()+i); cout << "   Removing " << s << endl;
    if(dep.count(s) && !dep[s].empty()) for(int j=0,l=dep[s].size(); j<l; ++j)
            if(!ex.count(dep[s][j]) && (i = find(ins, dep[s][j])) > -1) remove(i, dep[s][j], dep, r, ins, ex);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    map<string, vector<string> > dep; map<string, set<string> > r; vector<string> ins; set<string> ex; stringstream ss; string cmd;
    while(getline(cin, cmd) && cmd!="END"){ cout << cmd << endl; ss.str(cmd); ss.clear(); ss >> cmd;
        if(cmd == "DEPEND"){ string s; ss >> s;
            while(ss >> cmd) dep[s].push_back(cmd), r[cmd].insert(s);
        }else if(cmd == "INSTALL"){ string s; ss >> s;
            if(find(ins,s) == -1) install(s, dep, ins), ex.insert(s);
            else cout << "   " << s << " is already installed." << endl;
        }else if(cmd == "REMOVE"){ string s; ss >> s; int i;
            if((i = find(ins,s)) > -1) remove(s, i, dep, r, ins, ex), ex.erase(s);
            else cout << "   " << s << " is not installed." << endl;
        }else{ const int l = ins.size();
            for(int i=0; i<l; ++i) cout << "   " << ins[i] << endl;
        }
    }
    cout << "END" << endl;
    return 0;
}