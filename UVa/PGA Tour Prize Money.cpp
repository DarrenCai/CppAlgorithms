/**
 * UVa207
 * PGA巡回赛的奖金
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct record
{
    string name;
    vector<int> r;
    int t, c;
    record():t(0),c(0) {}
    void add(int v)
    {
        r.push_back(v);
        t += v;
        if(r.size()<=2)
        {
            c = t;
        }
    }
    bool operator< (const record& b) const
    {
        const int len = r.size();
        const int lenb = b.r.size();
        if(len != lenb)
        {
            return len > lenb;
        }
        if(t != b.t)
        {
            return t < b.t;
        }
        return name < b.name;
    }
};

bool cmp(const record& a, const record& b)
{
    if(a.r.size() < 2)
    {
        return false;
    }
    if(b.r.size() < 2)
    {
        return true;
    }
    return a.c <= b.c;
}

void print(const record& r, int place=0, double money=-1, bool tie=false)
{
    stringstream ss;
    place ? (tie ? ss<<place<<'T' : ss<<place) : ss<<" ";
    cout << left << setw(21) << r.name << setw(10) << ss.str();
    int j, size = r.r.size();
    for(j=0; j<size; ++j)
    {
        cout << setw(5) << r.r[j];
    }
    for(; j<4; ++j)
    {
        cout << setw(5) << "";
    }
    size==4 ? cout << setw(money>=0 ? 10:1) << r.t : cout << setw(1) << "DQ";
    if(money >= 0)
    {
        cout << setw(1) << '$' << setw(9) << right << fixed << setprecision(2) << money;
    }
    cout << setw(1) << endl;
}

int main()
{
    int c, count = 0;
    cin >> c;
    while(c--)
    {
        double t, p[70];
        cin >> t;
        for(int i=0; i<70; ++i)
        {
            cin >> p[i];
            p[i] *= t/100;
        }
        int n, m, m1, m2;
        cin >> n;
        cin.get();
        vector<record> s, tie;
        for(int i=0; i<n; ++i)
        {
            record r;
            int score;
            char name[21] = {0};
            cin.get(name, 21);
            for(int j=19; name[j]==' '; --j)
            {
                name[j] = 0;
            }
            r.name = string(name);
            while(r.r.size()<4 && cin>>score)
            {
                r.add(score);
            }
            if(r.r.size() >= 2)
            {
                s.push_back(r);
            }
            cin.clear();
            r.r.size()==4 ? cin.getline(name, 1) : cin.getline(name, 5);
        }
        n = s.size();
        sort(s.begin(), s.end(), cmp);
        for(m1=0; m1<69 && m1<n-1 && s[m1].r.size()>=2; ++m1);
        for(; m1<n-1 && s[m1].r.size()>=2 && s[m1+1].r.size()>=2 && s[m1].c==s[m1+1].c; ++m1);
        n = m1+1;
        sort(s.begin(), s.begin()+n);
        for(m=0; m<m1 && s[m].r.size()==4; ++m);
        if(s[m].r.size() < 4)
        {
            -- m;
        }
        else
        {
            for(; m<m1 && s[m].r.size()==4 && s[m+1].r.size()==4 && s[m].t==s[m+1].t; ++m);
        }
        sort(s.begin()+m+1, s.begin()+n);
        if(count ++)
        {
            cout << endl;
        }
        cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won" << endl
             << "-----------------------------------------------------------------------" << endl;
        m1=m2=0;
        for(int i=0; i<=m; ++i)
        {
            tie.push_back(s[i]);
            if((i<m && s[i].t<s[i+1].t) || i==m)
            {
                int repeat = 0;
                const int size = tie.size();
                double money = m2<70 ? 0 : -1;
                for(int j=0; j<size; ++j)
                {
                    if(*tie[j].name.rbegin() != '*')
                    {
                        if(m2 < 70)
                        {
                            money += p[m2++];
                        }
                        ++ repeat;
                    }
                }
                if(repeat)
                {
                    money /= repeat;
                }
                for(int j=0; j<size; ++j)
                {
                    *tie[j].name.rbegin() == '*' ? print(tie[j], m1+1) : print(tie[j], m1+1, money, repeat>1 && money>=0);
                }
                m1 += size;
                tie.clear();
            }
        }
        for(int i=m+1; i<n; ++i)
        {
            tie.push_back(s[i]);
            if((i<n-1 && s[i].t!=s[i+1].t) || i==n-1)
            {
                const int size = tie.size();
                for(int j=0; j<size; ++j)
                {
                    tie[j].r.size()==4 ? print(tie[j], m1+1) : print(tie[j]);
                }
                m1 += size;
                tie.clear();
            }
        }
    }
    return 0;
}