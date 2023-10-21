#define N 1010
int nxt[N]; // 失配函数/后缀函数

/* MP算法计算nxt数组
 * 利用MP算法的nxt数组可以求字符串的循环节
 * 统计模式串能重叠的所有匹配时，一定要用MP算法计算nxt数组
 */
void getNext(const char (&p)[N], int n) {
    nxt[0] = -1;
    for (int i=0, j=-1; i<n; nxt[++i] = ++j) while (j>=0 && p[j]!=p[i]) j = nxt[j];
}

/*
 * KMP算法计算nxt数组
 * KMP算法计算nxt数组，仅仅在求模式串不能重叠的匹配上有效率优化，通用性上不如MP算法
 */
void getNext(const char (&p)[N], int n) {
    nxt[0] = -1;
    for (int i=0, j=0; i<n;) {
        while (j>=0 && p[j]!=p[i]) j = nxt[j];
        ++i; ++j;
        nxt[i] = p[i]==p[j] ? nxt[j] : j;
    }
}

int kmp(const char (&s)[N], const char (&p)[N], int m, int n) {
    getNext(p, n);      // 如果统计模式串能重叠的所有匹配，则一定要用MP算法计算nxt数组
    for (int i=0, j=0; i<m; ++i) {
        while (j>=0 && p[j]!=s[i]) j = nxt[j];
        if (++j == n) {
            // 匹配到了一个
            return i+1 - j;
            // 不return则可以继续寻找后续匹配
        }
    }
    return -1;
}