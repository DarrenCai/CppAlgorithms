/**
 * UVa1593
 * 代码对齐
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    using namespace std;
    vector<vector<string> > code;
    int len[180] = { 0 };
    string s;
    stringstream ss;
    while(getline(cin, s))
    {
        ss.str(s);
        ss.clear();
        vector<string> line;
        string word;
        int p = 0;
        while(ss >> word)
        {
            line.push_back(word);
            const int l = word.length();
            if(len[p] < l)
            {
                len[p] = l;
            }
            ++ p;
        }
        code.push_back(line);
    }
    const int m = code.size();
    for(int i=0; i<m; ++i)
    {
        const int n = code[i].size();
        for(int j=0; j<n-1; ++j)
        {
            cout << code[i][j];
            for(int k=code[i][j].length(); k<len[j]+1; ++k)
            {
                cout << ' ';
            }
        }
        cout << code[i][n-1] << endl;
    }
    return 0;
}