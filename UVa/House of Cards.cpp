/**
 * UVa1085/LA4451
 * 纸牌房屋
 * World Finals >> 2009 - Stockholm
 */

#include <iostream>
using namespace std;

#define M 13
int m, kase = 0; char s[7];

struct card {
    int v; char c;
    card():v(0) {};
    int f() const;
} p[M<<1];

int card::f() const {
    return c == p[0].c ? 1 : -1;
}

struct tri {
    card a, b, c;
    int score() const {
        if (!a.v || !b.v || !c.v) return 0;
        int s = a.v + b.v + c.v;
        return a.f() + b.f() + c.f() > 0 ? s : -s;
    }
};

struct state {
    tri ta, tb, tc, td, te, tf; card a, b;
    int score() const {
        return tri{ta.a, p[1], p[2]}.score() + ta.score() + tri{tb.a, p[3], p[4]}.score() + tb.score()
            + tri{tc.a, p[5], p[6]}.score() + tc.score() + tri{td.a, ta.c, tb.b}.score() + td.score()
            + tri{te.a, tb.c, tc.b}.score() + te.score() + tri{tf.a, td.c, te.b}.score() + tf.score()
            + (a.c == p[0].c ? a.v : -a.v) + (b.c == p[0].c ? b.v : -b.v);
    }
};

