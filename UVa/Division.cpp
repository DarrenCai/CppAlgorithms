/**
 * UVa725
 * 除法
 */

#include <iostream>

int main()
{
    using namespace std;
    int k=0, max, n;
    while(cin>>n && n) {
        bool noSolution = true;
        if (k++) cout << endl;
        max = 98765 / n;
        for(int i=1234; i<=max; ++i) {
            short c[10] = {0};
            ++ c[i%10]; ++ c[i/10%10]; ++ c[i/100%10]; ++ c[i/1000%10]; ++ c[i/10000];
            if (c[0]>1 || c[1]>1 || c[2]>1 || c[3]>1 || c[4]>1 || c[5]>1 || c[6]>1 || c[7]>1 || c[8]>1 || c[9]>1)
                continue;
            int d = i*n;
            ++ c[d%10]; ++ c[d/10%10]; ++ c[d/100%10]; ++ c[d/1000%10]; ++ c[d/10000];
            if (c[0]==1 && c[1]==1 && c[2]==1 && c[3]==1 && c[4]==1 && c[5]==1 && c[6]==1 && c[7]==1 && c[8]==1 && c[9]==1) {
                noSolution = false;
                cout << d << " / ";
                if (i<10000) cout << '0';
                cout << i << " = " << n << endl;
            }
        }
        if (noSolution) {
            cout << "There are no solutions for " << n << '.' << endl;
        }
    }
    return 0;
}