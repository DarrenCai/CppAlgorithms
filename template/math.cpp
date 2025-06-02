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