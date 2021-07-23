#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define N 1010
int nxt[N];

void getNext(const char (&p)[N]) {
    nxt[0] = -1;
    int len = strlen(p), i = 0, j = -1;
    while (i < len) {
        if (j==-1 || p[i] == p[j]) {
            if (p[++i] == p[++j]) {
                nxt[i] = nxt[j];
            } else nxt[i] = j;
        } else j = nxt[j];
    }
}

int kmp(const char (&t)[N], const char (&p)[N]) {
    getNext(p);
    int tLen = strlen(t), pLen = strlen(p), i = 0, j = 0;
    while (i<tLen && j<pLen) {
        if (j==-1 || t[i] == p[j]) {
            ++i; ++j;
        } else {
            j = nxt[j];
        }
    }
    if (j == pLen) return i-j;
    return -1;
}

void kmp(const char (&t)[N], const char (&p)[N], vector<int>& ans) {
    getNext(p);
    int tLen = strlen(t), pLen = strlen(p), i = 0, j = 0;
    while (i<tLen) {
        if (j==-1 || t[i] == p[j]) {
            ++i; ++j;
        } else {
            j = nxt[j];
        }
        if (j == pLen) {
            ans.push_back(i-j);
            j = nxt[j];
        }
    }
}

int kmpCount(const char (&t)[N], const char (&p)[N]) {
    getNext(p);
    int ans = 0;
    int tLen = strlen(t), pLen = strlen(p), i = 0, j = 0;
    while (i<tLen) {
        if (j==-1 || t[i] == p[j]) {
            ++i; ++j;
        } else {
            j = nxt[j];
        }
        if (j == pLen) {
            ++ ans;
            j = nxt[j];
        }
    }
    return ans;
}

int main() {
    char t1[N] = "abcdefghlmngh";
    char p1[N] = "gh";
    vector<int> v1;
    kmp(t1, p1, v1);
    cout << t1 << ' ' << p1 << ':';
    for (int i: v1) cout << ' ' << i;
    cout << endl;
    char t2[N] = "abcdefggggglmngg";
    char p2[N] = "gg";
    vector<int> v2;
    kmp(t2, p2, v2);
    cout << t2 << ' ' << p2 << ':';
    for (int i: v2) cout << ' ' << i;
    cout << endl;
}