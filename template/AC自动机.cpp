#include <cstring>
using namespace std;

#define M 1000010   // 文本串长度
#define N 152       // 模式串数量
#define L 72        // 模式串最大长度
#define C 26        // 全部字符数，示例仅考虑26个小写字母

/*
 * 获取字符索引，示例仅考虑26个小写字母
 * 这里要按照实际需要做改动
 */
int idx(char c) {
    return c-'a';
}

struct node {
    int ch[C],  // 下一节点的编号
        val,    // val>0时表示根节点到此节点形成了一个模式串，记录其编号，这里要按照实际需要做改动
        last,   // 后缀链接（suffix link）：表示此节点沿着失配指针往回走时，遇到的下一个模式串节点编号
        f;      // 失配指针
} trie[N*L];

/*
 * 变量申明，示例是统计各个模式串出现的次数
 * 这里要按照实际需要做改动
 */
int q[N*L], cnt[N], n, t; char p[N][L], s[M];

void insert(const char (&s)[L], int v) {
    int x = 0;
    for (int i=0; s[i]; ++i) {
        int c = idx(s[i]), &k = trie[x].ch[c];
        if (!k) memset(trie + (k = ++t), 0, sizeof(node));
        x = k;
    }
    trie[x].val = v;
}

void getFail() {
    int head = 0, tail = 0;
    for (int i=0, u; i<C; ++i) if (u = trie[0].ch[i]) q[tail++] = u;
    while (head < tail) {
        int x = q[head++];
        for (int i=0; i<C; ++i) {
            int &u = trie[x].ch[i];
            if (!u) {
                u = trie[trie[x].f].ch[i];
                continue;
            }
            q[tail++] = u;
            int &f = trie[u].f = trie[trie[x].f].ch[i];
            trie[u].last = trie[f].val ? f : trie[f].last;
        }
    }
}

/*
 * 有匹配到，dfs方式更新结果
 * 这里要按照实际需要做改动
 */
void update(int x) {
    if (x) ++cnt[trie[x].val], update(trie[x].last);
}

void find(const char (&s)[M]) {
    int x = 0;
    for (int i=0; s[i]; ++i) {
        x = trie[x].ch[idx(s[i])];
        if (trie[x].val) update(x);
        else if (trie[x].last) update(trie[x].last);
    }
}

/*
 * 求解的主程序
 * 这里要按照实际需要做改动
 */
void solve() {
    memset(trie, t=0, sizeof(node));
    memset(cnt, 0, sizeof(cnt));

    // 读入模式串并构建trie，模式串可能存在重复
    // map<string, int> id;
    for (int i=1; i<=n; ++i) {
        // cin >> p[i];
        insert(p[i], i);
        // id[string(p[i])] = i;
    }

    // 获取失配函数
    getFail();
    
    // cin >> s;
    // 读入文本串，查找，得到结果
    find(s);

    // 输出
    // cout << ans << endl;
}