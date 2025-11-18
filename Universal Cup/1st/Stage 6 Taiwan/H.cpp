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
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

template<class T> int sgn(T x)  {
	return (x > 0) - (x < 0);
}

template<class T>
struct Point {
	typedef Point P;

	T x, y;
	Point() {}
	explicit Point(T x, T y) : x(x), y(y) {}

	bool operator < (P p) const {
		return tie(x, y) < tie(p.x, p.y);
	}

	P operator + (P p) const {
		return P(x + p.x, y + p.y);
	}

	P operator - (P p) const {
		return P(x - p.x, y - p.y);
	}

	P operator * (T scale) const {
		return P(x * scale, y * scale);
	}

	P operator / (T scale) const {
		return P(x / scale, y / scale);
	}

	T dot(P p) const {
		return x * p.x + y * p.y;
	}

	T cross(P p) const {
		return x * p.y - y * p.x;
	}

	T cross(P a, P b) const {
		return (a - *this).cross(b - *this);
	}
	T dist2() const {
		return x * x + y * y;
	}
	double dist() const {
		return sqrt((double)dist2());
	}
	double angle() const { // [-pi, pi]
		return atan2(y, x);
	}
	P unit() const {
		return *this / dist();
	}
	P perp() const { // rot +90deg 
		return P(-y, x);
	}
	P normal() const {
		return perp().unit();
	}
	P rotate(double a) {
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	friend ostream& operator << (ostream &os, P p) {
		return os << "(" << p.x << ", " << p.y << ")";
	}
};

#define int long long
#define double long double

typedef Point<double> P;

P ccCenter(const P& A, const P& B, const P& C) {
	P b = C - A, c = B - A;
	return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}

const double inf = 1e18;

const int N = 2005, mod = (1ll << 31) - 1;

int n, k, v;

double R[N][N];

P a[N];

double dp[N][N];
vector<int> update[N];

void Hollwo_Pelw(){
	cin >> n >> k >> v;
	for (int i = 1; i <= n; i++) {
		a[i].x = v; v = (v * 233811181 + 1) % mod;
		a[i].y = v; v = (v * 233811181 + 1) % mod;
	}

	for (int l = 1; l <= n; l++) {
		P o = a[l];
		double rad = 0, EPS = 1e-8;

		update[l].push_back(l);
		
		for (int r = l; r <= n; r++) {

			if ((o - a[r]).dist() > rad + EPS) {
				o = a[r];
				rad = 0;
				for (int i = l; i < r; i++) if ((o - a[i]).dist() > rad + EPS) {
					o = (a[r] + a[i]) / 2;
					rad = (o - a[i]).dist();
					for (int j = l; j < i; j++) if ((o - a[j]).dist() > rad + EPS) {
						o = ccCenter(a[i], a[j], a[r]);
						rad = (o - a[i]).dist();
					}
				}
				update[l].push_back(r - 1);
			}
			// update[l].push_back(r);

			R[l][r] = rad;
		}

		if (update[l].back() != n)
			update[l].push_back(n);
	}


	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = inf;
		}
	}

	for (int j = 0; j <= k; j++)
		dp[n][j] = 0;
	for (int i = n; i >= 1; i--) {
		for (int x : update[i]) {
			for (int j = 0; j < k; j++) {
				dp[i - 1][j + 1] = min(dp[i - 1][j + 1], dp[x][j] + R[i][x]);
			}
		}
	}

	cout << fixed << setprecision(10) << dp[0][k] << '\n';
}