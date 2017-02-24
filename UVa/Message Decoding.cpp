/**
 * UVa213
 * 信息解码
 */

#include <iostream>
#include <string>

using namespace std;

int len()
{
    char lens[3];
    cin >> lens[0] >> lens[1] >> lens[2];
    return (lens[0]-'0' << 2) + (lens[1]-'0' << 1) + lens[2]-'0';
}

int key(const int len)
{
    int k = 0;
    for(int i=0; i<len; ++i)
    {
        char c;
        cin >> c;
        k = 2*k + c-'0';
    }
    return k;
}

int main()
{
    string header;
    while(getline(cin, header))
    {
        string ans = "";
        while(int n = len())
        {
            const int s = (1<<n)-n-1;
            int k;
            while((k = key(n)) < (1<<n)-1)
            {
                ans += header[s+k];
            }
        }
        cout << ans << endl;
        cin.get();
    }
    return 0;
}