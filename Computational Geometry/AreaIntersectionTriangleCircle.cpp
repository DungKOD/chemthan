#include <bits/stdc++.h>
using namespace std;

#define double double
#define EPS 1e-9
const double PI = acos(-1);
struct PT {
    double x, y;
    PT() : x(0), y(0) {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT& p) : x(p.x), y(p.y) {}
    int operator < (const PT& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
    int operator == (const PT& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
    PT operator + (const PT& p) const {return PT(x + p.x, y + p.y);}
    PT operator - (const PT& p) const {return PT(x - p.x, y - p.y);}
    PT operator * (double c) const {return PT(x * c, y * c);}
    PT operator / (double c) const {return PT(x / c, y / c);}
};
double cross(PT p, PT q) {return p.x * q.y - p.y * q.x;}
double area(PT a, PT b, PT c) {return fabs(cross(a, b) + cross(b, c) + cross(c, a)) / 2;}
double area2(PT a, PT b, PT c) {return cross(a, b) + cross(b, c) + cross(c, a);}
double dot(PT p, PT q) {return p.x * q.x + p.y * q.y;}
double dist(PT p, PT q) {return sqrt(dot(p - q, p - q));}
double dist2(PT p, PT q) {return dot(p - q, p - q);}
PT RotateCCW90(PT p) {return PT(-p.y, p.x);}
PT RotateCW90(PT p) {return PT(p.y, -p.x);}
PT RotateCCW(PT p, double t) {return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));}
int sign(double x) {return x < -EPS ? -1 : x > EPS;}
int sign(double x, double y) {return sign(x - y);}
ostream& operator << (ostream& os, const PT& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

double sqr(double x) {return x * x;}
double AreaTC(PT ct, double r, PT p1, PT p2) {
    double a, b, c, x, y, s = cross(p1 - ct, p2 - ct) / 2;
    a = dist(ct, p2), b = dist(ct, p1), c = dist(p1, p2);
    if (a <= r && b <= r) {
        return s;
    }
    else if (a < r && b >= r) {
        x = (dot(p1 - p2, ct - p2) + sqrt(c * c * r * r - sqr(cross(p1 - p2, ct - p2)))) / c;
        return asin(s * (c - x) * 2 / c / b / r) * r * r / 2 + s * x / c;
    }
    else if (a >= r && b < r) {
        y = (dot(p2 - p1, ct - p1) + sqrt(c * c * r * r - sqr(cross(p2 - p1, ct - p1)))) / c;
        return asin(s * (c - y) * 2 / c / a / r) * r * r / 2 + s * y / c;
    }
    else {
        if (fabs(2 * s) >= r * c || dot(p2 - p1, ct - p1) <= 0 || dot(p1 - p2, ct - p2) <= 0) {
            if (dot(p1 - ct, p2 - ct) < 0) {
                if (cross(p1 - ct, p2 - ct) < 0) {
                    return (-PI - asin(s * 2 / a / b)) * r * r / 2;
                }
                else {
                    return (PI - asin(s * 2 / a / b)) * r * r / 2;
                }
            }
            else {
                return asin(s * 2 / a / b) * r * r / 2;
            }
        }
        else {
            x = (dot(p1 - p2, ct - p2) + sqrt(c * c * r * r - sqr(cross(p1 - p2, ct - p2)))) / c;
            y = (dot(p2 - p1, ct - p1) + sqrt(c * c * r * r - sqr(cross(p2 - p1, ct - p1)))) / c;
            return (asin(s * (1 - x / c) * 2 / r / b) + asin(s * (1 - y / c) * 2 / r / a)) * r * r / 2 + s * ((y + x) / c - 1);
        }
    }
}
double AreaTC(PT ct, double r, PT p1, PT p2, PT p3) {
    return AreaTC(ct, r, p1, p2) + AreaTC(ct, r, p2, p3) + AreaTC(ct, r, p3, p1);
}

int main() {
    return 0;
}
