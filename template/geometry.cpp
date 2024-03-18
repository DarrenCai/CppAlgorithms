#include <cmath>

#define eps 1e-10
struct Point {
    double x, y;
    Point(double x = 0., double y = 0.): x(x), y(y) {}
    void Normalize() {
        double l = sqrt(x*x + y*y); x /= l; y /= l;
    }
};
typedef Point Vector;

Vector operator+ (const Vector& A, const Vector& B) {
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator- (const Vector& A, const Vector& B) {
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator* (const Vector& A, double p) {
    return Vector(A.x * p, A.y * p);
}

Vector operator/ (const Vector& A, double p) {
    return Vector(A.x / p, A.y / p);
}

bool operator< (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) {
    return A.x * B.x + A.y * B.y;
}

double Length(const Vector& A) {
    return sqrt(A.x*A.x + A.y*A.y);
}

double Angle(const Vector& A, const Vector& B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}

double Cross(const Vector& A, const Vector& B) {
    return A.x * B.y - A.y * B.x;
}

double Area2(const Point& A, const Point& B, const Point& C) {
    return Cross(B - A, C - A);
}

Vector Rotate(const Vector& A, double rad) {
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}

Vector Normal(const Vector& A) {
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}

Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    return P + v * (Cross(w, u) / Cross(v, w));
}

Point GetLineProjection(const Point& P, const Point& A, const Point& B) {
    Vector v = B-A;
    return A + v * (Dot(v, P-A) / Dot(v, v));
}

int sign(double x) {
    return x==0. ? 0 : (x < 0. ? -1 : 1);
}

bool SegmentProperIntersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    // return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
    return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;  // 部分卡精度的题目需要直接判断正负号
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) { // 不含端点
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

bool OnSegment2(const Point& p, const Point& a1, const Point& a2) { // 含端点
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}

double DistanceToLine(const Point& P, const Point& A, const Point& B) {
    Vector v1 = B - A, v2 = P - A;
    return abs(Cross(v1, v2)) / Length(v1);
}

double DistanceToSegment(const Point& P, const Point& A, const Point& B) {
    if (A == B) return Length(P-A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    return abs(Cross(v1, v2)) / Length(v1);
}

double PolygonArea(const Point* p, int n) { // 有向面积
    double area = 0;
    for (int i=n-2; i>0; --i) area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}

double PolygonArea(const Point* p, int n) { // 有向面积
    double area = p[0].y * (p[n-1].x - p[1].x) + p[n-1].y * (p[n-2].x - p[0].x);
    for (int i=n-2; i>0; --i) area += p[i].y * (p[i-1].x - p[i+1].x);
    return area/2;
}

int PointInPolygon(const Point& p, const Point* poly, int n) {
    int wn = 0;
    for (int i=0; i<n; ++i) {
        if (OnSegment2(p, poly[i], poly[(i+1)%n])) return -1; // 在边界上
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) ++wn;
        if (k < 0 && d2 <= 0 && d1 > 0) --wn;
    }
    if (wn != 0) return 1; // 内部
    return 0; // 外部
}

// Andrew算法计算凸包，输入点数组p，个数为n，输出点数组ch。函数返回凸包顶点数。
// 输入不能有重复点。函数执行完之后输入点的顺序被破坏
// 把两个 <= 改成 <，则凸包的顶点数可能变多，但实际形状一样
// 在精度要求高时建议用dcmp比较
int ConvexHull(const Point* p, int n, Point* ch) {
    sort(p, p+n); //先比较x坐标，再比较y坐标
    int m = 0;
    for (int i=0; i<n; ++i) {
        while (m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    for (int i=n-2, k=m; i>=0; --i) {
        while (m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) --m;
        ch[m++] = p[i];
    }
    if (n > 1) --m;
    return m;
}

// 用有向直线 A->B 切割多边形p，返回“左侧”。如果退化，可能会返回单点或者线段
int CutPolygon(const Point* p, int n, Point A, Point B, Point* q) {
    int m = 0; Vector v = B-A;
    for (int i=0; i<n; ++i) {
        Point C = p[i], D = p[(i+1)%n];
        if (dcmp(Cross(v, C-A)) >= 0) q[m++] = C;
        if (dcmp(Cross(v, C-D)) != 0) {
            Point ip = GetLineIntersection(A, v, C, D-C);
            if (OnSegment(ip, C, D)) q[m++] = ip;
        }
    }
    return m;
}

// 有向直线。它的左边就是对应的半平面
struct Line {
    Point P; // 直线上任意一点
    Vector v; // 方向向量。它的左边就是对应的半平面
    double ang; // 极角，即从x 正半轴旋转到向量v 所需要的角（弧度）
    Line() {}
    Line(const Point& P, const Vector& v):P(P),v(v){ ang = atan2(v.y, v.x); }
    bool operator< (const Line& L) const { // 排序用的比较运算符
        return ang < L.ang;
    }
};

// 点p在有向直线L的左边（线上不算）
bool OnLeft(const Line& L, const Point& p) {
    return Cross(L.v, p-L.P) > 0;
}

// 两直线交点。假定交点唯一存在
Point GetIntersection(const Line& a, const Line& b) {
    Vector u = a.P-b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}

// 半平面交的主过程
int HalfplaneIntersection(Line* L, int n, Point* poly) {
    sort(L, L+n); // 按极角排序
    Line *q = new Line[n]; // 双端队列
    int first, last; // 双端队列的第一个元素和最后一个元素的下标
    q[first = last = 0] = L[0]; // 双端队列初始化为只有一个半平面L[0]
    Point *p = new Point[n]; // p[i]为q[i]和q[i+1]的交点
    for (int i=1; i<n; ++i) {
        while (first < last && !OnLeft(L[i], p[last-1])) --last;
        while (first < last && !OnLeft(L[i], p[first])) ++first;
        q[++last] = L[i];
        if (fabs(Cross(q[last].v, q[last-1].v)) < eps) { // 两向量平行且同向，取内侧的一个
            --last;
            if (OnLeft(q[last], L[i].P)) q[last] = L[i];
        }
        if (first < last) p[last-1] = GetIntersection(q[last-1], q[last]);
    }
    while (first < last && !OnLeft(q[first], p[last-1])) --last; // 删除无用平面 (*)
    if (last - first <= 1) return 0; // 空集 (**)
    p[last] = GetIntersection(q[last], q[first]); // 计算首尾两个半平面的交点
    int m = 0; // 从deque 复制到输出中
    for (int i=first; i<=last; ++i) poly[m++] = p[i];
    return m;
}