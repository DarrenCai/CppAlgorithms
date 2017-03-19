/**
 * UVa212
 * 医院设备利用
 */

#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    using namespace std;
    struct rInfo
    {
        int avilT, usedT;
    };
    struct pInfo
    {
        string name;
        int surgT, recoT, roomID, roomB, bedID;
    };
    rInfo roomInfo[10], bedInfo[30];
    pInfo patients[100];
    int pOrder[100];
    int rooms, beds, time0, transT, prepO, prepR, n, endT;
    while (cin >> rooms >> beds >> time0 >> transT >> prepO >> prepR >> n)
    {
        time0 *= 60, endT = time0;
        for (int i = 0; i < rooms; ++i)
            roomInfo[i].avilT = time0, roomInfo[i].usedT = 0;
        for (int i = 0; i < beds; ++i)
            bedInfo[i].avilT = time0, bedInfo[i].usedT = 0;
        for (int i = 0; i < n; ++i)
        {
            pOrder[i] = i;
            cin >> patients[i].name >> patients[i].surgT >> patients[i].recoT;
            patients[i].name.append(8 - patients[i].name.length(), ' ');
            int minT = roomInfo[0].avilT, roomID = 0;
            for (int j = 1; j < rooms; ++j)
                if (roomInfo[j].avilT < minT)
                {
                    roomID = j;
                    minT = roomInfo[j].avilT;
                }
            patients[i].roomB = minT;
            patients[i].roomID = roomID + 1;
            roomInfo[roomID].usedT += patients[i].surgT;
            roomInfo[roomID].avilT = minT + patients[i].surgT + prepO;
        }
        sort(pOrder, pOrder + n, [&patients](int a, int b) {
            const int Ta = patients[a].roomB + patients[a].surgT;
            const int Tb = patients[b].roomB + patients[b].surgT;
            if (Ta == Tb)
                return (patients[a].roomB != patients[b].roomB && patients[a].roomID < patients[b].roomID)
                    || (patients[a].roomB == patients[b].roomB && a < b);
            return Ta < Tb;
        });
        for (int i = 0; i < n; ++i)
        {
            const int T = patients[pOrder[i]].roomB + patients[pOrder[i]].surgT;
            for (int j = 0; j < beds; ++j)
                if (bedInfo[j].avilT <= T)
                {
                    patients[pOrder[i]].bedID = j + 1;
                    bedInfo[j].usedT += patients[pOrder[i]].recoT;
                    bedInfo[j].avilT = T + transT + patients[pOrder[i]].recoT;
                    if (bedInfo[j].avilT > endT)
                        endT = bedInfo[j].avilT;
                    bedInfo[j].avilT += prepR;
                    break;
                }
        }
        cout << " Patient          Operating Room          Recovery Room" << endl
             << " #  Name     Room#  Begin   End      Bed#  Begin    End" << endl
             << " ------------------------------------------------------" << endl;
        for (int i = 1; i <= n; ++i)
        {
            const int ohs = patients[i - 1].roomB / 60;
            const int oms = patients[i - 1].roomB % 60;
            const int ohe = (patients[i - 1].roomB + patients[i - 1].surgT) / 60;
            const int ome = (patients[i - 1].roomB + patients[i - 1].surgT) % 60;
            const int rhs = (patients[i - 1].roomB + patients[i - 1].surgT + transT) / 60;
            const int rms = (patients[i - 1].roomB + patients[i - 1].surgT + transT) % 60;
            const int rhe = (patients[i - 1].roomB + patients[i - 1].surgT + transT + patients[i - 1].recoT) / 60;
            const int rme = (patients[i - 1].roomB + patients[i - 1].surgT + transT + patients[i - 1].recoT) % 60;
            cout << (i < 10 ? " " : "") << i << "  " << patients[i - 1].name << "  " << (patients[i - 1].roomID < 10 ? " " : "")
                 << patients[i - 1].roomID << "   " << (ohs < 10 ? " " : "") << ohs << (oms < 10 ? ":0" : ":") << oms << "   "
                 << (ohe < 10 ? " " : "") << ohe << (ome < 10 ? ":0" : ":") << ome << "     " << (patients[i - 1].bedID < 10 ? " " : "")
                 << patients[i - 1].bedID << "   " << (rhs < 10 ? " " : "") << rhs << (rms < 10 ? ":0" : ":") << rms << "   "
                 << (rhe < 10 ? " " : "") << rhe << (rme < 10 ? ":0" : ":") << rme << endl;
        }
        cout << endl
             << "Facility Utilization" << endl
             << "Type  # Minutes  % Used" << endl
             << "-------------------------" << endl;
        if(n==0) endT += 10;
        for (int i = 1; i <= rooms; ++i)
        {
            const int T = roomInfo[i - 1].usedT;
            const int a = T * 100 / (endT - time0);
            const int b = (T * 100 % (endT - time0)) * 100.0 / (endT - time0) + 0.5;
            cout << "Room " << (i < 10 ? " " : "") << i << (T < 10 ? "       " : (T < 100 ? "      " : (T < 1000 ? "     " : "    ")))
                 << T << (a < 10 ? "    " : "   ") << a << (b < 10 ? ".0" : ".") << b << endl;
        }
        for (int i = 1; i <= beds; ++i)
        {
            const int T = bedInfo[i - 1].usedT;
            const int a = T * 100 / (endT - time0);
            const int b = (T * 100 % (endT - time0)) * 100.0 / (endT - time0) + 0.5;
            cout << "Bed  " << (i < 10 ? " " : "") << i << (T < 10 ? "       " : (T < 100 ? "      " : (T < 1000 ? "     " : "    ")))
                 << T << (a < 10 ? "    " : "   ") << a << (b < 10 ? ".0" : ".") << b << endl;
        }
        cout << endl;
    }
    return 0;
}