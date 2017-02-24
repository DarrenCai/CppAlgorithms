/**
 * UVa455
 * 周期串
 */

 #include <iostream>
 #include <string>

 int main()
 {
     using namespace std;
     int n;
     cin >> n;
     for(int k=0; k<n; ++k)
     {
        string s;
        cin >> s;
        const int len = s.length();
        for(int i=1; i<=len; ++i)
        {
            if(len%i == 0)
            {
                const string sub = s.substr(0, i);
                bool flag = true;
                for(int j=0; flag && j<=len-i; j+=i)
                {
                    if(s.find(sub, j) != j)
                    {
                        flag = false;
                    }
                }
                if(flag)
                {
                    if(k)
                    {
                        cout << endl;
                    }
                    cout << i << endl;
                    break;
                }
            }
        }
     }
     return 0;
 }