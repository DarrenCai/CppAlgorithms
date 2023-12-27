/**
 * Manacher算法
 */

#define L 600060
char str[L>>1],     // 原始串
    s[L];           // 拓展串
int r[L],           // 回文半径r[i]，r[i]-1就是原始串中以对应位置为中心的回文串的最大长度
    n;

void manacher() {
    // cin >> str;      // 读入原始串后先构建拓展串
    n = 2; s[0] = '@'; s[1] = '#';      // '@'用来防止数组越界
    for (int i=0; str[i]; ++i) s[n++] = str[i], s[n++] = '#';
    s[n] = '\0';
    /**
     * mx：所有字符产生的最大回文子串的最大右边界，
     * id：产生这个最大右边界的对称轴的位置。
     */
    for (int i=1, mx=0, id=0; i<n; ++i) {
        if (i < mx) r[i] = min(r[(id<<1) - i], mx - i);
        else r[i] = 1;
        while (s[i + r[i]] == s[i - r[i]]) r[i]++;
        if (i + r[i] > mx) mx = i + r[i], id = i;
    }
}