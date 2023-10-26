#define L 102000
char s[L]; int sa[L], rk1[L], rk2[L], c[L], height[L], n;

bool eq(const int *y, int i, int j, int w) {
    return y[i]==y[j] && max(i, j) + w < n && y[i+w]==y[j+w];
}

void build() {
    int m = 128, *x = rk1, *y = rk2;     // m需要根据字符的实际范围初始化
    for (int i=0; i<m; ++i) c[i] = 0;
    for (int i=0; i<n; ++i) ++c[x[i] = s[i]];  // s[i]可能需要转化（压缩范围）
    for (int i=1; i<m; ++i) c[i] += c[i-1];
    for (int i=n-1; i>=0; --i) sa[--c[x[i]]] = i;
    for (int k=1; k<n; k<<=1) {
        int p = 0;
        for (int i=n-k; i<n; ++i) y[p++] = i;
        for (int i=0; i<n; ++i) if (sa[i] >= k) y[p++] = sa[i]-k;
        for (int i=0; i<m; ++i) c[i] = 0;
        for (int i=0; i<n; ++i) ++c[x[y[i]]];
        for (int i=1; i<m; ++i) c[i] += c[i-1];
        for (int i=n-1; i>=0; --i) sa[--c[x[y[i]]]] = y[i];
        int *z = x; x = y; y = z;
        p = 1; x[sa[0]] = 0;
        for (int i=1; i<n; ++i) x[sa[i]] = eq(y, sa[i-1], sa[i], k) ? p-1 : p++;
        if (p == n) break;
        m = p;
    }
    for (int i=0, k=0; i<n; ++i) {
        if (x[i] == 0) continue;
        if (k) --k;
        int j = sa[x[i]-1];
        while (max(i, j) + k < n && s[i+k] == s[j+k]) ++k;
        height[x[i]] = k;
    }
}