/**
 * UVa673
 * 平衡的括号
 */

#include <iostream>
#include <stack>

int main()
{
    using namespace std;
    int n; cin >> n; cin.get();
    while(n--){ stack<char> s; char c; bool f=true;
        while(!cin.eof() && (c=cin.get()) != '\n'){ if(!f) continue;
            if(c==')'){ if(!s.empty() && s.top()=='(') s.pop(); else f=false; }
            else if(c==']'){ if(!s.empty() && s.top()=='[') s.pop(); else f=false; }
            else s.push(c);
        }
        cout << (f && s.empty() ? "Yes" : "No") << endl;
    }
    return 0;
}