#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fi first
#define se second
#define For(i, l, r) for (auto i = (l); i < (r); i++)
#define ForE(i, l, r) for (auto i = (l); i <= (r); i++)
#define FordE(i, l, r) for (auto i = (l); i >= (r); i--)
#define Fora(v, a) for (auto v: (a))
#define bend(a) (a).begin(), (a).end()
#define isz(a) ((signed)(a).size())

using ll = long long;
using ld = long double;
using pii = pair <int, int>;
using vi = vector <int>;
using vpii = vector <pii>;
using vvi = vector <vi>;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rngll(chrono::high_resolution_clock::now().time_since_epoch().count());
using randint_t = uniform_int_distribution<int>;
using randll_t = uniform_int_distribution<long long>;
using randd_t = uniform_real_distribution<double>;
// return x with probability p, y with probability 1-p
template<class T>
T pick(T x, T y, double p = 0.5){
	assert(-0.0001 <= p && p <= 1.0001);
	return randd_t(0, 1)(rng) <= p ? x : y;
}
array<int, 2> get_range(int n, bool allow_empty_range = false){
	if(allow_empty_range){
		int l = rng() % (n + 1), r = rng() % (n + 1);
		if(l > r) swap(l, r);
		return {l, r};
	}
	else{
		int l = rng() % n, r = rng() % n;
		if(l > r) swap(l, r);
		return {l, r + 1};
	}
}

vector <int> partition(int n, int k){
	vector <int> ans(k, n / k);
	For(i, 0, n % k){
		ans[i]++;
	}
	return ans;
}

void Alisa(){
	string s; cin >> s;
	int m = isz(s);
	int n; cin >> n;
	vector <int> a(n);
	For(i, 0, n){
#ifdef LOCAL
		a[i] = randint_t(0, 999'999'999)(rng);
#else
		cin >> a[i];
#endif
	}

	auto b = partition(n, m);
	b.insert(b.begin(), 0);
	partial_sum(b.begin(), b.end(), b.begin());

	vector <int> c(m);
	For(i, 0, m){
		c[i] = s[i] - 'a';
	}
	For(i, 1, m){
		if (c[i] == c[i - 1]){
			c[i] = 26;
		}
	}

	vector <int> ans;
	For(i, 0, m){
		For(j, b[i], b[i + 1]){
			if (a[j] % 27 == c[i]){
				ans.emplace_back(a[j]);
			}
		}
	}
	cout << isz(ans) << endl;
	for (auto x: ans){
		cout << x << ' ';
	}
	cout << endl;
}

void Eva(){
	int k; cin >> k;
	vector <int> ans(k);
	For(i, 0, k){
		cin >> ans[i];
	}
	vector <int> c;
	c.emplace_back(ans[0] % 27);
	For(i, 1, k){
		if (ans[i] % 27 != ans[i - 1] % 27){
			c.emplace_back(ans[i] % 27);
		}
	}
	For(i, 1, isz(c)){
		if (c[i] == 26){
			c[i] = c[i - 1];
		}
	}
	string s;
	For(i, 0, isz(c)){
		s += char(c[i] + 'a');
	}
	cout << s << endl;
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	// freopen("KEK.inp", "r", stdin);
	// freopen("KEK.out", "w", stdout);
	string subtask; cin >> subtask;
	if (subtask == "Alisa"){
		Alisa();
	}
	else{
		Eva();
	}
}

/*
==================================================+
INPUT                                             |
--------------------------------------------------|

--------------------------------------------------|
==================================================+
OUTPUT                                            |
--------------------------------------------------|

--------------------------------------------------|
==================================================+
*/