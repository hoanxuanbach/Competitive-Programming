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
const double eps = 1e-7;
const i64 oo = 1e18;

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
    P scale(T val) const { return *this / dist() * val; }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<double> P;

int n;
double x;
P a[mxN];

void solve() {
    cin >> x >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].x >> a[i].y;

    int cidx1 = 2, cidx2 = -1;
    double cdis = 0.0;
    P cur1 = a[1], cur2;
    for (int i = 2; i <= n; ++i) {
        cdis += (a[i] - a[i - 1]).dist();
        if (cdis > x) {
            cdis -= (a[i] - a[i - 1]).dist();
            cidx2 = i, cur2 = (a[i] - a[i - 1]).scale(x - cdis) + a[i - 1];
            break;
        }
    }
    cout << fixed << setprecision(12);
    if (cidx2 == -1) {
        cout << (a[1] - a[n]).dist() << endl;
        return;
    }
    double res = oo;
    while (cidx2 <= n) {

        // cout << cidx1 << " " << cur1 << endl;
        // cout << cidx2 << " " << cur2 << endl;

        res = min(res, (cur1 - cur2).dist());
        double dis1 = (a[cidx1] - cur1).dist(), dis2 = (a[cidx2] - cur2).dist();
        double maxx = min(dis1, dis2);
        double l = 0, r = maxx;

        // cout << maxx << endl;

        auto get = [&](double val) {
            P point1 = (a[cidx1] - cur1).scale(val) + cur1;
            P point2 = (a[cidx2] - cur2).scale(val) + cur2;
            return (point1 - point2).dist();
        };

        while (r - l > eps) {
            double mid1 = l + (r - l) / 3;
            double mid2 = l + (r - l) / 3 * 2;
            if (get(mid1) > get(mid2)) l = mid1;
            else r = mid2;
        }
        res = min(res, get(l));
        res = min(res, get(r));

        if (abs(dis1 - dis2) <= eps) {
            ++cidx1, ++cidx2;
            cur1 = a[cidx1 - 1], cur2 = a[cidx2 - 1];
        }
        else if (dis1 < dis2) {
            ++cidx1, cur1 = a[cidx1 - 1];
            cur2 = (a[cidx2] - cur2).scale(dis1) + cur2;
        }
        else {
            ++cidx2, cur2 = a[cidx2 - 1];
            cur1 = (a[cidx1] - cur1).scale(dis2) + cur1;
        }
        // cout << endl;
    }
    cout << res << endl;
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
