#include<bits/stdc++.h>
using namespace std;

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
		return out << "{" << p.x << ", " << p.y << "}";
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
#define scalarapply(applyop, op) point &operator applyop(const T &c){ return *this = *this op c; }
	scalarapply(+=, +) scalarapply(-=, -) scalarapply(*=, *) scalarapply(/=, /)
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
// Returns the angle of p->O->q
// [-pi, pi]
template<class T>
double angle(const point<T> &p, const point<T> &q){
	return atan2(p ^ q, p * q);
}
// Returns the angle of p->O->q
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
template<class T>
struct compare_by_angle{
	point<T> origin;
	compare_by_angle(const point<T> &origin = point<T>()): origin(origin){ }
	int side(const point<T> &p) const{
		return p < origin ? -1 : p == origin ? 0 : 1;
	}
	bool operator()(const point<T> &p, const point<T> &q) const{
		int sp = side(p), sq = side(q);
		if(sp != sq) return sp < sq;
		return doubled_signed_area(origin, p, q) > 0;
	}
};
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
// T must be able to hold the fourth power of max coordinate
// returns [a, b, c, and d lies in a circle]
template<class T>
bool concircular(point<T> a, point<T> b, point<T> c, const point<T> &d){
		a -= d, b -= d, c -= d;
	return a.squared_norm() * (b ^ c) + b.squared_norm() * (c ^ a) + c.squared_norm() * (a ^ b) == 0;
}
// T must be able to hold the fourth power of max coordinate
// returns [d lies in the interior of the circle defined by a, b, c]
template<class T>
bool inside_of_circle(point<T> a, point<T> b, point<T> c, const point<T> &d){
		a -= d, b -= d, c -= d;
	return (a.squared_norm() * (b ^ c) + b.squared_norm() * (c ^ a) + c.squared_norm() * (a ^ b)) * (doubled_signed_area(a, b, c) > 0 ? 1 : -1) > 0;
}
// T must be able to hold the fourth power of max coordinate
// returns [d lies in the exterior of the circle defined by a, b, c]
template<class T>
bool outside_of_circle(point<T> a, point<T> b, point<T> c, const point<T> &d){
		a -= d, b -= d, c -= d;
	return (a.squared_norm() * (b ^ c) + b.squared_norm() * (c ^ a) + c.squared_norm() * (a ^ b)) * (doubled_signed_area(a, b, c) > 0 ? -1 : 1) > 0;
}

using pointint = point<int>;
using pointll = point<long long>;
using pointlll = point<__int128_t>;
using pointd = point<double>;
using pointld = point<long double>;

template<class T, class F1 = decltype(squared_distance<T>), class F2 = decltype(::sqrt)>
pair<T, pair<int, int>> find_a_closest_pair(const vector<point<T>> &a, F1 distance_powered = squared_distance, F2 get_distance = sqrt){
	int n = (int)a.size();
	assert(n >= 2);
	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	sort(order.begin(), order.end(), [&](int i, int j){ return a[i].y < a[j].y; });
	for(auto t = 1; t < n; ++ t) if(a[order[t - 1]] == a[order[t]]) return {0, {order[t - 1], order[t]}};
	pair<T, pair<int, int>> res{numeric_limits<T>::max() / 2, {}};
	map<point<T>, int> s;
	int t = 0;
	for(auto i: order){
		T d = 1 + get_distance(res.first);
		while(a[order[t]].y <= a[i].y - d) s.erase(a[order[t]]), ++ t;
		auto low = s.lower_bound({a[i].x - d, a[i].y});
		auto high = s.upper_bound({a[i].x + d, a[i].y});
		for(; low != high; ++ low) res = min(res, pair<T, pair<int, int>>{distance_powered(low->first, a[i]), pair<int, int>{low->second, i}});
		s.insert({a[i], i});
	}
	return res;
}
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}



void solve(){
    int N;cin >> N;
    vector<pointld> P(N);

    int X=290797,M=50515093;
    for(int i=0;i<2*N;i++){
        if(i&1) P[i/2].x=X;
        else P[i/2].y=X;
        X=X*X%M;
    }
    
    cout << setprecision(18) << fixed << sqrtl(find_a_closest_pair(P).first) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
