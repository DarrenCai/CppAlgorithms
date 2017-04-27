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
            stack<int> sequence;
            marshal.push(coache);
            while(--n) {
                cin >> coache;
                marshal.push(coache);
            }
            marshal.push(0);
            sequence.push(0);
            while(marshal.front() && front<N+2) {
                if(sequence.top() > marshal.front()) break;
                else if(sequence.top() == marshal.front()) {
                    sequence.pop();
                    marshal.pop();
                }
                else {
                    while(front < marshal.front()) sequence.push(front ++);
                    marshal.pop();
                    ++ front;
                }
            }
            cout << (marshal.front() ? "No" : "Yes") << endl;
        }
        cout << endl;
    }
    return 0;
}