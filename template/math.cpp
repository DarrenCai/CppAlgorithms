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