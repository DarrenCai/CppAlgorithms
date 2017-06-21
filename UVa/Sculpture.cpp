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

void printDeque(const deque<short>& m, const p& pt){
    cout << pt.first << " " << pt.second << ":";
    for(deque<short>::const_iterator it=m.cbegin(); it!=m.cend(); ++it)
        cout << " " << *it;
    cout << endl;
}

int main()
{
    short t; cin >> t;
    while(t--){
        map<p, deque<short> > mx, my, mz;
        short n, s=0, v=0; cin >> n;
        for(short i=0; i<n; ++i){
            short x0, y0, z0, x, y, z; cin >> x0 >> y0 >> z0 >> x >> y >> z; x += x0; y += y0; z += z0;
            for(int j=x0; j<x; ++j) for(int k=y0; k<y; ++k) { p pt(j, k);
                if(!mz.count(pt)) mz[pt].push_back(z0), mz[pt].push_back(z)/*, printDeque(mz[pt], pt)*/;
                else{
                    // printDeque(mz[pt], pt);
                    short a = search(mz[pt], z0), b = search(mz[pt], z, (a<0 ? 0 : a));
                    if(b<0) mz[pt].push_front(z), mz[pt].push_front(z0);
                    else if(a+1==mz[pt].size() && mz[pt][a]==z0) mz[pt][a] = z;
                    else if(a+1==mz[pt].size() && mz[pt][a]<z0) mz[pt].push_back(z0), mz[pt].push_back(z);
                    else {
                        if(b&1) mz[pt].insert(mz[pt].begin()+1+b, z)/*, printDeque(mz[pt], pt)*/;
                        mz[pt].erase(mz[pt].begin()+(a<0 ? 0 : (a&1 && mz[pt][a]==z0 ? a : a+1)), mz[pt].begin()+b+1); //printDeque(mz[pt], pt);
                        if(a<0) mz[pt].push_front(z0); else if(a&1 && mz[pt][a]<z0) mz[pt].insert(mz[pt].begin()+1+a, z0);
                    }
                    // printDeque(mz[pt], pt);
                }
            }
            for(int j=x0; j<x; ++j) for(int k=z0; k<z; ++k) { p pt(j, k);
                if(!my.count(pt)) my[pt].push_back(y0), my[pt].push_back(y)/*, printDeque(my[pt], pt)*/;
                else{
                    // printDeque(my[pt], pt);
                    short a = search(my[pt], y0), b = search(my[pt], y, (a<0 ? 0 : a));
                    if(b<0) my[pt].push_front(y), my[pt].push_front(y0);
                    else if(a+1==my[pt].size() && my[pt][a]==y0) my[pt][a] = y;
                    else if(a+1==my[pt].size() && my[pt][a]<y0) my[pt].push_back(y0), my[pt].push_back(y);
                    else {
                        if(b&1) my[pt].insert(my[pt].begin()+1+b, y)/*, printDeque(my[pt], pt)*/;
                        my[pt].erase(my[pt].begin()+(a<0 ? 0 : (a&1 && my[pt][a]==y0 ? a : a+1)), my[pt].begin()+b+1); //printDeque(my[pt], pt);
                        if(a<0) my[pt].push_front(y0); else if(a&1 && my[pt][a]<y0) my[pt].insert(my[pt].begin()+1+a, y0);
                    }
                    // printDeque(my[pt], pt);
                }
            }
            for(int j=y0; j<y; ++j) for(int k=z0; k<z; ++k) { p pt(j, k);
                if(!mx.count(pt)) mx[pt].push_back(x0), mx[pt].push_back(x)/*, printDeque(mx[pt], pt)*/;
                else{
                    // printDeque(mx[pt], pt);
                    short a = search(mx[pt], x0), b = search(mx[pt], x, (a<0 ? 0 : a));
                    if(b<0) mx[pt].push_front(x), mx[pt].push_front(x0);
                    else if(a+1==mx[pt].size() && mx[pt][a]==x0) mx[pt][a] = x;
                    else if(a+1==mx[pt].size() && mx[pt][a]<x0) mx[pt].push_back(x0), mx[pt].push_back(x);
                    else {
                        if(b&1) mx[pt].insert(mx[pt].begin()+1+b, x)/*, printDeque(mx[pt], pt)*/;
                        mx[pt].erase(mx[pt].begin()+(a<0 ? 0 : (a&1 && mx[pt][a]==x0 ? a : a+1)), mx[pt].begin()+b+1); //printDeque(mx[pt], pt);
                        if(a<0) mx[pt].push_front(x0); else if(a&1 && mx[pt][a]<x0) mx[pt].insert(mx[pt].begin()+1+a, x0);
                    }
                    // printDeque(mx[pt], pt);
                }
            }
            
        }
        for(map<p, deque<short> >::iterator it=mx.begin(); it!=mx.end(); ++it){
            printDeque(it->second, it->first);
            short size = it->second.size(); s += size;
            for(int i=0; i<size; i+=2) v += it->second[i+1]-it->second[i];
        }
        cout << endl;
        for(map<p, deque<short> >::iterator it=my.begin(); it!=my.end(); ++it) s += it->second.size(), printDeque(it->second, it->first);
        cout << endl;
        for(map<p, deque<short> >::iterator it=mz.begin(); it!=mz.end(); ++it) s += it->second.size(), printDeque(it->second, it->first);
        cout << s << ' ' << v << endl;
    }
    return 0;
}