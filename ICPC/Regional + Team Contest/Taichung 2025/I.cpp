#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template<class P>
vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

const double PI = acos(-1);

#define int long long 
void solve(){
    int n,R;cin >> n >> R;

    vector<P> poly(n);
    for(int i=0;i<n;i++) cin >> poly[i].x >> poly[i].y;
    poly=convexHull(poly);

    Point<double> O(0,0);
    double circle_area = PI*R*R;

    n=(int)poly.size();
    if(n<=2){
        cout << setprecision(10) << fixed << circle_area/2 << '\n';
        return;
    }
    double res = 0;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        Point<double> PA(poly[i].x,poly[i].y);
        Point<double> PB(poly[j].x,poly[j].y);
        vector<Point<double>> X=circleLine(O,R,PA,PB);
        assert((int)X.size()==2);
        Point<double> A=X[0],B=X[1];
        //cout << '*' << i << '\n';
        //cout << A.x << ' ' << A.y << ' ' << B.x << ' ' << B.y << '\n';
        
        double angle=A.angle()-B.angle();
        if(angle<0) angle=-angle;
        if(angle>PI) angle=2*PI-angle;
        double area = circle_area*(angle/(2*PI));

        vector<Point<double>> tri={O,A,B};
        area -= abs(polygonArea2(tri))/2;
        res=max(res,min(area,circle_area-area));

        int so = (A.cross(B,O)<0);
        Point<double> PC(poly[(i+2)%n].x,poly[(i+2)%n].y);
        int sx = (A.cross(B,PC)<0);
        //cout << poly[i].x << ' ' << poly[i].y << ' ' << poly[j].x << ' ' << poly[j].y << '\n';
        
        //cout << so << ' ' << sx << ' ' << angle << '\n';
        if(so!=sx){
            cout << setprecision(10) << fixed << circle_area/2 << '\n';
            return;
        }
    }
    cout << setprecision(10) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
