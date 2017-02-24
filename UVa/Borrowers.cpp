/**
 * UVa230
 * 图书管理系统
 */

#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

struct book
{
    string title, author;
    book(const string t, const string a): title(t), author(a) {}
    bool operator< (const book& o) const
    {
        return author<o.author || (author==o.author && title<o.title);
    }
};

int main()
{
    set<book> s, rs;
    map<string, string> m;
    string ss;
    while(getline(cin, ss) && ss[0]=='"')
    {
        const int l = ss.find('"', 1) + 1;
        book b(ss.substr(0, l), ss.substr(l+4));
        s.insert(b);
        m[b.title] = b.author;
    }
    while(getline(cin, ss) && ss[0]!='E')
    {
        if(ss[0] == 'B')
        {
            const string t = ss.substr(7);
            s.erase(book(t, m[t]));
        }
        if(ss[0] == 'R')
        {
            const string t = ss.substr(7);
            rs.insert(book(t, m[t]));
            s.insert(book(t, m[t]));
        }
        if(ss[0] == 'S')
        {
            for(auto& b: rs)
            {
                set<book>::iterator iter = s.find(b);
                cout << "Put " << b.title << (iter==s.begin() ? " first" : string(" after ") + (--iter)->title) << endl;
            }
            cout << "END" << endl;
            rs.clear();
        }
    }
    return 0;
}