/**
 * UVa220
 * 黑白棋
 */

#include <iostream>

bool black;
char s[8][9], total;

void printMove(const char row, const char col)
{
    using namespace std;
    if(total++)
    {
        cout << ' ';
    }
    cout << '(' << row << ',' << col << ')';
}

bool possible(const char i, const char j)
{
    const char a = black ? 'B':'W';
    const char b = black ? 'W':'B';
    if(s[i][j] == '-')
    {
        unsigned char t=0;
        for(char k=j-1; k>=0 && s[i][k]==b; --k, ++t);
        if(t && j-t-1>=0 && s[i][j-t-1]==a)
        {
            return true;
        }
        t=0;
        for(char k=j+1; k<7 && s[i][k]==b; ++k, ++t);
        if(t && j+t+1<8 && s[i][j+t+1]==a)
        {
            return true;
        }
        t=0;
        for(char k=i-1; k>=0 && s[k][j]==b; --k, ++t);
        if(t && i-t-1>=0 && s[i-t-1][j]==a)
        {
            return true;
        }
        t=0;
        for(char k=i+1; k<7 && s[k][j]==b; ++k, ++t);
        if(t && i+t+1<8 && s[i+t+1][j]==a)
        {
            return true;
        }
        t=0;
        for(char k=i-1; k>=0 && j-i+k>=0 && s[k][j-i+k]==b; --k, ++t);
        if(t && i-t-1>=0 && j-t-1>=0 && s[i-t-1][j-t-1]==a)
        {
            return true;
        }
        t=0;
        for(char k=i-1; k>=0 && j+i-k<7 && s[k][j+i-k]==b; --k, ++t);
        if(t && i-t-1>=0 && j+t+1<8 && s[i-t-1][j+t+1]==a)
        {
            return true;
        }
        t=0;
        for(char k=i+1; k<7 && j+i-k>=0 && s[k][j+i-k]==b; ++k, ++t);
        if(t && i+t+1<8 && j-t-1>=0 && s[i+t+1][j-t-1]==a)
        {
            return true;
        }
        t=0;
        for(char k=i+1; k<7 && j-i+k<7 && s[k][j-i+k]==b; ++k, ++t);
        if(t && i+t+1<8 && j+t+1<8 && s[i+t+1][j+t+1]==a)
        {
            return true;
        }
    }
    return false;
}

void handle(const char i, const char j, char& W, char& B)
{
    const char a = black ? 'B':'W';
    const char b = black ? 'W':'B';
    s[i][j] = a;
    unsigned char t[8] = { 0 };
    for(char k=j-1; k>=0 && s[i][k]==b; --k, ++t[0]);
    if(!(t[0] && j-t[0]-1>=0 && s[i][j-t[0]-1]==a))
    {
        t[0] = 0;
    }
    for(char k=j+1; k<7 && s[i][k]==b; ++k, ++t[1]);
    if(!(t[1] && j+t[1]+1<8 && s[i][j+t[1]+1]==a))
    {
        t[1] = 0;
    }
    for(char k=i-1; k>=0 && s[k][j]==b; --k, ++t[2]);
    if(!(t[2] && i-t[2]-1>=0 && s[i-t[2]-1][j]==a))
    {
        t[2] = 0;
    }
    for(char k=i+1; k<7 && s[k][j]==b; ++k, ++t[3]);
    if(!(t[3] && i+t[3]+1<8 && s[i+t[3]+1][j]==a))
    {
        t[3] = 0;
    }
    for(char k=i-1; k>=0 && j-i+k>=0 && s[k][j-i+k]==b; --k, ++t[4]);
    if(!(t[4] && i-t[4]-1>=0 && j-t[4]-1>=0 && s[i-t[4]-1][j-t[4]-1]==a))
    {
        t[4] = 0;
    }
    for(char k=i-1; k>=0 && j+i-k<7 && s[k][j+i-k]==b; --k, ++t[5]);
    if(!(t[5] && i-t[5]-1>=0 && j+t[5]+1<8 && s[i-t[5]-1][j+t[5]+1]==a))
    {
        t[5] = 0;
    }
    for(char k=i+1; k<7 && j+i-k>=0 && s[k][j+i-k]==b; ++k, ++t[6]);
    if(!(t[6] && i+t[6]+1<8 && j-t[6]-1>=0 && s[i+t[6]+1][j-t[6]-1]==a))
    {
        t[6] = 0;
    }
    for(char k=i+1; k<7 && j-i+k<7 && s[k][j-i+k]==b; ++k, ++t[7]);
    if(!(t[7] && i+t[7]+1<8 && j+t[7]+1<8 && s[i+t[7]+1][j+t[7]+1]==a))
    {
        t[7] = 0;
    }
    for(char k=1; k<=t[0]; ++k)
    {
        s[i][j-k] = a;
    }
    for(char k=1; k<=t[1]; ++k)
    {
        s[i][j+k] = a;
    }
    for(char k=1; k<=t[2]; ++k)
    {
        s[i-k][j] = a;
    }
    for(char k=1; k<=t[3]; ++k)
    {
        s[i+k][j] = a;
    }
    for(char k=1; k<=t[4]; ++k)
    {
        s[i-k][j-k] = a;
    }
    for(char k=1; k<=t[5]; ++k)
    {
        s[i-k][j+k] = a;
    }
    for(char k=1; k<=t[6]; ++k)
    {
        s[i+k][j-k] = a;
    }
    for(char k=1; k<=t[7]; ++k)
    {
        s[i+k][j+k] = a;
    }
    for(char k=0; k<8; ++k)
    {
        for(char l=0; l<8; ++l)
        {
            if(s[k][l] == 'W')
            {
                ++ W;
            }
            if(s[k][l] == 'B')
            {
                ++ B;
            }
        }
    }
}

int main()
{
    using namespace std;
    int n, count=0;
    cin >> n;
    while(n--)
    {
        cin.get();
        if(count++)
        {
            cout << endl;
        }
        for(char i=0; i<8; ++i)
        {
            cin.getline(s[i], 9);
        }
        black = true;
        if(cin.get() == 'W')
        {
            black = false;
        }
        string cmd;
        while(cin >> cmd && cmd != "Q")
        {
            if(cmd == "L")
            {
                total = 0;
                for(char i=0; i<8; ++i)
                {
                    for(char j=0; j<8; ++j)
                    {
                        if(possible(i, j))
                        {
                            printMove(i+'1', j+'1');
                        }
                    }
                }
                if(!total)
                {
                    cout << "No legal move.";
                }
                cout << endl;
            }
            else
            {
                const char r = cmd[1]-'1';
                const char c = cmd[2]-'1';
                if(!possible(r, c))
                {
                    black = !black;
                }
                char w=0, b=0;
                handle(r, c, w, b);
                cout << "Black - ";
                if(b>9)
                {
                    cout << (int)b;
                }
                else
                {
                    cout << ' ' << char(b+'0');
                }
                cout << " White - ";
                if(w>9)
                {
                    cout << (int)w;
                }
                else
                {
                    cout << ' ' << char(w+'0');
                }
                cout << endl;
                black = !black;
            }
        }
        for(char i=0; i<8; ++i)
        {
            cout << s[i] << endl;
        }
    }
    return 0;
}