// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

template<class T>
struct point{
	T x{}, y{};
	point(){ }
	template<class U> point(const point<U> &otr): x(otr.x), y(otr.y){ }
	template<class U, class V> point(U x, V y): x(x), y(y){ }
	template<class U> point(const array<U, 2> &p): x(p[0]), y(p[1]){ }
	friend istream &operator>>(istream &in, point &p){
		return in >> p.x >> p.y;
	}
	friend ostream &operator<<(ostream &out, const point &p){
		return out << p.x << " " << p.y;
	}
	template<class U> operator array<U, 2>() const{
		return {x, y};
	}
	T operator*(const point &otr) const{
		return x * otr.x + y * otr.y;
	}
	T operator^(const point &otr) const{
		return x * otr.y - y * otr.x;
	}
	point operator+(const point &otr) const{
		return {x + otr.x, y + otr.y};
	}
	point &operator+=(const point &otr){
		return *this = *this + otr;
	}
	point operator-(const point &otr) const{
		return {x - otr.x, y - otr.y};
	}
	point &operator-=(const point &otr){
		return *this = *this - otr;
	}
	point operator-() const{
		return {-x, -y};
	}
#define scalarop_l(op) friend point operator op(const T &c, const point &p){ return {c op p.x, c op p.y}; }
	scalarop_l(+) scalarop_l(-) scalarop_l(*) scalarop_l(/)
#define scalarop_r(op) point operator op(const T &c) const{ return {x op c, y op c}; }
	scalarop_r(+) scalarop_r(-) scalarop_r(*) scalarop_r(/)
#define scalarapply(op) point &operator op(const T &c){ return *this = *this op c; }
	scalarapply(+=) scalarapply(-=) scalarapply(*=) scalarapply(/=)
#define compareop(op) bool operator op(const point &otr) const{ return pair<T, T>(x, y) op pair<T, T>(otr.x, otr.y); }
	compareop(>) compareop(<) compareop(>=) compareop(<=) compareop(==) compareop(!=)
#undef scalarop_l
#undef scalarop_r
#undef scalarapply
#undef compareop
	double norm() const{
		return sqrt(x * x + y * y);
	}
	long double norm_l() const{
		return sqrtl(x * x + y * y);
	}
	T squared_norm() const{
		return x * x + y * y;
	}
	// [0, 2 * pi]
	double angle() const{
		auto a = atan2(y, x);
		if(a < 0) a += 2 * acos(-1);
		return a;
	}
	// [0, 2 * pi]
	long double angle_l() const{
		auto a = atan2(y, x);
		if(a < 0) a += 2 * acosl(-1);
		return a;
	}
	point<double> unit() const{
		return point<double>(x, y) / norm();
	}
	point<long double> unit_l() const{
		return point<long double>(x, y) / norm_l();
	}
	point perp() const{
		return {-y, x};
	}
	point<double> normal() const{
		return perp().unit();
	}
	point<long double> normal_l() const{
		return perp().unit_l();
	}
	point<double> rotate(double theta) const{
		return {x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta)};
	}
	point<long double> rotate_l(double theta) const{
		return {x * cosl(theta) - y * sinl(theta), x * sinl(theta) + y * cosl(theta)};
	}
	point reflect_x() const{
		return {x, -y};
	}
	point reflect_y() const{
		return {-x, y};
	}
	point reflect(const point &o = {}) const{
		return {2 * o.x - x, 2 * o.y - y};
	}
	/*
	bool parallel_to(const point &q) const{
		if constexpr(is_floating_point_v<T>) return abs(*this ^ q) <= 1e-9;
		else return abs(*this ^ q) == 0;
	}
	*/
};
template<class T, class U>
point<double> lerp(const point<T> &p, const point<U> &q, double t){
	return point<double>(p) * (1 - t) + point<double>(q) * t;
}
template<class T, class U>
point<long double> lerp_l(const point<T> &p, const point<U> &q, long double t){
	return point<long double>(p) * (1 - t) + point<long double>(q) * t;
}
template<class T>
double distance(const point<T> &p, const point<T> &q){
	return (p - q).norm();
}
template<class T>
long double distance_l(const point<T> &p, const point<T> &q){
	return (p - q).norm_l();
}
template<class T>
T squared_distance(const point<T> &p, const point<T> &q){
	return (p - q).squared_norm();
}
template<class T>
T doubled_signed_area(const point<T> &p, const point<T> &q, const point<T> &r){
	return q - p ^ r - p;
}
template<class T>
T doubled_signed_area(const vector<point<T>> &a){
	if(a.empty()) return 0;
	T res = a.back() ^ a.front();
	for(auto i = 1; i < (int)a.size(); ++ i) res += a[i - 1] ^ a[i];
	return res;
}
// [-pi, pi]
template<class T>
double angle(const point<T> &p, const point<T> &q){
	return atan2(p ^ q, p * q);
}
// [-pi, pi]
template<class T>
long double angle_l(const point<T> &p, const point<T> &q){
	return atan2l(p ^ q, p * q);
}
// Check if p->q->r is sorted by angle with respect to the origin
template<class T>
bool is_sorted_by_angle(const point<T> &origin, const point<T> &p, const point<T> &q, const point<T> &r){
	T x = p - origin ^ q - origin;
	T y = q - origin ^ r - origin;
	if(x >= 0 && y >= 0) return true;
	if(x < 0 && y < 0) return false;
	return (p - origin ^ r - origin) < 0;
}
// Check if a is sorted by angle with respect to the origin
template<class T>
bool is_sorted_by_angle(const point<T> &origin, const vector<point<T>> &a){
	for(auto i = 0; i < (int)a.size() - 2; ++ i) if(!is_sorted_by_angle(origin, a[i], a[i + 1], a[i + 2])) return false;
	return true;
}
template<class T>
bool counterclockwise(const point<T> &p, const point<T> &q, const point<T> &r){
	return doubled_signed_area(p, q, r) > 0;
}
template<class T>
bool clockwise(const point<T> &p, const point<T> &q, const point<T> &r){
	return doubled_signed_area(p, q, r) < 0;
}
template<class T>
bool colinear(const point<T> &p, const point<T> &q, const point<T> &r){
	return doubled_signed_area(p, q, r) == 0;
}
template<class T>
bool colinear(const vector<point<T>> &a){
	int i = 1;
	while(i < (int)a.size() && a[0] == a[i]) ++ i;
	if(i == (int)a.size()) return true;
	for(auto j = i + 1; j < (int)a.size(); ++ j) if(!colinear(a[0], a[i], a[j])) return false;
	return true;
}
point<double> polar(double x, double theta){
	assert(x >= 0);
	return {x * cos(theta), x * sin(theta)};
}
point<long double> polar_l(long double x, long double theta){
	assert(x >= 0);
	return {x * cosl(theta), x * sinl(theta)};
}

