#include <cmath>

#define eps 1e-12

double cubic_root(double x) {
    return x<0. ? -pow(-x, 1./3.) : pow(x, 1./3.);
}

int solve_cubic_equation(double a, double b, double c, double d, double (&x)[3]) {
    // 一元三次方程求解，返回不同实根的数量，a!=0
    double A = b*b - 3*a*c, B = b*c - 9*a*d, C = c*c - 3*b*d, delta = B*B - 4.*A*C;
    // https://blog.csdn.net/u012912039/article/details/101363323
    // A=B=0时，方程有三重实根-c/b
    // delta > 0 时，方程有一个实根和一对共轭虚根
    // delta = 0 时，方程有有两个不同实根，其中一个是两重根
    // delta < 0 时，方程有三个不同实根
    if (A == 0. && B == 0.) {
        x[0] = -c/b;
        return 1;
    } else if (delta > 0.) {
        delta = sqrt(delta);
        double y1 = A*b + 1.5*a*(delta-B), y2 = A*b - 1.5*a*(delta+B);
        x[0] = -(cubic_root(y1) + cubic_root(y2) + b)/3./a;
        return 1;
    } else if (delta > -eps) {
        x[0] = B/A - b/a; x[1] = -B/2./A;
        return 2;
    } 
    double sA = sqrt(A), t = acos((A*b-1.5*a*B)/A/sA)/3., s = sqrt(3)*sin(t); t = cos(t); a *= -3.;
    x[0] = (b + 2*sA*t) / a; x[1] =  (b - sA*(t + s)) / a; x[2] = (b - sA*(t - s)) / a;
    return 3;
}

double find_a_root(double a, double b, double c, double d) {
    // 求出一元三次方程的一个实根，a!=0
    double A = b*b - 3*a*c, B = b*c - 9*a*d, C = c*c - 3*b*d, delta = B*B - 4.*A*C;
    if (A == 0. && B == 0.) return -c/b;
    if (delta > 0.) {
        delta = sqrt(delta);
        double y1 = A*b + 1.5*a*(delta-B), y2 = A*b - 1.5*a*(delta+B);
        return -(cubic_root(y1) + cubic_root(y2) + b)/3./a;
    } else if (delta > -eps) return -B/2./A;
    double sA = sqrt(A), t = acos((A*b-1.5*a*B)/A/sA)/3.;
    return -(b + 2*sA*cos(t)) / 3. / a;
}

int solve_quadratic_equation(double a, double b, double c, double *x) {
    // 解一元二次方程（a可以为0）并返回实根数量
    if (a == 0.) {
        if (b == 0.) return 0;
        *x = -c/b;
        return 1;
    }
    double delta = b*b - 4.*a*c;
    if (delta < 0.) {
        if (delta < -eps) return 0;
        delta = 0.;
    }
    a *= 2; delta = sqrt(delta);
    if (delta == 0. || delta < a*eps) {
        *x = -b/a;
        return 1;
    }
    *x = (-b-delta)/a; *(++x) = (delta-b)/a;
    return 2;
}