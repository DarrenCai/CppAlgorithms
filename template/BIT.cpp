/**
 * 树状数组
 * Binary Indexed Tree
 */

#define N 100010
int a[N], c[N], n; //原数组与树状数组

int lowbit(int i) {
    return i&(-i);
}

/**
 * 更新
 * 这里以区间更新(加法)为例
 */
void update(int i, int k) {   //在i位置加上k
    while (i <= n) {
        c[i] += k;
        i += lowbit(i);
    }
}

/**
 * 查询
 * 这里以区间查询(区间求和)为例
 */
int query(int i) {      //求a[1...i]的和
    int sum = 0;
    while (i > 0) {
        sum += c[i];
        i -= lowbit(i);
    }
    return sum;
}