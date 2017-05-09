/**
 * UVa122
 * 树的层次遍历
 */

#include <iostream>
#include <string>
#include <map>

int main()
{
    using namespace std;
    map<int,int> nodes; string node;
    bool complete = true;
    while(cin >> node) {
        const int len = node.length();
        if(len == 2) {
            map<int,int>::const_iterator it=nodes.begin();
            if(it->first != 1)    complete = false;
            while(++it != nodes.end() && complete)
                if(!nodes.count(it->first/2))   complete = false;
            if(complete) {
                it=nodes.begin(); cout << it->second;
                while(++it != nodes.end())      cout << ' ' << it->second;
                cout << endl;
            } else  cout << "not complete" << endl;
            complete = true;
            nodes.clear();
        } else if(complete) {
            int k=1, v=0;
            for(int i=1; i<len-1; ++i) {
                if(node[i]>='0' && node[i]<='9')    v = 10*v + node[i]-'0';
                else if(node[i]=='L' || node[i]=='R')    k = (k<<1) + int(node[i]=='R');
            }
            if(nodes.count(k))      complete = false;
            else    nodes[k] = v;
        }
    }
    return 0;
}