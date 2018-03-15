/**
 * 有一只羊圈，开始有一只羊。每只羊在出生2个月后开始长羊毛，每月长0.8斤羊毛，最多长10斤。
 * 在出生5个月后，产羊毛能力下降，每个月只能长0.7斤羊毛。假设每只羊不死，每个月又放入一只
 * 新生小羊，问：10年后羊圈里共有多少羊毛？
 */

#include <iostream>

#define m 120

int main()
{
    using namespace std;
    const float array[] = {0, 0, 0.8, 1.6, 2.4, 3.1, 3.8, 4.5, 5.2, 5.9, 6.6, 7.3, 8, 8.7, 9.4, 10};
    float total = (m-16)*10;
    for(int i=0; i<16; ++i)
        total += array[i];
    cout << total << endl;
    return 0;
}