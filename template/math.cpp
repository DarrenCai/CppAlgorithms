/* Euclid algorithm, 欧几里德算法 */
int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

/* 出自编程之美的求最大公约数算法 */
int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a < 0) return gcd(-a, b);
    if (a == 0) return b;
    if (a == 1) return 1;
    if (a & 1) {
        if (b & 1) return gcd(a, (b-a)>>1);
        return gcd(a, b >> 1);
    } else {
        if (b & 1) return gcd(a >> 1, b);
        return gcd(a >> 1, b >> 1) << 1;
    }
}

/**
 * 下面的a,b,c为任意整数,g=gcd(a,b)
 * 扩展欧几里德算法: 找出一对整数(x,y),使得ax+by=gcd(a,b)
 * 结论1: 若方程ax+by=c的一组整数解为(x0,y0),则它的任意整数解都可以写成(x0+kb', y0-ka'),
 *       其中a'=a/g,b'=b/g,k取任意整数。
 * 结论2: 若方程ax+by=g的一组解是(x0,y0),
 *       则当c是g的倍数时ax+by=c的一组解是(x0*(c/g), y0*(c/g));当c不是g的倍数时无整数解。
 */
int gcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1; y = 0; return a;
    } else {
        int g = gcd(b, a%b, y, x);
        y -= a/b*x;
        return g;
    }
}

/**
 * 求a模n的逆，逆不存在时返回-1
 */
int inv(int a, int n) {
    int x, y;
    return gcd(a, n, x, y) == 1 ? (x + n) % n : -1;
}

/**
 * 求1, 2, 3, ..., n中与n互素的数的个数
 */
int euler_phi(int n) {
    int m = sqrt(n+0.5);
    int ans = n;
    for(int i = 2; i <= m; i++) if(n % i == 0) {
        ans = ans / i * (i-1);
        while(n % i == 0) n /= i;
    }
    if(n > 1) ans = ans / n * (n-1);
    return ans;
}

/**
 * 计算1~n中所有数的欧拉phi函数值,复杂度O(nlogn)
 */
void phi_table(int n, int* phi) {
    for(int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; i++) if(!phi[i])
        for(int j = i; j <= n; j += i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i-1);
        }
}

/**
 * 计算a^n mod M
 */
#define M 1007
int pow_mod(long long a, int n) {
    int ans = 1;
    while (n) {
        if (n & 1) ans = ans*a % M;
        a = a*a % M;
        n >>= 1;
    }
    return ans;
}

namespace fft {
    #include <cmath>
    #define N 1<<21
    int res[N], tot;
    struct complex {
        double x, y;
        void operator+= (const complex &t) {
            x += t.x; y += t.y;
        }
        complex operator- (const complex &t) const {
            return {x - t.x, y - t.y};
        }
        complex operator* (const complex &t) const {
            return {x * t.x - y * t.y, x * t.y + y * t.x};
        }

    } a[N], b[N];
    
    /**
     * inv=1时求的是傅里叶变换（DFT），inv=-1时求的是傅里叶逆变换（IDFT）
     */
    void fft(complex (&a)[N], int inv) {
        for (int i=0, j=0; i<tot; ++i) { // 原地快速bit reversal
            if(j > i) {complex t = a[i]; a[i] = a[j]; a[j] = t;}
            int k = tot;
            while(j & (k >>= 1)) j &= ~k;
            j |= k;
        }
        for(int step=1; step<tot; step<<=1) {
            // 把每相邻两个“step点DFT”通过一系列蝴蝶变换合并为一个“2*step点DFT”
            double alpha = inv*M_PI / step;
            // 为求高效，我们并不是依次执行各个完整的DFT合并，而是枚举下标k
            // 对于一个下标k，执行所有DFT合并中该下标对应的蝴蝶变换，即通过E[k]和O[k]计算X[k]
            // 蝴蝶变换参考：http://en.wikipedia.org/wiki/Butterfly_diagram
            for(int k=0; k<step; k++) {
                // 计算omega^k
                complex wk = {cos(alpha*k), sin(alpha*k)};
                for(int Ek=k; Ek<tot; Ek += step<<1) { // Ek是某次DFT合并中E[k]在原始序列中的下标
                    int Ok = Ek + step; // Ok是该DFT合并中O[k]在原始序列中的下标
                    complex t = wk * a[Ok]; // 蝴蝶变换：x1 * omega^k
                    a[Ok] = a[Ek] - t;  // 蝴蝶变换：y1 = x0 - t
                    a[Ek] += t;         // 蝴蝶变换：y0 = x0 + t
                }
            }
        }
    }

    void workFFT(int n, int m) { // a[0, n], b[0, m]
        int bit = 0;
        while ((1 << bit) < n + m + 1) ++bit;
        tot = 1 << bit;
        fft(a, 1); fft(b, 1);
        for (int i=0; i<tot; ++i) a[i] = a[i] * b[i]; //点表示法直接运算
        fft(a, -1); //逆变换，点表示法转换为多项式表示法
        for (int i=0, j=m+n; i<=j; ++i) res[i]  = a[i].x / tot + 0.5; //向上取整
    }
}

