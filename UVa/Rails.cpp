/**
 * UVa514
 * 铁轨
 */

#include <iostream>
#include <stack>

int main()
{
    using namespace std;
    int N;
    while(cin >> N && N) {
        int coache;
        while(cin>>coache && coache) {
            int n = N, top=1;
            stack<int> marshal, part;
            part.push(0);
            do {
                marshal.push(coache);
                cin >> coache;
            } while(--n);
            while(!marshal.empty()) {
                while(marshal.top() != top && part.top()+1 == marshal.top()) {
                    if() break;
                    part.push(marshal.top());
                    marshal.pop();
                }
                //
            }
            cout << "No" << endl;
        }
        cout << endl;
    }
    return 0;
}