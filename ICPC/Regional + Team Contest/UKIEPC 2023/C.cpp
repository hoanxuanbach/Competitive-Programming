/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define pb push_back
#define ff first
#define ss second
#define isz(x) (int)x.size()
using namespace std;

const int mxN = 2e5 + 5;
const int mod = 1e9 + 7;
const i64 oo = 1e18;

const double PI = acos(-1);

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << ", " << p.y << ")"; }
};

template<class T>
T polygonArea2(vector<Point<T>>& v) {
    T a = v.back().cross(v[0]);
    for (int i = 0; i < isz(v) - 1; ++i)
        a += v[i].cross(v[i + 1]);
    return a;
}

void chkmax(double &x, double y) {
    x = (x > y ? x : y);
}

typedef Point<double> P;

int n, p;
double a[105], dp[105][105][105];
P cope[105];

double calc(int i1, int i2, int i3) {
    vector<P> v = {cope[i1], cope[i2], cope[i3]};
    return abs(polygonArea2(v) / 2);
}

void solve() {
    cin >> n >> p;
    cope[0] = P(0, 1000);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cope[i] = cope[0].rotate((360 - a[i]) / 180 * PI);
    }
    double res = 0;
    for (int chosen = 2; chosen <= p; ++chosen) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (i != j) {
        double val = dp[i][j][chosen];
        if (chosen == p) {
            chkmax(res, val);
            continue;
        }
        if (i < j) {
            for (int mid = i + 1; mid < j; ++mid) {
                double nval = val + calc(i, j, mid);
                chkmax(dp[mid][j][chosen + 1], nval);
                chkmax(dp[i][mid][chosen + 1], nval);
            }
        }
        else {
            for (int md = i + 1; md < j + n; ++md) {
                int mid = (md > n ? md - n : md);
                double nval = val + calc(i, j, mid);
                chkmax(dp[mid][j][chosen + 1], nval);
                chkmax(dp[i][mid][chosen + 1], nval);
            }
        }
    }
    cout << fixed << setprecision(12) << res << endl;
}

signed main() {

#ifndef CDuongg
    if(fopen(taskname".inp", "r"))
        assert(freopen(taskname".inp", "r", stdin)), assert(freopen(taskname".out", "w", stdout));
#else
    freopen("bai3.inp", "r", stdin);
    freopen("bai3.out", "w", stdout);
    auto start = chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; //cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
