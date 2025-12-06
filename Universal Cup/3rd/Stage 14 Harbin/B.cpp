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

#define sz(v) (int) (v.size())
#define all(v) v.begin(), v.end()

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
	double angle() const { return atan2(y, x); }
	
	P unit() const { return *this/dist(); } // makes d is t ()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));
	}
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; 
	}
};

#define ll long long

typedef Point<ll> P;

vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts))) for (P p : pts) {
		while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
		h[t++] = p;
	}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

ll area(vector<P> v) {
	ll a = v.back().cross(v[0]);
	for(int i = 0; i < sz(v) - 1; i++) a += v[i].cross(v[i+1]);
	return a;
}

ll area3(P p1, P p2, P p3) {
	return abs(area(vector<P>{p1, p2, p3}));
}


void Hollwo_Pelw(){
	int n;
	vector<P> pts;

	cin >> n;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		pts.push_back(P{x, y});
	}

	vector<P> outer = convexHull(pts);

	set<pair<int, int>> occ;
	for (P p : outer) {
		// cout << p.x << ' ' << p.y << '\n';
		occ.insert({p.x, p.y});
	}
	vector<P> leftover_pts;

	for (P p : pts) {
		if (!occ.count({p.x, p.y})) {
			leftover_pts.push_back(p);
		}
	}

	if (leftover_pts.empty()) {
		return cout << "-1\n", (void) 0;
	}

	ll best = 8e18;

	if (leftover_pts.size() <= 3) {

		for (P ip : leftover_pts) {
			for (int i = 0; i < sz(outer); i++) {

				best = min(best, area3(ip, outer[i], outer[(i + 1) % sz(outer)]));
			}
		}

		cout << area(outer) - best << '\n';
		return ;
	}

	vector<P> inner = convexHull(leftover_pts);

	for (int i = 0, j = 0; i < 2 * sz(outer); i++) {
		P p1 = outer[(i) % sz(outer)], p2 = outer[(i + 1) % sz(outer)];
		while (area3(inner[j], p1, p2) >= area3(inner[(j + 1) % sz(inner)], p1, p2)) {
			j = (j + 1) % sz(inner);
		}
		best = min(best, area3(inner[j], p1, p2));
	}

	cout << area(outer) - best << '\n';
	return ;
}