#include <bits/stdc++.h>
using namespace std;

struct Vec {
    double x, y, z;
    Vec(double x=0, double y=0, double z=0): x(x), y(y), z(z) {}
};

Vec operator+(const Vec& a, const Vec& b) { return Vec(a.x+b.x, a.y+b.y, a.z+b.z); }
Vec operator-(const Vec& a, const Vec& b) { return Vec(a.x-b.x, a.y-b.y, a.z-b.z); }
Vec operator*(const Vec& a, double k) { return Vec(a.x*k, a.y*k, a.z*k); }

double dot(const Vec& a, const Vec& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec cross(const Vec& a, const Vec& b) {
    return Vec(a.y*b.z - a.z*b.y,
               a.z*b.x - a.x*b.z,
               a.x*b.y - a.y*b.x);
}

double norm(const Vec& a) {
    return sqrt(dot(a,a));
}

Vec normalize(const Vec& a) {
    double n = norm(a);
    return Vec(a.x/n, a.y/n, a.z/n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    cout << fixed << setprecision(10);

    while (T--) {
        double R;
        cin >> R;

        int a,b,c,u,v,w,x,y,z;
        cin >> a >> b >> c;
        cin >> u >> v >> w;
        cin >> x >> y >> z;

        // normalize to unit vectors
        auto toUnit = [](int p, int q, int r) {
            double len = sqrt(1.0*p*p + 1.0*q*q + 1.0*r*r);
            return Vec(p/len, q/len, r/len);
        };

        Vec A = toUnit(a,b,c);  // your place
        Vec U = toUnit(u,v,w);  // departure
        Vec X = toUnit(x,y,z);  // destination

        // Great circle normal
        Vec N = cross(U, X);

        // Compute if perpendicular falls within arc
        double cond1 = dot(N, cross(U, A));
        double cond2 = dot(N, cross(A, X));

        double d;
        if (cond1 >= 0 && cond2 >= 0) {
            // projection falls inside arc
            d = R * asin(fabs(dot(A, N)) / norm(N));
        } else {
            // nearest endpoint
            double d1 = R * acos(max(-1.0, min(1.0, dot(A, U))));
            double d2 = R * acos(max(-1.0, min(1.0, dot(A, X))));
            d = min(d1, d2);
        }

        cout << d << "\n";
    }
}