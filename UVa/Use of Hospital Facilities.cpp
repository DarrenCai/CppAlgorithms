/**
 * UVa212
 * 医院设备利用
 * 注意：自己写的四舍五入时候可能有再次进位的情况，原来就没有考虑这一点
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
    }roomInfo[10], bedInfo[30];     // 如果要用自写的测试数据，则改成bedInfo[100]
    struct pInfo
    {
        string name;
        int surgT, recoT, roomID, roomB, bedID;
    }patients[100];
    int rooms, beds, time0, transT, prepO, prepR, n, endT, pOrder[100];
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
            roomInfo[roomID].avilT += patients[i].surgT + prepO;
        }
        sort(pOrder, pOrder + n, [&patients](int a, int b) {
            const int Ta = patients[a].roomB + patients[a].surgT;
            const int Tb = patients[b].roomB + patients[b].surgT;
            return Ta < Tb || (Ta==Tb && patients[a].roomID < patients[b].roomID);
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
            const pInfo p = patients[i-1];
            const int ohs = p.roomB / 60;
            const int oms = p.roomB % 60;
            const int ohe = (p.roomB + p.surgT) / 60;
            const int ome = (p.roomB + p.surgT) % 60;
            const int rhs = (p.roomB + p.surgT + transT) / 60;
            const int rms = (p.roomB + p.surgT + transT) % 60;
            const int rhe = (p.roomB + p.surgT + transT + p.recoT) / 60;
            const int rme = (p.roomB + p.surgT + transT + p.recoT) % 60;
            cout << (i < 10 ? " " : "") << i << "  " << p.name << "  " << (p.roomID < 10 ? " " : "")
                 << p.roomID << "   " << (ohs < 10 ? " " : "") << ohs << (oms < 10 ? ":0" : ":") << oms << "   "
                 << (ohe < 10 ? " " : "") << ohe << (ome < 10 ? ":0" : ":") << ome << "     " << (p.bedID < 10 ? " " : "")
                 << p.bedID << "   " << (rhs < 10 ? " " : "") << rhs << (rms < 10 ? ":0" : ":") << rms << "   "
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
            const int u = T * 10000.0 / (endT - time0) + 0.5;
            const int a = u / 100, b = u%100;
            cout << "Room " << (i < 10 ? " " : "") << i << (T < 10 ? "       " : (T < 100 ? "      " : (T < 1000 ? "     " : "    ")))
                 << T << (a < 10 ? "    " : "   ") << a << (b < 10 ? ".0" : ".") << b << endl;
        }
        for (int i = 1; i <= beds; ++i)
        {
            const int T = bedInfo[i - 1].usedT;
            const int u = T * 10000.0 / (endT - time0) + 0.5;
            const int a = u / 100, b = u%100;
            cout << "Bed  " << (i < 10 ? " " : "") << i << (T < 10 ? "       " : (T < 100 ? "      " : (T < 1000 ? "     " : "    ")))
                 << T << (a < 10 ? "    " : "   ") << a << (b < 10 ? ".0" : ".") << b << endl;
        }
        cout << endl;
    }
    return 0;
}