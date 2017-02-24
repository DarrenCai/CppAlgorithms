/**
 * UVa1589
 * 象棋
 * 注意黑方将碰到红方帅，直接吃掉的情况（此时黑方赢了）
 */

#include <iostream>

struct piece
{
    char t;
    unsigned char r:4;
    unsigned char c:4;
};

bool check(const short r, const short c, const piece* s, const short n)
{
    for(short i=0; i<n; ++i)
    {
        if(s[i].r==r && s[i].c==c)
        {
            continue;
        }
        if(s[i].t=='G' && s[i].c==c)
        {
            bool flag = true;
            for(short j=0; flag && j<n; ++j)
            {
                if(s[j].c==c && s[j].r<s[i].r && s[j].r>r)
                {
                    flag = false;
                }
            }
            if(flag)
            {
                return true;
            }
        }
        if(s[i].t=='R' && (s[i].c==c || s[i].r==r))
        {
            bool flag = true;
            for(short j=0; flag && j<n; ++j)
            {
                if(s[i].c==c && s[j].c==c && (r-s[j].r)*(s[j].r-s[i].r)>0)
                {
                    flag = false;
                }
                if(s[i].r==r && s[j].r==r && (c-s[j].c)*(s[j].c-s[i].c)>0)
                {
                    flag = false;
                }
            }
            if(flag)
            {
                return true;
            }
        }
        if(s[i].t=='H' && (s[i].c-c)*(s[i].c-c)*(s[i].r-r)*(s[i].r-r)==4)
        {
            bool flag = true;
            for(short j=0; flag && j<n; ++j)
            {
                if((s[j].c==s[i].c && 2*s[j].r==s[i].r+r)
                    || (s[j].r==s[i].r && 2*s[j].c==s[i].c+c))
                {
                    flag = false;
                }
            }
            if(flag)
            {
                return true;
            }
        }
        if(s[i].t=='C' && (s[i].c==c || s[i].r==r))
        {
            short count = 0;
            for(short j=0; j<n; ++j)
            {
                if(s[i].c==c && s[j].c==c && (r-s[j].r)*(s[j].r-s[i].r)>0)
                {
                    ++ count;
                }
                if(s[i].r==r && s[j].r==r && (c-s[j].c)*(s[j].c-s[i].c)>0)
                {
                    ++ count;
                }
            }
            if(count == 1)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    using namespace std;
    short n, r, c;
    while(cin >> n >> r >> c && n+r+c)
    {
        const short N = n;
        piece s[N];
        while(n--)
        {
            short a, b;
            cin >> s[n].t >> a >> b;
            s[n].r = a;
            s[n].c = b;
        }
        bool fail = true;
        if((r>1 && !check(r-1, c, s, N))
            || (r<3 && !check(r+1, c, s, N))
            || (c>4 && !check(r, c-1, s, N))
            || (c<6 && !check(r, c+1, s, N)))
        {
            fail = false;
        }
        for(short i=0; fail && i<N; ++i)
        {
            if(s[i].t=='G' && s[i].c==c)
            {
                bool flag = true;
                for(short j=0; flag && j<N; ++j)
                {
                    if(s[j].c==c && s[j].r<s[i].r)
                    {
                        flag = false;
                    }
                }
                fail = !flag;
            }
        }
        cout << (fail ? "YES" : "NO") << endl;
    }
    return 0;
}