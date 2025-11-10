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

const int N = 2e6 + 5;

int n, pre[N], suf[N], cnt[N][3];
string s;

inline int o(char c) {
	if (c == 'C') return 0;
	if (c == 'W') return 1;
	if (c == 'P') return 2;
	return 3;
}

int val[3];

/*

aXbXbXaX X X

z <= x + y, z >= y >= x > 0

*/


inline bool check_with_ends(int l, int r) {
	vector<int> id = {0, 1, 2};
	sort(id.begin(), id.end(), [&](const int &i, const int &j){
		return val[i] < val[j];
	});

	if (val[id[2]] > val[id[0]] + val[id[1]] + 1) {
		return 0;
	}

	if (val[id[2]] == val[id[0]] + val[id[1]] + 1) {

		// only possible is id[2], id[2]
		if (l == id[2] || r == id[2]) {
			return 0;
		} else {
			return 1;
		}
	}

	if (val[id[2]] == val[id[0]] + val[id[1]]) {

		// possible has form id[2], x
		for (int i = 0; i < 2; i++) if (val[id[i]] > 0) {

			// id[i] can be one of endp

			if (l != id[i] && r != id[2]) return 1;
			if (l != id[2] && r != id[i]) return 1;
		}

		return 0;
	}

	return 1;
}

inline bool check(int l, int r) {
	if (l > r) return 0;
	for (int i = 0; i < 3; i++)
		val[i] = cnt[r][i] - cnt[l - 1][i];
	return pre[l - 1] == 0 && suf[r + 1] == 0 && check_with_ends(o(s[l - 1]), o(s[r + 1]));
}

void Hollwo_Pelw(){
	cin >> n >> s;
	s = '$' + s + '$';

	pre[0] = suf[n + 1] = 0;

	for (int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1] + (s[i] == s[i - 1]);
	}
	for (int i = n; i >= 1; i--) {
		suf[i] = suf[i + 1] + (s[i] == s[i + 1]);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++)
			cnt[i][j] = cnt[i - 1][j] + (o(s[i]) == j);
	}

	if (pre[n] == 0) {
		cout << "Beautiful\n";
		return ;
	}

	if (!check(1, n)) {
		cout << "Impossible\n";
		return ;
	}

	int resl = 1, resr = n;

	for (int l = 1, r = 1; l <= n; l++) {
		r = max(r, l);
		while (r <= n && !check(l, r)) r ++;
		if (r <= n && r - l < resr - resl) {
			resl = l, resr = r;
		}
	}

	cout << "Possible\n";
	cout << resl << ' ' << resr << '\n';

	for (int i = 0; i < 3; i++) {
				val[i] = cnt[resr][i] - cnt[resl - 1][i];
		}

	// resl=2,resr=n-1;

	int A=o(s[resl-1]),B=o(s[resr+1]);
	vector<int> id = {0, 1, 2};
	sort(id.begin(), id.end(), [&](const int &i, const int &j){
		return val[i] < val[j];
	});
		//cout << val[id[0]] << ' ' << val[id[1]] << ' ' << val[id[2]] << '\n';

	vector<int> res;
	if(val[id[2]]<val[id[1]]+val[id[0]]){
		while(max({val[0],val[1],val[2]})>1){
			int i=(A+1)%3;
			if(val[i]<val[(i+1)%3]) i=(i+1)%3;
			res.push_back(i);
			val[i]--;A=i;
		}
		assert(val[0]==1 && val[1]==1 && val[2]==1);
		int i=0;
		if(i==A) i++;
		int j=0;
		while(j==B || j==i) j++;
		int k=i^j^3;
		res.push_back(i);
		res.push_back(k);
		res.push_back(j);
	}
	else if(val[id[2]]==val[id[0]]+val[id[1]]){
		if(!val[id[0]]){
			for(int i=0;i<val[id[2]];i++){
				res.push_back(id[2]);
				res.push_back(id[1]);
			}
			if(A == id[2] || B == id[1]){
				reverse(res.begin(),res.end());
			}
		}
		else{
			while(val[id[0]]>0 || val[id[1]]>0){
				res.push_back(id[2]);
				if(val[id[0]]>0) res.push_back(id[0]),val[id[0]]--;
				else res.push_back(id[1]),val[id[1]]--;
			}
			if(A==id[2]){
				if(A==id[1]) swap(res[1],res[(int)res.size()-1]);
				reverse(res.begin(),res.end());
			}
			else{
				if(B==id[1]) swap(res[1],res[(int)res.size()-1]);
			}
		}
	}
	else{
		while(val[id[0]]>0 || val[id[1]]>0){
			res.push_back(id[2]);
			if(val[id[0]]>0) res.push_back(id[0]),val[id[0]]--;
			else res.push_back(id[1]),val[id[1]]--;
		}
		res.push_back(id[2]);
	}
	for (int i = 0; i < 3; i++) {
		val[i] = cnt[resr][i] - cnt[resl - 1][i];
	}

	bool ok=true;
	if(res[0]==o(s[resl-1])) ok=false;
	if(res.back()==o(s[resr+1])) ok=false;
	for(int i=0;i<(int)res.size();i++){
		val[res[i]]--;
		if(i && res[i]==res[i-1]) ok=false;
	}
	assert(!val[0] && !val[1] && !val[2] && ok);

	for(int i=resl;i<=resr;i++){
		int j=res[i-resl];
		if(j==0) s[i]='C';
		else if(j==1) s[i]='W';
		else s[i]='P';
	}
	for(int i=1;i<=n;i++) cout << s[i];
	cout << '\n';
}