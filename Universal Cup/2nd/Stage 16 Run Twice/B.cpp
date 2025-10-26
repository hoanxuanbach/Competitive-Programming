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

int n, k;
vector <int> a;

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	// freopen("KEK.inp", "r", stdin);
	// freopen("KEK.out", "w", stdout);
int tests; cin >> tests; while (tests--){
	cin >> n >> k;
	a.resize(k);
	For(i, 0, k){
		cin >> a[i];
	}

	if (isz(a) >= 1 and a.back() == n){
		a.pop_back();
	}
	else{
		a.emplace_back(n);
	}
	k = isz(a);
	cout << n << ' ' << k << endl;
	For(i, 0, k){
		cout << a[i] << ' ';
	}
	cout << endl;
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