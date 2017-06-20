/**
 * UVa12171
 * 雕塑
 * 这里用区间求并的方式求解
 */

#include <iostream>
#include <deque>
#include <map>
using namespace std;
#define p pair<short, short>

short search(const deque<short>& m, const short k, short s=0) {
    short l=s, h=m.size()-1, mid;
    while(mid=(l+h)/2, l<=h){
        if(m[mid]<=k) l=mid+1;
        else h=mid-1;
    }
    return h;
}

int main()
{
    short t; cin >> t;
    while(t--){
        map<p, deque<short> > mx, my, mz;
        short n; cin >> n;
        for(short i=0; i<n; ++i){
            short x0, y0, z0, x, y, z; cin >> x0 >> y0 >> z0 >> x >> y >> z; x += x0; y += y0; z += z0;
            for(int j=x0; j<=x; ++j) for(int k=y0; k<=y; ++k) { p pt(j, k);
                if(!mz.count(pt)) mz[pt].push_back(z0), mz[pt].push_back(z);
                else{
                    short a = search(mz[pt], z0), b = search(mz[pt], z), s=mz[pt].size()-1;
                    if(b<0) mz[pt].push_front(z), mz[pt].push_front(z0);
                    else {
                        mz[pt].erase(mz[pt].begin()+(a<0 ? 0 : a+1), mz[pt].begin()+b);
                        a+1>=mz[pt].size() ? mz[pt].push_back(z) : (void)mz[pt].insert(mz[pt].begin()+1+a, z);
                        if(a<0) mz[pt].push_front(z0);
                    }
                }
            }
            for(int j=x0; j<=x; ++j) for(int k=z0; k<=z; ++k) { p pt(j, k);
                if(!my.count(pt)) my[pt].push_back(y0), my[pt].push_back(y);
                else{
                    short a = search(my[pt], y0), b = search(my[pt], y), s=my[pt].size()-1;
                    if(b<0) my[pt].push_front(y), my[pt].push_front(y0);
                    else {
                        my[pt].erase(my[pt].begin()+(a<0 ? 0 : a+1), my[pt].begin()+b);
                        a+1>=my[pt].size() ? my[pt].push_back(y) : (void)my[pt].insert(my[pt].begin()+1+a, y);
                        if(a<0) my[pt].push_front(y0);
                    }
                }
            }
            for(int j=y0; j<=y; ++j) for(int k=z0; k<=z; ++k) { p pt(j, k);
                if(!mx.count(pt)) mx[pt].push_back(x0), mx[pt].push_back(x);
                else{
                    short a = search(mx[pt], x0), b = search(mx[pt], x), s=mx[pt].size()-1;
                    if(b<0) mx[pt].push_front(x), mx[pt].push_front(x0);
                    else {
                        mx[pt].erase(mx[pt].begin()+(a<0 ? 0 : a+1), mx[pt].begin()+b);
                        a+1>=mx[pt].size() ? mx[pt].push_back(x) : (void)mx[pt].insert(mx[pt].begin()+1+a, x);
                        if(a<0) mx[pt].push_front(x0);
                    }
                }
            }
            
        }
        short s=0, v=0;
        for(map<p, deque<short> >::iterator it=mx.begin(); it!=mx.end(); ++it){
            short size = it->second.size(); s += size;
            for(int i=0; i<size; i+=2) v+=it->second[i+1]-it->second[i];
        }
        for(map<p, deque<short> >::iterator it=my.begin(); it!=my.end(); ++it) s += it->second.size();
        for(map<p, deque<short> >::iterator it=mz.begin(); it!=mz.end(); ++it) s += it->second.size();
        cout << s << ' ' << v << endl;
    }
    return 0;
}