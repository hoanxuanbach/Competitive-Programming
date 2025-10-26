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

using ull = unsigned long long;
mt19937_64 rng(13052005);

const int N = 1e6 + 1;

map <ull, int> mpp;
ull a[N];

void init(){
	mpp[0] = 0;
	For(i, 1, N){
		a[i] = rng();
		mpp[a[i]] = i;
	}
	assert(isz(mpp) == N);
}

int answer(ull h){
	auto itr = mpp.find(h);
	if (itr != mpp.end()){
		return itr->second;
	}
	else{
		return -1;
	}
}

void Anya(){
	ull h = 0;
	int q; cin >> q; while (q--){
		int x; cin >> x;
		h ^= a[x];
		cout << answer(h) << endl;
	}
	cout << h << endl;
}

void Andrei(){
	ull h;
	cin >> h;
	int q; cin >> q; while (q--){
		int x; cin >> x;
		h ^= a[x];
		cout << answer(h) << endl;
	}
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	// freopen("KEK.inp", "r", stdin);
	// freopen("KEK.out", "w", stdout);
	init();

	string subtask; cin >> subtask;
	if (subtask == "start"){
		Anya();
	}
	else{
		Andrei();
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