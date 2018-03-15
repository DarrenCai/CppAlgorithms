/**
 * UVa246
 * 10-20-30游戏
 */

#include <iostream>
#include <vector>
#include <unordered_set>
// #include <cstdio>
using namespace std;

class pile {
protected:
    unsigned char cards[26], head, len;
public:
    pile(): head(0), len(0){}
    unsigned char front(unsigned char offset = 0) const {
        if (len > offset) {
            unsigned char pos = (head+offset)%52;
            return pos&1 ? cards[pos>>1] >> 4 : cards[pos>>1] & 0xf;
        }
        return 0;
    }
    unsigned char back(unsigned char offset = 0) const {
        if (len > offset) {
            unsigned char pos = (head+len-1-offset)%52;
            return pos&1 ? cards[pos>>1] >> 4 : cards[pos>>1] & 0xf;
        }
        return 0;
    }
    void push_front(unsigned char v) {
        v = v & 0xf;
        if (len < 52) {
            head = (head+51) % 52;    // head = (head-1+52) % 52;
            unsigned char& c = cards[head>>1];
            c = head&1 ? (c&0xf) | v<<4 : (c&0xf0) | v;
            ++ len;
        }
    }
    void push_back(unsigned char v) {
        v = v & 0xf;
        if (len < 52) {
            ++ len;
            unsigned char pos = (head+len-1)%52;
            unsigned char& c = cards[pos>>1];
            c = pos&1 ? (c&0xf) | v<<4 : (c&0xf0) | v;
        }
    }
    unsigned char pop_front() {
        if (len > 0) {
            unsigned char v = cards[head>>1];
            head = (head+1)%52;
            -- len;
            return head&1 ? v&0xf : v>>4;
        }
        return 0;
    }
    unsigned char pop_back() {
        if (len > 0) {
            -- len;
            unsigned char pos = (head+len)%52;
            return pos&1 ? cards[pos>>1] >> 4 : cards[pos>>1] & 0xf;
        }
        return 0;
    }
    unsigned char size() {
        return len;
    }
    bool empty() {
        return len==0;
    }
    void clear() {
        len = head = 0;
    }
    unsigned char operator[] (unsigned char index) const {
        return front(index);
    }
    bool operator== (const pile& rhs) const {
        if (len != rhs.len) return false;
        for (unsigned char i=0; i<len; ++i)
            if (front(i) != rhs[i]) return false;
        return true;
    }
};

struct deck: pile {
    vector<pile> piles; unsigned char cur;
    bool operator== (const deck& rhs) const {
        if (len != rhs.len || piles.size() != rhs.piles.size() || cur != rhs.cur) return false;
        for (unsigned char i=0; i<len; ++i)
            if (front(i) != rhs[i]) return false;
        unsigned size = piles.size();
        for (unsigned char i=0; i<size; ++i)
            if (!(piles[i] == rhs.piles[i])) return false;
        return true;
    }
};

struct hash5381lShift5 {
    unsigned int operator()(deck d) const {
        unsigned int hash = 5381;
        unsigned char size = d.size();
        for (unsigned char i=0; i<size; ++i)
            hash = ((hash<<5) + hash) + d[i];
        size = d.piles.size();
        for (unsigned char i=0; i<size; ++i) {
            unsigned char size1 = d.piles[i].size();
            for (unsigned char j=0; j<size1; ++j)
                hash = ((hash<<5) + hash) + d.piles[i][j];
        }
        return hash;
    }
};

enum Type{None, Win, Loss, Draw};
struct Result {
    Type type;
    unsigned int step;
    Result(): type(None) {}
};

Result judge(deck& d) {
    unordered_set<deck, hash5381lShift5> ds;
    d.piles = vector<pile>(7);
    for (unsigned char i=0; i<14; ++i)
        d.piles[i%7].push_back(d.pop_front());
    Result result; result.step = 14;
    ds.insert(d);
    while (result.type == None) {
        for (unsigned char i=0; i<d.piles.size(); ++i) {
            if (!d.piles[i].empty()) {
                d.piles[i].push_back(d.pop_front());
                ++ result.step;
                unsigned char v;
                while (d.piles[i].size() >= 3) {
                    v = d.piles[i][0] + d.piles[i][1] + d.piles[i].back();
                    if (v == 10 || v==20 || v==30) {
                        d.push_back(d.piles[i].pop_front());
                        d.push_back(d.piles[i].pop_front());
                        d.push_back(d.piles[i].pop_back());
                    } else {
                        v = d.piles[i].front() + d.piles[i].back() + d.piles[i].back(1);
                        if (v == 10 || v==20 || v==30) {
                            d.push_back(d.piles[i].pop_front());
                            d.push_back(d.piles[i].back(1));
                            d.push_back(d.piles[i].back());
                            d.piles[i].pop_back();
                            d.piles[i].pop_back();
                        } else {
                            v = d.piles[i].back() + d.piles[i].back(1) + d.piles[i].back(2);
                            if (v == 10 || v==20 || v==30) {
                                d.push_back(d.piles[i].back(2));
                                d.push_back(d.piles[i].back(1));
                                d.push_back(d.piles[i].back());
                                d.piles[i].pop_back();
                                d.piles[i].pop_back();
                                d.piles[i].pop_back();
                            }
                        }
                    }
                    if (v != 10 && v != 20 && v != 30) break;
                }
                if (d.empty()) {
                    result.type = Loss;
                    return result;
                }
            }
            if (d.piles[i].empty()) {
                d.piles.erase(d.piles.begin() + i);
                if (d.piles.size() == 0) {
                    result.type = Win;
                    return result;
                }
                d.cur %= d.piles.size();
                -- i;
            } else d.cur = (d.cur+1) % d.piles.size();
            if (ds.count(d)) {
                result.type = Draw;
                return result;
            } else ds.insert(d);
        }
    }
    return result;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (true) {
        deck d;
        for (unsigned char i=0; i<52; ++i) {
            unsigned short card; cin >> card;
            if (card == 0) return 0;
            d.push_back(card);
        }
        if (!d.empty()) {
            d.cur = 0;
            Result result = judge(d);
            cout << (result.type == Win ? "Win " : (result.type == Loss ? "Loss" : "Draw")) << ": " << result.step << endl;
        }
    }
    return 0;
}