using pointint = point<int>;
using pointll = point<long long>;
using pointlll = point<__int128_t>;
using pointd = point<double>;
using pointld = point<long double>;

#define T double
#define POINTS const point<T> &p, const point<T> &q, const point<T> &r
point<T> weighted_mean(POINTS, T a = 0.5, T b = 0.5, T c = 0.5){
	return (a * p + b * q + c * r) / (a + b + c);
}
point<T> circumcenter(POINTS){
	point<T> a = r - p, b = q - p;
	return p + (a * b.squared_norm() - b * a.squared_norm()).perp() / (2 * a ^ b);
}
T circumradius(POINTS){
	return (p - q).norm() * (q - r).norm() * (r - p).norm() / (2 * doubled_signed_area(p, q, r));
}
point<T> incenter(POINTS){
	return weighted_mean(p, q, r, (p - q).norm(), (q - r).norm(), (r - p).norm());
}
T inradius(POINTS){
	return doubled_signed_area(p, q, r) / ((p - q).norm() + (q - r).norm() + (r - p).norm());
}
point<T> orthocenter(POINTS){
	return weighted_mean(p, q, r, (q - p ^ r - p) / ((q - p) * (r - p)), (r - q ^ p - q) / ((r - q) * (p - q)), (p - r ^ q - r) / ((p - r) * (q - r)));
}
template<int i> point<T> excenter(POINTS){
	return weighted_mean(p, q, r, (i == 0 ? -1 : 1) * (p - q).norm(), (i == 1 ? -1 : 1) * (q - r).norm(), (i == 2 ? -1 : 1) * (r - p).norm());
}
template<int i> T exradius(POINTS){
	return doubled_signed_area(p, q, r) / ((i == 0 ? -1 : 1) * (p - q).norm() + (i == 1 ? -1 : 1) * (q - r).norm() + (i == 2 ? -1 : 1) * (r - p).norm());
}
#undef POINTS
#undef T

template<class T>
pair<point<T>, double> minimum_enclosing_circle(vector<point<T>> a){
	int n = (int)a.size();
	shuffle(a.begin(), a.end(), mt19937(1564));
	point<T> o = a[0];
	double r = 0, EPS = 1 + 1e-8;
	for(auto i = 0; i < n; ++ i) if((o - a[i]).norm() > r * EPS){
		o = a[i], r = 0;
		for(auto j = 0; j < i; ++ j) if((o - a[j]).norm() > r * EPS){
			o = (a[i] + a[j]) / 2, r = (o - a[i]).norm();
			for(auto k = 0; k < j; ++ k) if((o - a[k]).norm() > r * EPS){
				o = circumcenter(a[i], a[j], a[k]), r = (o - a[i]).norm();
			}
		}
	}
	return {o, r};
}


void solve(){
    int n;cin >> n;
    vector<pointld> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    int m;cin >> m;
    vector<pointld> p;
    for(int i=0;i<m;i++){
        pointld c;cin >> c;
        for(int j=0;j<n;j++) p.push_back(c-a[j]);
    }
    auto res = minimum_enclosing_circle(p);
    cout << setprecision(10) << fixed << res.se << ' ' << res.fi << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