namespace simplex {
    /**
     * 单纯形在必然有解时的一种实现，能算出优化目标的最大值或者指出最大值无界
     */
    #define INF 1e100
    #define M 10005
    #define N 1005
    double a[M][N], b[M], c[N], ans; int m, n; // m个约束n个变量

    void pivot(int l, int e) {  // 转轴操作函数
        b[l] /= a[l][e];
        for (int j = 1; j <= n; j++) if (j != e) a[l][j] /= a[l][e];
        a[l][e] = 1 / a[l][e];

        for (int i = 1; i <= m; i++) if (i != l && abs(a[i][e]) > 0.) {
            b[i] -= a[i][e] * b[l];
            for (int j = 1; j <= n; j++) if (j != e) a[i][j] -= a[i][e] * a[l][j];
            a[i][e] = -a[i][e] * a[l][e];
        }

        ans += c[e] * b[l];
        for (int j = 1; j <= n; j++) if (j != e) c[j] -= c[e] * a[l][j]; c[e] = -c[e] * a[l][e];
    }

    double simplex() {
        // 初始时如果找不到e进行替换，那么说明原问题无解。
        // for (e = 1; e <= n; e++) 判断是否所有初始c[e]都<=0
        while (true) {
            int e = 0, l = 0;
            for (e = 1; e <= n; e++) if (c[e] > 0.) break;
            if (e == n + 1) return ans;  // 此时ans即为最优解
            double mn = INF;
            for (int i = 1; i <= m; i++) {
                if (a[i][e] > 0. && mn > b[i] / a[i][e]) {
                    mn = b[i] / a[i][e];  // 找对这个e限制最紧的l
                    l = i;
                }
            }
            if (mn == INF) return INF;  // 无界
            pivot(l, e);                // 转动l,e
        }
    }
}

namespace simplex2 {
    // 改进单纯形算法的实现
    // 参考：http://en.wikipedia.org/wiki/Simplex_algorithm
    // 输入矩阵a描述线性规划的标准形式。a为m+1行n+1列，其中行0~m-1为不等式，行m为目标函数（最大化）。列0~n-1为变量0~n-1的系数，列n为常数项
    // 第i个约束为a[i][0]*x[0] + a[i][1]*x[1] + ... <= a[i][n]
    // 目标为max(a[m][0]*x[0] + a[m][1]*x[1] + ... + a[m][n-1]*x[n-1] - a[m][n])
    // 注意：变量均有非负约束x[i] >= 0
    #define INF 1e100
    #define eps 1e-10
    #define M 10005
    #define N 1005
    int m; // 约束个数
    int n; // 变量个数
    double a[M][N]; // 输入矩阵
    int B[M], C[N]; // 算法辅助变量

    void pivot(int r, int c) {
        int t = C[c]; C[c] = B[r]; B[r] = t;
        a[r][c] = 1 / a[r][c];
        for (int j = 0; j <= n; j++) if (j != c) a[r][j] *= a[r][c];
        for (int i = 0; i <= m; i++) if (i != r) {
            for (int j = 0; j <= n; j++) if (j != c) a[i][j] -= a[i][c] * a[r][j];
            a[i][c] = -a[i][c] * a[r][c];
        }
    }

    bool feasible() {
        while (true) {
            int r, c; double p = INF;
            for (int i = 0; i < m; i++) if (a[i][n] < p) p = a[r = i][n];
            if (p > -eps) return true;
            p = 0.;
            for (int i = 0; i < n; i++) if (a[r][i] < p) p = a[r][c = i];
            if (p > -eps) return false;
            p = a[r][n] / a[r][c];
            for (int i = r+1; i < m; i++) if (a[i][c] > eps) {
                double v = a[i][n] / a[i][c];
                if (v < p) r = i, p = v;
            }
            pivot(r, c);
        }
    }

    // 解有界返回1，无解返回0，无界返回-1。x[i]的值为可行解，ret为目标函数的值
    int simplex(double x[N], double& ret) {
        for (int i = 0; i < n; i++) C[i] = i;
        for (int i = 0; i < m; i++) B[i] = n+i;
        if (!feasible()) return 0;
        while (true) {
            int r, c; double p = 0.;
            for (int i = 0; i < n; i++) if (a[m][i] > p) p = a[m][c = i];
            if (p < eps) {
                for (int i = 0; i < n; i++) if (C[i] < n) x[C[i]] = 0;
                for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = a[i][n];
                ret = -a[m][n];
                return 1;
            }
            p = INF;
            for (int i = 0; i < m; i++) if (a[i][c] > eps) {
                double v = a[i][n] / a[i][c];
                if (v < p) r = i, p = v;
            }
            if (p == INF) return -1;
            pivot(r, c);
        }
    }
}