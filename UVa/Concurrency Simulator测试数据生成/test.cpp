#include <iostream>
#include <cstdlib>
#include <cstdio>
//#include<ctime>

int main()
{
    using namespace std;
    freopen("in.txt", "w", stdout);
    //srand(unsigned(time(0)));
    cout << 1000 << endl;
    int count = 0;
    while(count++ < 1000)
    {
        cout << endl;
        int m = rand()%10 + 1;
        int t0 = rand()%100 + 1;
        int q = t0;
        int t1 = rand()%100 + 1;
        if(t1 > q) q = t1;
        int t2 = rand()%100 + 1;
        if(t2 > q) q = t2;
        int t3 = rand()%100 + 1;
        if(t3 > q) q = t3;
        int t4 = rand()%100 + 1;
        if(t4 > q) q = t4;
        q += rand() % 3000;
        cout << m << ' ' << t0 << ' ' << t1 << ' ' << t2 << ' ' << t3 << ' ' << t4 << ' ' << q << endl;
        for(int i=0; i<m; ++i){
            int t = rand()%25+1, unlock = 0;
            for(int j=0; j<t-1; ++j){
                int op = rand()%3, a;
                char v;
                if(unlock){
                    if(j == unlock) { op = 3; unlock = 0; }
                    while(op == 2) op = rand()%3;
                }
                while(op == 2 && j==t-2) op = rand()%3;
                if(op == 2) unlock = rand()%(t-2-j)+1+j;
                switch(op){
                    case 0:
                        v = 'a' + rand()%26;
                        a = rand()%100;
                        cout << v << " = " << a << endl;
                        break;
                    case 1:
                        v = 'a' + rand()%26;
                        cout << "print " << v << endl;
                        break;
                    case 2:
                        cout << "lock" << endl;
                        break;
                    case 3:
                        cout << "unlock" << endl;
                }
            }
            cout << "end" << endl;
        }
    }
    return 0;
} 