#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
//#include<ctime>

int main()
{
    using namespace std;
    //srand(unsigned(time(0)));
    int count = 0, avilT[10], bedT[100][2];
    while (count++ < 10)
    {
        freopen("temp.txt", "w", stdout);
        const int rooms = rand() % 10 + 1;
        int beds = rand() % 30 + 1;
        const int time0 = rand() % 24;
        const int transT = rand() % 31;
        const int prepO = rand() % 31;
        const int prepR = rand() % 31;
        const int n = rand() % 100;
        for (int i = 0; i < rooms; ++i)
            avilT[i] = time0 * 60;
        int minT, maxT = 0;
        for (int i = 0; i < n; ++i)
        {
            string name;
            int m = rand() % 8 + 1;
            while (m--)
            {
                name += 'a' + rand() % 26;
            }
            name[0] -= 32;
            const int surgT = rand() % 241;
            const int recoT = rand() % 361;
            cout << name << endl << surgT << ' ' << recoT << endl;
            int minT = avilT[0], roomID = 0;
            for (int j = 1; j < rooms; ++j)
                if (avilT[j] < minT)
                {
                    roomID = j;
                    minT = avilT[j];
                }
            avilT[roomID] = minT + surgT + prepO;
            bedT[i][0] = minT + surgT + transT;
            bedT[i][1] = bedT[i][0] + recoT + prepR;
            if (i == 0)
                minT = bedT[0][0];
            else if (bedT[i][0] < minT)
                minT = bedT[i][0];
            if (bedT[i][1] > maxT)
                maxT = bedT[i][1];
        }
        int max = 0;
        for (int t = minT; t <= maxT; ++t)
        {
            int count = 0;
            for (int i = 0; i < n; ++i)
                if (t > bedT[i][0] && t <= bedT[i][1])
                    ++count;
            if (count > max)
                max = count;
        }
        if (beds < max)
        {
            max += rand() % 99;
            if (max > 99)
                max = 99;
            beds = max;
        }
        fclose(stdout);
        freopen("temp.txt", "r", stdin);
        freopen("in.txt", "a", stdout);
        cout << rooms << ' ' << beds << ' ' << time0 << ' ' << transT << ' ' << prepO << ' ' << prepR << ' ' << n << endl;
        for (int i = 0; i < n; ++i)
        {
            string name;
            int surgT, recoT;
            cin >> name >> surgT >> recoT;
            cout << name << endl << surgT << ' ' << recoT << endl;
        }
    }
    remove("temp.txt");
    return 0;
}