int alphabeta(const state& s, int i, int alpha, int beta) {
    if (i == m) return s.score();
    state ch[24]; int t = 0;
    if (i&1) {
        if (s.b.v) {
            if (!s.ta.a.v) ch[t] = s, ch[t++].ta.a = p[i], ch[t] = s, ch[t].ta.a = s.b, ch[t++].b = p[i];
            if (!s.tb.a.v) ch[t] = s, ch[t++].tb.a = p[i], ch[t] = s, ch[t].tb.a = s.b, ch[t++].b = p[i];
            if (!s.tc.a.v) ch[t] = s, ch[t++].tc.a = p[i], ch[t] = s, ch[t].tc.a = s.b, ch[t++].b = p[i];
            if (!s.td.a.v && s.ta.c.v && s.tb.b.v) ch[t] = s, ch[t++].td.a = p[i], ch[t] = s, ch[t].td.a = s.b, ch[t++].b = p[i];
            if (!s.te.a.v && s.tb.c.v && s.tc.b.v) ch[t] = s, ch[t++].te.a = p[i], ch[t] = s, ch[t].te.a = s.b, ch[t++].b = p[i];
            if (!s.tf.a.v && s.td.c.v && s.te.b.v) ch[t] = s, ch[t++].tf.a = p[i], ch[t] = s, ch[t].tf.a = s.b, ch[t++].b = p[i];
            if (s.ta.a.v && !s.ta.b.v) ch[t] = s, ch[t].ta.b = s.b, ch[t].ta.c = p[i], ch[t++].b.v = 0, ch[t] = s, ch[t].ta.b = p[i], ch[t].ta.c = s.b, ch[t++].b.v = 0;
            if (s.tb.a.v && !s.tb.b.v) ch[t] = s, ch[t].tb.b = s.b, ch[t].tb.c = p[i], ch[t++].b.v = 0, ch[t] = s, ch[t].tb.b = p[i], ch[t].tb.c = s.b, ch[t++].b.v = 0;
            if (s.tc.a.v && !s.tc.b.v) ch[t] = s, ch[t].tc.b = s.b, ch[t].tc.c = p[i], ch[t++].b.v = 0, ch[t] = s, ch[t].tc.b = p[i], ch[t].tc.c = s.b, ch[t++].b.v = 0;
            if (s.td.a.v && !s.td.b.v) ch[t] = s, ch[t].td.b = s.b, ch[t].td.c = p[i], ch[t++].b.v = 0, ch[t] = s, ch[t].td.b = p[i], ch[t].td.c = s.b, ch[t++].b.v = 0;
            if (s.te.a.v && !s.te.b.v) ch[t] = s, ch[t].te.b = s.b, ch[t].te.c = p[i], ch[t++].b.v = 0, ch[t] = s, ch[t].te.b = p[i], ch[t].te.c = s.b, ch[t++].b.v = 0;
            if (s.tf.a.v && !s.tf.b.v) ch[t] = s, ch[t].tf.b = s.b, ch[t].tf.c = p[i], ch[t++].b.v = 0, ch[t] = s, ch[t].tf.b = p[i], ch[t].tf.c = s.b, ch[t++].b.v = 0;
        } else {
            ch[t] = s; ch[t++].b = p[i];
            if (!s.ta.a.v) ch[t] = s, ch[t++].ta.a = p[i];
            if (!s.tb.a.v) ch[t] = s, ch[t++].tb.a = p[i];
            if (!s.tc.a.v) ch[t] = s, ch[t++].tc.a = p[i];
            if (!s.td.a.v && s.ta.c.v && s.tb.b.v) ch[t] = s, ch[t++].td.a = p[i];
            if (!s.te.a.v && s.tb.c.v && s.tc.b.v) ch[t] = s, ch[t++].te.a = p[i];
            if (!s.tf.a.v && s.td.c.v && s.te.b.v) ch[t] = s, ch[t++].tf.a = p[i];
        }
    } else {
        if (s.a.v) {
            if (!s.ta.a.v) ch[t] = s, ch[t++].ta.a = p[i], ch[t] = s, ch[t].ta.a = s.a, ch[t++].a = p[i];
            if (!s.tb.a.v) ch[t] = s, ch[t++].tb.a = p[i], ch[t] = s, ch[t].tb.a = s.a, ch[t++].a = p[i];
            if (!s.tc.a.v) ch[t] = s, ch[t++].tc.a = p[i], ch[t] = s, ch[t].tc.a = s.a, ch[t++].a = p[i];
            if (!s.td.a.v && s.ta.c.v && s.tb.b.v) ch[t] = s, ch[t++].td.a = p[i], ch[t] = s, ch[t].td.a = s.a, ch[t++].a = p[i];
            if (!s.te.a.v && s.tb.c.v && s.tc.b.v) ch[t] = s, ch[t++].te.a = p[i], ch[t] = s, ch[t].te.a = s.a, ch[t++].a = p[i];
            if (!s.tf.a.v && s.td.c.v && s.te.b.v) ch[t] = s, ch[t++].tf.a = p[i], ch[t] = s, ch[t].tf.a = s.a, ch[t++].a = p[i];
            if (s.ta.a.v && !s.ta.b.v) ch[t] = s, ch[t].ta.b = s.a, ch[t].ta.c = p[i], ch[t++].a.v = 0, ch[t] = s, ch[t].ta.b = p[i], ch[t].ta.c = s.a, ch[t++].a.v = 0;
            if (s.tb.a.v && !s.tb.b.v) ch[t] = s, ch[t].tb.b = s.a, ch[t].tb.c = p[i], ch[t++].a.v = 0, ch[t] = s, ch[t].tb.b = p[i], ch[t].tb.c = s.a, ch[t++].a.v = 0;
            if (s.tc.a.v && !s.tc.b.v) ch[t] = s, ch[t].tc.b = s.a, ch[t].tc.c = p[i], ch[t++].a.v = 0, ch[t] = s, ch[t].tc.b = p[i], ch[t].tc.c = s.a, ch[t++].a.v = 0;
            if (s.td.a.v && !s.td.b.v) ch[t] = s, ch[t].td.b = s.a, ch[t].td.c = p[i], ch[t++].a.v = 0, ch[t] = s, ch[t].td.b = p[i], ch[t].td.c = s.a, ch[t++].a.v = 0;
            if (s.te.a.v && !s.te.b.v) ch[t] = s, ch[t].te.b = s.a, ch[t].te.c = p[i], ch[t++].a.v = 0, ch[t] = s, ch[t].te.b = p[i], ch[t].te.c = s.a, ch[t++].a.v = 0;
            if (s.tf.a.v && !s.tf.b.v) ch[t] = s, ch[t].tf.b = s.a, ch[t].tf.c = p[i], ch[t++].a.v = 0, ch[t] = s, ch[t].tf.b = p[i], ch[t].tf.c = s.a, ch[t++].a.v = 0;
        } else {
            ch[t] = s; ch[t++].a = p[i];
            if (!s.ta.a.v) ch[t] = s, ch[t++].ta.a = p[i];
            if (!s.tb.a.v) ch[t] = s, ch[t++].tb.a = p[i];
            if (!s.tc.a.v) ch[t] = s, ch[t++].tc.a = p[i];
            if (!s.td.a.v && s.ta.c.v && s.tb.b.v) ch[t] = s, ch[t++].td.a = p[i];
            if (!s.te.a.v && s.tb.c.v && s.tc.b.v) ch[t] = s, ch[t++].te.a = p[i];
            if (!s.tf.a.v && s.td.c.v && s.te.b.v) ch[t] = s, ch[t++].tf.a = p[i];
        }
    }
    for (int j=0; j<t; ++j) {
        int v = alphabeta(ch[j], i+1, alpha, beta);
        i&1 ? beta = min(beta, v) : alpha = max(alpha, v);
        if (beta <= alpha) break;
    }
    return i&1 ? beta : alpha;
}

void solve() {
    cin >> m; m <<= 1;
    for (int i=0; i<m; ++i) cin >> p[i].v >> p[i].c;
    int v = alphabeta(state(), 8, -500, 500);
    if (v) {
        if (p[0].c == 'R') {
            if (s[0] == 'A') cout << "Case " << ++kase << ": Axel " << (v > 0 ? "wins " : "loses ") << abs(v) << endl;
            else cout << "Case " << ++kase << ": Birgit " << (v < 0 ? "wins " : "loses ") << abs(v) << endl;
        } else {
            if (s[0] == 'A') cout << "Case " << ++kase << ": Axel " << (v < 0 ? "wins " : "loses ") << abs(v) << endl;
            else cout << "Case " << ++kase << ": Birgit " << (v > 0 ? "wins " : "loses ") << abs(v) << endl;
        }
    } else cout << "Case " << ++kase << ": Axel and Birgit tie" << endl;
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("ou.txt", "w", stdout);
    while (cin >> s && s[0] != 'E') solve();
    return 0;
}