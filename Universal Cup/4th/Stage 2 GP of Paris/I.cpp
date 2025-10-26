#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

signed main(){
#ifndef hollwo_pelw_local
	if (fopen(".inp", "r"))
		assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
	using namespace chrono;
	auto start = steady_clock::now();
#endif
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	int testcases = 1;
	cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

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
	bool parallel_to(const point &q) const{
		if constexpr(is_floating_point_v<T>) return abs(*this ^ q) <= 1e-9;
		else return abs(*this ^ q) == 0;
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

// Requires point
template<class T>
struct line{
	point<T> p{}, d{1, 0}; // p + d*t
	line(){ }
	template<class U>
	line(const line<U> &l): p(l.p), d(l.d){ }
	template<class U, class V>
	line(const point<U> &p, const point<V> &q, bool Two_Points = true): p(p), d(Two_Points ? q - p : q){ }
	line(const point<T> &d): p(), d(d){ }
	line(T a, T b, T c): p(abs(a) > T(1e-9) ? -c / a : 0, abs(a) <= T(1e-9) && abs(b) > T(1e-9) ? -c / b : 0), d(-b, a){ }
	friend istream &operator>>(istream &in, line<T> &l){
		in >> l.p >> l.d, l.d -= l.p;
		return in;
	}
	friend ostream &operator<<(ostream &out, const line<T> &l){
		return out << "{" << l.p << " -> " << l.q() << "}";
	}
	bool degenerate() const{
		if constexpr(is_floating_point_v<T>) return d.norm() <= 1e-9;
		else return d == point<T>();
	}
	point<T> q() const{
		return p + d;
	}
	line &flip(){
		p += d;
		d = -d;
		return *this;
	}
	line flipped() const{
		return line(*this).flip();
	}
	// d.y * (X - p.x) - d.x * (Y - p.y) = 0
	tuple<T, T, T> coef() const{
		return {d.y, -d.x, d.perp() * p};
	}
	bool parallel_to(const line<T> &L) const{
		return abs(d ^ L.d) <= 1e-9;
	}
	line<double> translate(T x) const{
		auto dir = d.perp();
		return {point<double>(p) + dir.unit() * x, d, false};
	}
	line<long double> translatel(T x) const{
		auto dir = d.perp();
		return {point<long double>(p) + dir.unit_l() * x, d, false};
	}
	bool on_left(const point<T> &r) const{
		return (r - p ^ d) < 0;
	}
	bool on_right(const point<T> &r) const{
		return (r - p ^ d) > 0;
	}
	bool on_line(const point<T> &r) const{
		return abs(r - p ^ d) <= 1e-9;
	}
	bool on_ray(const point<T> &r) const{
		return abs(r - p ^ d) <= 1e-9 && (r - p) * d >= 0;
	}
	bool on_segment(const point<T> &r) const{
		if(abs(r - p ^ d) > 1e-9) return false;
		auto x = (r - p) * d;
		return 0 <= x && x <= d.squared_norm();
	}
	bool on_open_segment(const point<T> &r) const{
		if(abs(r - p ^ d) > 1e-9) return false;
		auto x = (r - p) * d;
		return 0 < x && x < d.squared_norm();
	}
	double distance_to_line(const point<T> &r) const{
		return abs(r - p ^ d) / d.norm();
	}
	long double distance_to_line_l(const point<T> &r) const{
		return abs(r - p ^ d) / d.norm_l();
	}
	double distance_to_ray(const point<T> &r) const{
		return (r - p) * d <= 0 ? distance(p, r) : distance_to_line(r);
	}
	long double distance_to_ray_l(const point<T> &r) const{
		return (r - p) * d <= 0 ? distance_l(p, r) : distance_to_line_l(r);
	}
	double distance_to_segment(const point<T> &r) const{
		auto x = (r - p) * d;
		return x <= 0 ? distance(p, r) : x >= d.squared_norm() >= 0 ? distance(q(), r) : distance_to_line(r);
	}
	long double distance_to_segment_l(const point<T> &r) const{
		auto x = (r - p) * d;
		return x <= 0 ? distance_l(p, r) : x >= d.squared_norm() ? distance_l(q(), r) : distance_to_line_l(r);
	}
	point<double> projection(const point<T> &r) const{
		return point<double>(p) + (point<double>(r) - point<double>(p)) * d / d.squared_norm() * point<double>(d);
	}
	point<long double> projection_l(const point<T> &r) const{
		return point<long double>(p) + (point<long double>(r) - point<long double>(p)) * d / d.squared_norm() * point<long double>(d);
	}
	// T must be a field.
	point<T> projection_f(const point<T> &r) const{
		return point<T>(p) + (r - p) * d / d.squared_norm() * point<T>(d);
	}
	point<double> reflection(const point<T> &r) const{
		return 2.0 * projection(r) - point<double>(r);
	}
	point<long double> reflection_l(const point<T> &r) const{
		return 2.0l * projection_l(r) - point<long double>(r);
	}
	// T must be a field.
	point<T> reflection_f(const point<T> &r) const{
		return T{2} * projection_f(r) - point<T>(r);
	}
	point<double> closest_point_on_segment(const point<T> &r) const{
		auto x = (r - p) * d;
		return x <= 0 ? point<double>(p) : x >= d.squared_norm() ? point<double>(q()) : projection(r);
	}
	point<long double> closest_point_on_segment_l(const point<T> &r) const{
		auto x = (r - p) * d;
		return x <= 0 ? point<long double>(p) : x >= d.squared_norm() ? point<long double>(q()) : projection_l(r);
	}
	// T must be a field.
	point<T> closest_point_on_segment_f(const point<T> &r) const{
		auto x = (r - p) * d;
		return x <= 0 ? point<T>(p) : x >= d.squared_norm() ? point<T>(q()) : projection_f(r);
	}
};

using lineint = line<int>;
using linell = line<long long>;
using linelll = line<__int128_t>;
using lined = line<double>;
using lineld = line<long double>;

// endpoint type: 0(ray), 1(closed end), 2(open end)
// type_mask % 3 for the left endpoint type of L
// type_mask / 3 % 3 for the right endpoint type of L
// type_mask / 9 % 3 for the left endpoint type of R
// type_mask / 27 for the right endpoint type of R
// Requires point and line
#define CHECK(type, x, y) (type == 0 || x < y || x == y && type == 1)
// Assumes parallel lines do not intersect
template<class T>
optional<pointd> intersect_no_parallel_overlap(int type_mask, const line<T> &L, const line<T> &M){
	assert(0 <= type_mask && type_mask < 81);
	T s = L.d ^ M.d;
	if(s == 0) return {};
	T ls = M.p - L.p ^ M.d, rs = M.p - L.p ^ L.d;
	if(s < 0) s = -s, ls = -ls, rs = -rs;
	if(CHECK(type_mask % 3, 0, ls) && CHECK(type_mask / 3 % 3, ls, s) && CHECK(type_mask / 9 % 3, 0, rs) && CHECK(type_mask / 27, rs, s)) return pointd(L.p) + 1.0 * ls / s * pointd(L.d);
	else return {};
}
// Assumes parallel lines do not intersect
template<class T>
optional<pointld> intersect_no_parallel_overlapl(int type_mask, const line<T> &L, const line<T> &M){
	assert(0 <= type_mask && type_mask < 81);
	T s = L.d ^ M.d;
	if(s == 0) return {};
	T ls = M.p - L.p ^ M.d, rs = M.p - L.p ^ L.d;
	if(s < 0) s = -s, ls = -ls, rs = -rs;
	if(CHECK(type_mask % 3, 0, ls) && CHECK(type_mask / 3 % 3, ls, s) && CHECK(type_mask / 9 % 3, 0, rs) && CHECK(type_mask / 27, rs, s)) return pointld(L.p) + 1.0L * ls / s * pointld(L.d);
	else return {};
}
#undef CHECK
// Assumes parallel lines do not intersect
template<class T>
optional<pointd> intersect_closed_segments_no_parallel_overlap(const line<T> &L, const line<T> &M){
	return intersect_no_parallel_overlap<T>(1 + 3 * 1 + 9 * 1 + 27 * 1, L, M);
}
// Assumes parallel lines do not intersect
template<class T>
optional<pointld> intersect_closed_segments_no_parallel_overlapl(const line<T> &L, const line<T> &M){
	return intersect_no_parallel_overlapl<T>(1 + 3 * 1 + 9 * 1 + 27 * 1, L, M);
}
// Assumes parallel lines do not intersect
template<class T>
optional<pointd> intersect_open_segments_no_parallel_overlap(const line<T> &L, const line<T> &M){
	return intersect_no_parallel_overlap<T>(2 + 3 * 2 + 9 * 2 + 27 * 2, L, M);
}
// Assumes parallel lines do not intersect
template<class T>
optional<pointld> intersect_open_segments_no_parallel_overlapl(const line<T> &L, const line<T> &M){
	return intersect_no_parallel_overlapl<T>(2 + 3 * 2 + 9 * 2 + 27 * 2, L, M);
}
// Assumes nothing
template<class T>
optional<pair<pointd, pointd>> intersect_closed_segments(const line<T> &L, const line<T> &M){
	auto s = L.d ^ M.d, ls = M.p - L.p ^ M.d;
	if(!s){
		if(ls) return {};
		auto Lp = L.p, Lq = L.q(), Mp = M.p, Mq = M.q();
		if(Lp > Lq) swap(Lp, Lq);
		if(Mp > Mq) swap(Mp, Mq);
		point<T> p = max(Lp, Mp), q = min(Lq, Mq);
		if(p <= q) return pair<pointd, pointd>{p, q};
		return {};
	}
	auto rs = M.p - L.p ^ L.d;
	if(s < 0) s = -s, ls = -ls, rs = -rs;
	if(0 <= ls && ls <= s && 0 <= rs && rs <= s){
		auto p = pointd(L.p) + 1.0 * ls / s * pointd(L.d);
		return pair<pointd, pointd>{p, p};
	}
	else return {};
}
// Assumes nothing
template<class T>
optional<pair<pointld, pointld>> intersect_closed_segmentsl(const line<T> &L, const line<T> &M){
	auto s = L.d ^ M.d, ls = M.p - L.p ^ M.d;
	if(!s){
		if(ls) return {};
		auto Lp = L.p, Lq = L.q(), Mp = M.p, Mq = M.q();
		if(Lp > Lq) swap(Lp, Lq);
		if(Mp > Mq) swap(Mp, Mq);
		point<T> p = max(Lp, Mp), q = min(Lq, Mq);
		if(p <= q) return pair<pointld, pointld>{p, q};
		return {};
	}
	auto rs = M.p - L.p ^ L.d;
	if(s < 0) s = -s, ls = -ls, rs = -rs;
	if(0 <= ls && ls <= s && 0 <= rs && rs <= s){
		auto p = pointld(L.p) + 1.0L * ls / s * pointld(L.d);
		return pair<pointld, pointld>{p, p};
	}
	else return {};
}
// Assumes nothing
template<class T>
optional<pair<pointd, pointd>> intersect_open_segments(const line<T> &L, const line<T> &M){
	auto s = L.d ^ M.d, ls = M.p - L.p ^ M.d;
	if(!s){
		if(ls) return {};
		auto Lp = L.p, Lq = L.q(), Mp = M.p, Mq = M.q();
		if(Lp > Lq) swap(Lp, Lq);
		if(Mp > Mq) swap(Mp, Mq);
		point<T> p = max(Lp, Mp), q = min(Lq, Mq);
		if(p < q) return pair<pointd, pointd>{p, q};
		return {};
	}
	auto rs = (M.p - L.p) ^ L.d;
	if(s < 0) s = -s, ls = -ls, rs = -rs;
	if(0 < ls && ls < s && 0 < rs && rs < s){
		auto p = pointd(L.p) + 1.0 * ls / s * pointd(L.d);
		return pair<pointd, pointd>{p, p};
	}
	else return {};
}
// Assumes nothing
template<class T>
optional<pair<pointld, pointld>> intersect_open_segmentsl(const line<T> &L, const line<T> &M){
	auto s = L.d ^ M.d, ls = M.p - L.p ^ M.d;
	if(!s){
		if(ls) return {};
		auto Lp = L.p, Lq = L.q(), Mp = M.p, Mq = M.q();
		if(Lp > Lq) swap(Lp, Lq);
		if(Mp > Mq) swap(Mp, Mq);
		point<T> p = max(Lp, Mp), q = min(Lq, Mq);
		if(p < q) return pair<pointld, pointld>{p, q};
		return {};
	}
	auto rs = (M.p - L.p) ^ L.d;
	if(s < 0) s = -s, ls = -ls, rs = -rs;
	if(0 < ls && ls < s && 0 < rs && rs < s){
		auto p = pointld(L.p) + 1.0L * ls / s * pointld(L.d);
		return pair<pointld, pointld>{p, p};
	}
	else return {};
}

void Hollwo_Pelw(){
	cout << fixed << setprecision(15);

	int n;
	cin >> n;
	
	vector<pointld> a(n);

	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[i] = {x, y};
	}

	vector<pointld> lines;

	lines.push_back(a[0]);
	lines.push_back(a[1]);


	// for (int j = 0; j < n; j++) {
	// 	cout << a[j].x << ' ' << a[j].y << " A" << 0 << j << '\n';
	// }

	for (int i = 1; i < n - 1; i++) {
		// lines = a[i], a[i + 1]

		auto l = lineld(a[i], a[i + 1]);

		for (auto &p : a) {
			p = l.reflection_l(p);
		}

		lines.push_back(a[i + 1]);

		// for (int j = 0; j < n; j++) {
		// 	cout << a[j].x << ' ' << a[j].y << " A" << i << j << '\n';
		// }
	}
	lines.push_back(a[0]);


	auto ans = lineld(lines[0], lines.back());
	// lines[0] -> lines[n]

	for  (int i = 1; i < n - 1; i++) {
		// ans interssect vs segment(lines[i], lines[i + 1]);

		auto p = intersect_open_segmentsl(ans, lineld(lines[i], lines[i + 1]));

		if (!p) {
			cout << "NO\n";
			return ;
		}

		auto p1 = (*p).first;

		long double dx = (p1 - lines[i]).x;
		long double lx = (lines[i + 1] - lines[i]).x;

		long double alpha = dx / lx;

		if (abs(alpha) < 1e-5 || abs(alpha) + 1e-5 > 1) {
			cout << "NO\n";
			return ;
		}
	}

	cout << "YES\n";
	

	long double res = ans.d.angle_l() / (2 * acosl(-1)) * 360;

	if (res > 180 + 1e-15) {
		res -= 360;
	}

	cout << res << '\n';
}