/**
 * UVa 272
 * TeX中的引号
 */

#include <iostream>

int main()
{
    using namespace std;
    char c;
    bool left = true;
    while(cin.get(c))
    {
        if(c == '"')
        {
            cout << (left ? "``" : "''");
            left = !left;
        }
        else
        {
            cout << c;
        }
    }
    return 0;
}