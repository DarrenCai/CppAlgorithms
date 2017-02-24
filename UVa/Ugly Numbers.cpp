/**
 * UVa136
 * 丑数
 * 注意g++编译时int/long可能是16位的
 */

#include <iostream>
#include <set>

int main()
{
    const int coeff[3] = {2, 3, 5};
    using namespace std;
    int count = 0;
    set<unsigned int> s;
    s.insert(1);
    while(++count)
    {
        unsigned int x = *(s.begin());
        s.erase(x);
        if(count == 1500)
        {
            cout << "The 1500'th ugly number is " << x << ".\n";
            return 0;
        }
        for(int i=0; i<3; ++i)
        {
            unsigned int x2 = x*coeff[i];
            if(!s.count(x2))
            {
                s.insert(x2);
            }
        }
    }
    return 0;
}