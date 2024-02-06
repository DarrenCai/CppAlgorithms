#include <cmath>

#define eps 1e-10
struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    void Normalize() {
        double l = sqrt(x*x + y*y + z*z); x /= l; y /= l; z /= l;
    }
};
typedef Point3 Vector3;

Vector3 operator+ (const Vector3& A, const Vector3& B) {
    return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}

Vector3 operator- (const Vector3& A, const Vector3& B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}

Vector3 operator* (const Vector3& A, double p) {
    return Vector3(A.x * p, A.y * p, A.z * p);
}

Vector3 operator/ (const Vector3& A, double p) {
    return Vector3(A.x / p, A.y / p, A.z / p);
}

double Length(const Vector3& A) {
    return sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
}

int dcmp(double x) {
    return abs(x) < eps ? 0 : (x < 0. ? -1 : 1);
}

bool operator== (const Point3& a, const Point3& b) {
    return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0 && dcmp(a.z - b.z) == 0;
}

double Dot(const Vector3& A, const Vector3& B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Vector3 Cross(const Vector3& A, const Vector3& B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

double Angle(const Vector3& A, const Vector3& B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}

double Area2(const Point3& A, const Point3& B, const Point3& C) {
    return Length(Cross(B - A, C - A));
}

Point3 GetLineIntersection(const Point3& P, const Vector3& v, const Point3& Q, const Vector3& w) {
    // 假定两直线共面且相交
    Vector3 u = P - Q;
    return P + v * (Length(Cross(w, u)) / Length(Cross(v, w)));
}

Point3 GetLineProjection(const Point3& P, const Point3& A, const Point3& B) {
    Vector3 v = B-A;
    return A + v * (Dot(v, P-A) / Dot(v, v));
}

bool SegmentProperIntersect(const Point3& a1, const Point3& a2, const Point3& b1, const Point3& b2) {
    // 假定两直线共面
    Vector3 c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    Vector3 c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(Dot(c1, c2)) < 0 && dcmp(Dot(c3, c4)) < 0;
}

bool OnSegment(const Point3& p, const Point3& a1, const Point3& a2) { // 不含端点
    return dcmp(Length(Cross(a1 - p, a2 - p))) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

bool OnSegment2(const Point3& p, const Point3& a1, const Point3& a2) { // 含端点
    return dcmp(Length(Cross(a1 - p, a2 - p))) == 0 && dcmp(Dot(a1 - p, a2 - p)) <= 0;
}

double DistanceToLine(const Point3& P, const Point3& A, const Point3& B) {
    Vector3 v1 = B - A, v2 = P - A;
    return Length(Cross(v1, v2)) / Length(v1);
}

double DistanceToSegment(const Point3& P, const Point3& A, const Point3& B) {
    if (A == B) return Length(P-A);
    Vector3 v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    return Length(Cross(v1, v2)) / Length(v1);
}

// 点p 到平面p0-n 的距离。n必须为单位向量
double DistanceToPlane(const Point3& p, const Point3& p0, const Vector3& n) {
    return fabs(Dot(p-p0, n)); // 如果不取绝对值，得到的是有向距离
}
// 点p 在平面p0-n 上的投影。n 必须为单位向量
Point3 GetPlaneProjection(const Point3& p, const Point3& p0, const Vector3& n) {
    return p-n*Dot(p-p0, n);
}

// 直线p1-p2 到平面p0-n 的交点。假定交点唯一存在
Point3 LinePlaneIntersection(Point3 p1, Point3 p2, Point3 p0, Vector3 n) {
    Vector3 v = p2-p1;
    double t = (Dot(n, p0-p1) / Dot(n,p2-p1)); /*** 判断分母是否为0 !!! ***/
    return p1 + v*t; //如果是线段，判断t 是不是在0 和1 之间
}

//点P 在△P0P1P2 中
bool PointInTri(const Point3& p, const Point3& p0, const Point3& p1, const Point3& p2) {
    double s = Length(Cross(p-p0, p1-p0)) + Length(Cross(p-p0, p2-p0)) + Length(Cross(p-p1, p2-p1));
    return dcmp(s - Length(Cross(p1-p0, p2-p0))) == 0;
}

//△P0P1P2 是否和线段AB相交
bool TriSegIntersection(const Point3& P0, const Point3& P1, const Point3& P2, const Point3& A, const Point3& B, Point3& P) {
    Vector3 n = Cross(P1-P0, P2-P0);
    if (dcmp(Dot(n, B-A)) == 0) return false; //线段AB 和平面P0P1P2 平行或共面
    else { //平面A 和直线P1-P2 有唯一交点
        double t = Dot(n, P0-A) / Dot(n, B-A);
        if (dcmp(t) < 0 || dcmp(t-1) > 0) return false; //交点不在线段AB 上
        P = A + (B-A)*t; //计算交点
        return PointInTri(P, P0, P1, P2); //判断交点是否在三角形P0-P1-P2 内
    }
}

struct Face{
    int v[3];
    Vector3 normal(Point3 *P) const {
        return Cross(P[v[1]]-P[v[0]], P[v[2]]-P[v[0]]);
    }
    bool visible(Point3* P, int i) const {
        return Dot(P[i]-P[v[0]], normal(P)) > 0;
    }
};

double rand01() { return rand() / (double)RAND_MAX; } // 0-1 的随机数
double randeps() { return (rand01() - 0.5) * eps; } // -eps/2 到 eps/2 的随机数
Point3 add_noise(Point3 p) { // 添加微小扰动
    return Point3(p.x + randeps(), p.y + randeps(), p.z + randeps());
}

// 增量法求三维凸包。
// 没有考虑各种特殊情况（如4点共面）。实践中，在调用前对输入点输入点应先去重再进行微小扰动
// Face ch[N], next[N]; bool vis[N][N];
int ConvexHull(Point3* P, int n, Face* ch) {
    // 由于已经进行扰动，前3个点不共线
    ch[0] = (Face){0, 1, 2}; ch[0] = (Face){2, 1, 0};
    int m = 2; 
    for (int i=3, t; i<n; ++i, m=t) {
        // 计算每条边“左面”的可见性
        for(int j=t=0; j<m; ++j) {
            const Face& f = ch[j];
            bool res = f.visible(P, i);
            if (!res) next[t++] = f;
            for (int k=0; k<3; k++) vis[f.v[k]][f.v[(k+1)%3]] = res;
        }
        for (int j=0; j<m; ++j) for (int k=0; k<3; ++k) {
            int a = ch[j].v[k], b = ch[j].v[(k+1)%3];
            if (!vis[b][a] && vis[a][b]) // (a,b)是分界线，左边对P[i]可见
                next[t++] = (Face){a, b, i};
        }
        for (int j=0; j<t; ++j) ch[j] = next[j];
    }
    return m;
}