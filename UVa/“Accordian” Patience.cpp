/**
 * UVa127
 * 纸牌游戏
 */

#include <iostream>
#include <vector>
#include <stack>

int main()
{
    using namespace std;
    while(true) {
        vector<stack<char> > pile(52);
        for(char i=0; i<52; ++i) {
            char c1, c2; cin >> c1;
            if(c1=='#') return 0;
            if(c1>='2' && c1<='9') c1 -= '0';
            else if(c1=='A') c1 = 1;
            else if(c1=='T') c1 = 10;
            else if(c1=='J') c1 = 11;
            else if(c1=='Q') c1 = 12;
            else if(c1=='K') c1 = 13;
            c1<<=2; cin>>c2;
            if(c2=='C') c1 |= 1;
            else if(c2=='D') c1 |= 2;
            else if(c2=='H') c1 |= 3;
            pile[i].push(c1);
        }
        char size, i, start=0;
        while((size=pile.size()) > 1) {
            for(i=start; i<size; ++i) {
                if(i>2) {
                    char c1 = pile[i].top();
                    char c2 = pile[i-3].top();
                    if((c1&3)==(c2&3) || c1>>2==c2>>2) {
                        pile[i-3].push(c1); pile[i].pop();
                        if(pile[i].empty()) pile.erase(pile.begin()+i);
                        start = i-3; break;
                    }
                }
                if(i>0) {
                    char c1 = pile[i].top();
                    char c2 = pile[i-1].top();
                    if((c1&3)==(c2&3) || c1>>2==c2>>2) {
                        pile[i-1].push(c1); pile[i].pop();
                        if(pile[i].empty()) pile.erase(pile.begin()+i);
                        start = i-1; break;
                    }
                }
            }
            if (i==size) break;
        }
        size = pile.size();
        cout << pile.size() << ' ' << (size==1 ? "pile" : "piles") << " remaining:";
        for(i=0; i<size; ++i) cout << ' ' << pile[i].size();
        cout << endl;
    }
    return 0;
}