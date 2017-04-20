/**
 * UVa210
 * 并行程序模拟
 */

#include <iostream>
#include <string>
#include <queue>
#include <deque>

int main()
{
    using namespace std;
    int n, count=0;
    cin >> n;
    while(n--){
        if(count++) cout << endl;
        int m, t[5], q;
        cin >> m >> t[0] >> t[1] >> t[2] >> t[3] >> t[4] >> q;
        int s[10][25][3] = {0}, r[10] = {0}, v[26] = {0};
        deque<int> rq;
        queue<int> bq;
        for(int i=0; i<m; ++i){
            int j=0;
            string op;
            while(cin>>op && op!="end"){
                if(op == "lock") s[i][j][0] = 2;
                else if(op == "unlock") s[i][j][0] = 3;
                else if(op == "print"){
                    s[i][j][0] = 1;
                    cin >> op;
                    s[i][j][1] = op[0]-'a';
                }
                else{
                    s[i][j][0] = 0;
                    s[i][j][1] = op[0]-'a';
                    cin >> op;
                    cin >> s[i][j][2];
                }
                ++j;
            }
            s[i][j][0] = 4;
            rq.push_back(i);
        }
        bool inLock = false;
        while(!rq.empty()){
            int i = rq.front(), et = 0;
            rq.pop_front();
            bool inBlock = false;
            while(et < q){
                int op = s[i][r[i]][0];
                if(op == 0) v[s[i][r[i]][1]] = s[i][r[i]][2];
                else if(op == 1) cout << i+1 << ": " << v[s[i][r[i]][1]] << endl;
                else if(op == 2){
                    if(inLock){
                        inBlock = true;
                        bq.push(i);
                        break;
                    }
                    else inLock = true;
                }
                else if(op == 3){
                    inLock = false;
                    if(!bq.empty()){
                        rq.push_front(bq.front());
                        bq.pop();
                    }
                }
                else break;
                ++ r[i];
                et += t[op];
            }
            if(!inBlock && s[i][r[i]][0] != 4) rq.push_back(i);
        }
    }
    return 0;
}