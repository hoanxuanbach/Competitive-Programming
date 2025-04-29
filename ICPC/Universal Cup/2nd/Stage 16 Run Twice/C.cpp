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

const int N = 2e3 + 5, base = 293;

int hex_to_dec(char c){
	if (c <= '9'){
		return c - '0';
	}
	else{
		return 10 + c - 'A';
	}
}

char dec_to_hex(int x){
	if (x < 10){
		return char(x + '0');
	}
	else{
		return char(x - 10 + 'A');
	}
}

int input_byte(){
	char c;
	cin >> c;
	int ans = hex_to_dec(c);
	cin >> c;
	ans = (ans << 4) | hex_to_dec(c);
	return ans;
}

void output_byte(int x){
	cout << dec_to_hex(x >> 4);
	cout << dec_to_hex(x & 15);
}

int n, m;
int a[N][N];
int b[N][N];

void message(){
	cin >> n >> m;
	ForE(i, 1, n){
		ForE(j, 1, m){
			a[i][j] = input_byte();
		}
	}

	vector <int> msg;
	msg.emplace_back(n >> 8);
	msg.emplace_back(n & 255);
	msg.emplace_back(m >> 8);
	msg.emplace_back(m & 255);

	ForE(i, 1, n){
		ForE(j, 1, m){
			if ((i + j) % 10 == 0){
				msg.emplace_back(a[i][j]);
			}
		}
	}
	cout << isz(msg) << endl;
	For(i, 0, isz(msg)){
		output_byte(msg[i]);
		cout << ' ';
	}
	cout << endl;
}

void parts(){
	vector <int> msg;
	int k; cin >> k;
	msg.resize(k);
	For(i, 0, k){
		msg[i] = input_byte();
	}
	reverse(bend(msg));
	n = msg.back(); msg.pop_back();
	n = (n << 8) | msg.back(); msg.pop_back();
	m = msg.back(); msg.pop_back();
	m = (m << 8) | msg.back(); msg.pop_back();
	ForE(i, 1, n){
		ForE(j, 1, m){
			if ((i + j) % 10 == 0){
				a[i][j] = msg.back(); msg.pop_back();
			}
		}
	}

	map <ull, pair <int, int>> mpp;
	ForE(i, 1, n - 10 + 1){
		ForE(j, 1, m - 10 + 1){
			ull h = 0;
			For(x, i, i + 10){
				For(y, j, j + 10){
					h *= base;
					if ((x + y) % 10 == 0){
						h += a[x][y] + 1;
					}
				}
			}
			mpp[h] = pair{i, j};
		}
	}
	int q; cin >> q;
	while (q--){
		int h, w; cin >> h >> w;
		ForE(i, 1, h){
			ForE(j, 1, w){
				b[i][j] = input_byte();
			}
		}
		array <ull, 10> hsh;
		hsh.fill(0ull);
		ForE(i, 1, 10){
			ForE(j, 1, 10){
				For(r, 0, 10){
					hsh[r] *= base;
				}
				int r = (i + j) % 10;
				hsh[r] += b[i][j] + 1;
			}
		}
		For(r, 0, 10){
			auto itr = mpp.find(hsh[r]);
			if (itr != mpp.end()){
				cout << itr->second.fi << ' ' << itr->second.se << endl;
				break;
			}
		}
	}
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
#ifdef LOCAL
	freopen("KEK.inp", "r", stdin);
	freopen("KEK.out", "w", stdout);
#endif
	string subtask; cin >> subtask;
	if (subtask == "message"){
		message();
	}
	else{
		parts();
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