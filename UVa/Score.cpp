/**
 * UVa1585
 * 得分
 */

 #include <iostream>
 #include <string>

 int main()
 {
     using namespace std;
     int n;
     cin >> n;
     while(n--)
     {
         string s;
         cin >> s;
         const int len = s.length();
         int count=0, score=0;
         for(int i=0; i<len; ++i)
         {
             if(s[i] == 'O')
             {
                 ++ count;
                 score += count;
             }
             else
             {
                 count = 0;
             }
         }
         cout << score << endl;
     }
     return 0;
 }