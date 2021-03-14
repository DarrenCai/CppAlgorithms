/* Euclid algorithm, 欧几里德算法 */
int gcd(int a, int b) {
    return b==0 ? a : gcd(b, a%b);
}

int gcd(int a, int b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
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
void gcd(int a, int b, int& g, int& x, int& y) {
    if (!b) {
        g = a; x = 1; y = 0;
    } else {
        gcd(b, a%b, g, y, x);
        y -= x*(a/b);
    }
}