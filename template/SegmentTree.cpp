/**
 * 线段树模板，很容易改成动态开点形式的
 * 单次点修改操作涉及到的区间结点数上限是⌈logN⌉+1,
 * 单次区间修改操作涉及到的区间结点数上限是4⌈logN⌉,
 * 结合实际进行的不同区间操作次数上限可以得出动态结点数上限
 * 具体可以参见Heap Manager.cpp
 */

#define N 1000100
#define INF 1000000000
struct node {int s, x, y; node(int s, int x, int y): s(s), x(x), y(y) {}} p(0, 0, 0);
int sum[N], minv[N], maxv[N], add[N], set[N], y1, y2, n;

node query(int o, int l, int r, int t = 0) {
    if (set[o] >= 0) {
        t += add[o] + set[o];
        return node(t * (min(r, y2) - max(l, y1) + 1), t, t);
    }
    if (l>=y1 && r<=y2) return node(sum[o] + t*(r-l+1), t + minv[o], t + maxv[o]);
    int ss = 0, sx = INF, sy = 0, m = (l+r)>>1, lc = o<<1, rc = lc+1; t += add[o];
    if (y1 <= m) p = query(lc, l, m, t), ss += p.s, sx = min(sx, p.x), sy = max(sy, p.y);
    if (y2 > m) p = query(rc, m+1, r, t), ss += p.s, sx = min(sx, p.x), sy = max(sy, p.y);
    return node(ss, sx, sy);
}

void pushdown(int o, int l, int r) {
    if (set[o] >= 0) {
        int v = add[o] + set[o]; sum[o] = v * (r-l+1); minv[o] = v; maxv[o] = v;
    } else if (l < r) {
        int lc = o<<1, rc = lc+1;
        sum[o] = sum[lc] + sum[rc]; minv[o] = min(minv[lc], minv[rc]); maxv[o] = max(maxv[lc], maxv[rc]);
        sum[o] += add[o]*(r-l+1); minv[o] += add[o]; maxv[o] += add[o];
    } else sum[o] = minv[o] = maxv[o] = add[o];
}

// 这是区间修改的例子
void op(int o, int l, int r, int v, bool isAdd) {
    if (l>=y1 && r<=y2) {
        isAdd ? add[o] += v : (set[o] = v, add[o] = 0);
    } else {
        int m = (l+r)>>1, lc = o<<1, rc = lc+1;
        if (set[o] >= 0) set[lc] = set[rc] = set[o], add[lc] = add[rc] = 0, set[o] = -1;
        if (add[o]) add[lc] += add[o], add[rc] += add[o], add[o] = 0;
        y1 <= m ? op(lc, l, m, v, isAdd) : pushdown(lc, l, m);
        y2 > m ? op(rc, m+1, r, v, isAdd) : pushdown(rc, m+1, r);
    }
    pushdown(o, l, r);
}

void build(int o, int l, int r) {
    add[o] = sum[o] = maxv[o] = 0; set[o] = -1; minv[o] = INF;
    if (l < r) {
        int m = (l+r)>>1, lc = o<<1, rc = lc+1;
        build(lc, l, m); build(rc, m+1, r);
    }
}

void solve() {
    // 每次求解先构建线段树
    build(1, 1, n);
    // 执行op操作
    // 查询query
}