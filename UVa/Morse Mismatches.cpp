/**
 * UVa508
 * 莫尔斯电码
 */

#include <iostream>
#include <string>
#include <map>

int main()
{
    using namespace std;
	map<char, string> code;
	map<string, string> ctx;
	char c;
	while(cin>>c && c!='*')
	{
		string morse;
		cin >> morse;
		code[c] = morse;
	}
	string word;
	while(cin>>word && word!="*")
	{
		const int len = word.length();
		string morse = "";
		for(int i=0; i<len; ++i)
		{
			morse += code[word[i]];
		}
		map<string, string>::iterator iter = ctx.find(morse);
		if(iter == ctx.end())
		{
			ctx[morse] = word;
		}
		else
		{
			int n = iter->second.length();
			if((iter->second[n-1]=='!' && n>len+1)
				|| (iter->second[n-1]!='!' && n>len))
			{
				iter->second = word + '!';
			}
			else if(iter->second[n-1] != '!')
			{
				iter->second += '!';
			}
		}
	}
	while(cin>>word && word!="*")
	{
		map<string, string>::iterator iter = ctx.find(word);
		if(iter != ctx.end())
		{
			cout << iter->second << endl;
		}
		else
		{
			const int len = word.length();
			int del=80, add=80;
			string ans, ans1;
			for(map<string, string>::iterator iter = ctx.begin(); iter != ctx.end(); ++iter)
			{
				const string morse = iter->first;
				const int d = morse.length() - len;
				if(d<0 && word.find(morse)==0)
				{
					if(-d<del)
					{
						del = -d;
						ans = iter->second;
					}
				}
				if(d>0 && morse.find(word)==0)
				{
					if(d<add)
					{
						add = d;
						ans1 = iter->second;
					}
				}
			}
			if(add < del)
			{
				ans = ans1;
			}
			int n = ans.length();
			if(ans[n-1] == '!')
			{
				ans[n-1] = '?';
			}
			else
			{
				ans += '?';
			}
			cout << ans << endl;
		}
	}
    return 0;
}