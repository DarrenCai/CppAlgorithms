/**
 * UVa815
 * 洪水
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Result
{
    float l, p; 
};

Result calc(const std::vector<int>& s, int w)
{
    struct Result ans;
    int high=s.size(), low=1, mid=(high+low)>>1;
    while(low <= high)
    {
		int sum = 0;
        for(int i=0; i<mid; ++i)
        {
            sum += s[i];
        }
        ans.l = w/100.0/mid + sum/1.0/mid;
        if(s[mid-1] >= ans.l)
        {
            high = mid-1;
        }
        else
        {
            low = mid+1;
        }
        mid=(high+low)>>1;
    }
	int sum = 0;
	for(int i=0; i<mid; ++i)
	{
		sum += s[i];
	}
	ans.l = w/100.0/mid + sum/1.0/mid;
    ans.p = 100.0*mid/s.size();
    return ans;
}

int main()
{
    using namespace std;
    int m, n, count=0;
    while(cin>>m>>n && m && n)
    {
        const int size = m*n;
        vector<int> s;
        for(int i=0; i<size; ++i)
        {
            int t;
            cin >> t;
            s.push_back(t);
        }
        sort(s.begin(), s.end());
        int w;
        cin >> w;
		struct Result ans = calc(s, w);
        cout << "Region " << ++count << endl;
		cout << "Water level is " << setiosflags(ios::fixed) << setprecision(2) << ans.l << " meters." << endl;
        cout << ans.p << " percent of the region is under water." << endl << endl;
    }
    return 0;
}