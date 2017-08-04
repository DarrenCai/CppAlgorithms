/**
 * UVa12166
 * 修改天平
 */

#include <iostream>
#include <string>
#include <map>
using namespace std;
string s; int idx;

void dfs(map<long long, int>& count, int depth){ char c = s[idx];
    if(c == '['){ ++idx; dfs(count, depth+1); ++idx; dfs(count, depth+1); ++idx; }
    else{long long a=0; while(c>='0' && c<='9'){a=10*a+c-'0'; c=s[++idx];} ++count[a<<depth];}
}

int main()
{
    short t; cin >> t;
    while(t--){ map<long long, int> count; cin >> s; idx=0; dfs(count, 0); int max=0, sum=0;
        for(map<long long, int>::iterator it=count.begin(); it!=count.end(); ++it){
            sum += it->second; if(max<it->second) max = it->second; }
        cout << sum-max << endl;
    }
    return 0;
}