/**
 * UVa514
 * 铁轨
 */

#include <iostream>
#include <queue>
#include <stack>

int main()
{
    using namespace std;
    int N;
    while(cin >> N && N) {
        int coache;
        while(cin>>coache && coache) {
            int n = N, front=1;
            queue<int> marshal;
            marshal.push(coache);
            while(--n) {
                cin >> coache;
                marshal.push(coache);
            }
            marshal.push(0);
            while(marshal.front()) {
                int top0 = marshal.front()+1, top = top0;
                while(marshal.front() != front && (top-1 == marshal.front())) {
                    top = marshal.front();
                    marshal.pop();
                }
                if(marshal.front() != front || top-1 != marshal.front()) break;
                marshal.pop();
                front = top0;
            }
            cout << (marshal.front() ? "No" : "Yes") << endl;
        }
        cout << endl;
    }
    return 0;
}