/**
 * @ref https://blog.csdn.net/hlhgzx/article/details/150618753
 * 
 *     Priority Search Tree（PST，优先查找树）是一种结合了 Binary Search Tree（BST，二分搜索树）和 Priority Queue（优先级队列）的平衡树，
 * 能高效处理 3-sided range queries（三边范围查询，比如在二维空间中动态查找形如 [a, b] × (−∞, c] 或 [a, b] × [c, ∞)的矩形区域内所有点）问题。
 * 
 *     以二维点集 S 的 Priority Search Tree 来举例，它首先是小顶堆（或大顶堆），对 S 中各点的 y 坐标来说，树上任何一个结点的值不大于其子结点的值，
 * 因此从根结点出发到每个结点的路径相当于一个优先级队列。树上每个结点还存储一个分界值 d，将子树按照 x 坐标进行划分形成左右子树， 左子树各结点的 x
 * 坐标均小于 d，右子树各结点的 x 坐标均大于 d，且左右子树高度之差不超过1。
 * 
 *     Priority Search Tree 可以动态插入和删除，插入或者删除过程可以用 red-black tree（红黑树）进行旋转操作维持树的平衡，从而做到插入和删除的
 * 时间复杂度都是O(log n)。区间查询的时间复杂度是O(k + log ⁡n)，其中 k 是区间内符合要求的点数量。
 */

#include <algorithm>
using namespace std;

#define N 100010
long long x[N], y[N], d[N]; int ls[N], rs[N], s[N], p[N], q[N], f[N], a[N], n, t, c; bool v[N];
bool cmp(int i, int j) {
    return x[i] < x[j];
}
void build(int& o, int l, int r) {
    if (!o) o = ++t, ls[o] = rs[o] = s[o] = 0;
    if (l < r) {
        int u = r;
        for (int i=l; i<r; ++i) if (y[a[i]] < y[a[u]]) u = i;
        int k = a[u]; for (int i=u; i<r; ++i) a[i] = a[i+1]; a[r] = k;
        u = (l+r-1)>>1; while (u+1 < r & x[a[u+1]] == x[a[u]]) ++u;
        d[o] = x[a[u]]; build(ls[o], l, u);
        if (u+1 < r) build(rs[o], u+1, r-1);
        p[o] = k; f[ls[o]] = f[rs[o]] = q[k] = o; s[o] = r-l+1;
    } else p[o] = a[l], q[a[l]] = o, s[o] = 1;
}
void build() {
    for (int i=0; i<n; ++i) a[i] = i;
    int o = s[0] = t = 0; sort(a, a+n, cmp); build(o, 0, n-1);
}
int query(int o, int i) {
    if (!s[o] || y[p[o]] > y[i]) return 0;
    int cnt = 0;
    if (v[p[o]] && x[p[o]] <= x[i]) a[c++] = p[o], v[p[o]] = false, ++cnt;
    if (ls[o]) cnt += query(ls[o], i);
    if (rs[o] && x[i] > d[o]) cnt += query(rs[o], i);
    s[o] -= cnt;
    return cnt;
}
void remove(int i) {
    for (int o = q[i]; o; o = f[o]) --s[o];
}

int main() {
    // 读入数据 n、x、y 后构建优先查找树
    build();
    // 查找 query(1, i);
}