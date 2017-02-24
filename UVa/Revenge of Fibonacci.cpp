/**
 * UVa12333
 * Fibonacci的复仇
 */

#include <iostream>
#include <string>

int main()
{
	using namespace std;
	struct node
	{
		int idx;
		node *next[10];
		node(): idx(-1), next{nullptr}{}
		node(int idx): next{nullptr}
		{
			this->idx = idx;
		}
	};
	node* trie = new node;
	trie->next[1] = new node(0);
	bool carry = false;
	int v[2][48] = {{0}, {0}};
	v[0][47] = v[1][47] = 1;
    for(int i=2; i<100000; ++i)
    {
		for(int j=0; j<48; ++j)
		{
			int t = v[0][j];
			v[0][j] = v[1][j];
			v[1][j] = t;
		}
		int t=0;
		for(int j=47; j>=0; --j)
		{
			v[1][j] = v[0][j] + t + (carry ? (j ? v[1][j-1] : 0) : v[1][j]);
			t = v[1][j] / 10;
			v[1][j] %= 10;
		}
		carry = t;
		if(t)
		{
			for(int j=47; j>0; --j)
			{
				v[1][j] = v[1][j-1];
			}
			v[1][0] = 1;
		}
		int j=0, k=0;
		for(j=0; j<48 && !v[1][j]; ++j);
		node* ptr = trie;
		while(j<48 && k++<40)
		{
			if(!ptr->next[v[1][j]])
			{
				ptr->next[v[1][j]] = new node(i);
			}
			ptr = ptr->next[v[1][j++]];
		}
    }
    int t=0, k=0;
    cin >> t;
    cin.get();
    while(t--)
    {
        string prefix;
        cin >> prefix;
		node* ptr = trie;
		for(auto& ch: prefix)
		{
			if(!(ptr = ptr->next[ch-'0']))
			{
				break;
			}
		}
        cout << "Case #" << ++k << ": " << (ptr ? ptr->idx : -1) << endl;
    }
    return 0;
}