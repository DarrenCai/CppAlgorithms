/**
 * UVa1572
 * 自组合
 */

#include <iostream>

bool topology(const char u, const char (&g)[52][52], char (&visit)[52]){
    visit[u] = -1;
    for(char v=0; v<52; ++v) if(g[u][v] && (visit[v] == -1 || (!visit[v] && topology(v, g, visit)))) return true;
    visit[u] = 1; return false;
}

bool unbounded(const char (&g)[52][52], char (&visit)[52]){
    for(char i=0; i<52; ++i) if(!visit[i] && topology(i, g, visit)) return true;
    return false;
}

int main()
{
    using namespace std;
    unsigned short n;
    while(cin >> n){
        char g[52][52]={0}, visit[52]={0};
        for(unsigned short i=0; i<n; ++i){ char e[4];
            for(char j=0; j<4; ++j){ char c0, c1; cin >> c0 >> c1; e[j] = c0=='0' ? -1 : 2*(c0-'A')+(c1=='+' ? 0:1); }
            for(char j=0; j<4; ++j) for(char k=0; k<4; ++k) if(j!=k && e[j]>=0 && e[k]>=0) g[e[j]][e[k]^1] = 1;
        }
        cout << (unbounded(g, visit) ? "unbounded" : "bounded") << endl;
    }
    return 0;
}