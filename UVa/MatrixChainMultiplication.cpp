/**
 * UVa442
 * 矩阵链乘积
 */

#include <iostream>
#include <string>
#include <stack>

struct rc {
    int r, c;
    rc(int r=0, int c=0) {
        this->r = r;
        this->c = c;
    }
};

int main()
{
    using namespace std;
    int n;
    rc matrix[26];
    cin >> n;
    while(n--) {
        char c;
        cin >> c;
        cin >> matrix[c-'A'].r >> matrix[c-'A'].c;
    }
    string exp;
    while(cin >> exp) {
        int t=0; stack<rc> s;
        for(int i=0; i<exp.length(); ++i) {
            if(exp[i] == ')') {
                rc b = s.top();
                s.pop();
                rc a = s.top();
                s.pop();
                if(a.c != b.r) {
                    t = -1;
                    break;
                }
                t += a.r * a.c * b.c;
                s.push(rc(a.r, b.c));
            }
            else if(exp[i] != '(') {
                s.push(matrix[exp[i]-'A']);
            }
        }
        t < 0 ? cout << "error" << endl : cout << t << endl;
    }
    return 0;
}