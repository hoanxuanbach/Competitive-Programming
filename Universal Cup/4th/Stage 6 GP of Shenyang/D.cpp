#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define CNT(mask) __builtin_popcount(mask)

using namespace std;
void solve();

const string DIGITS[10] = {
    "1110111", // 0
    "0010010", // 1
    "1011101", // 2
    "1011011", // 3
    "0111010", // 4
    "1101011", // 5
    "1101111", // 6
    "1010010", // 7
    "1111111", // 8
    "1111011"  // 9
};

const string EMPTY = "0000000";
#define int long long
const long long INF = LLONG_MAX;

struct Data {
    bool blank;
	bool zero;
    int digit;
};

struct Position {
    int r1, c1, r2, c2;
};

Position positions[7] = {
    {0, 1, 0, 2}, // 0: top horizontal
    {1, 0, 2, 0}, // 1: upper-left
    {1, 3, 2, 3}, // 2: upper-right
    {3, 1, 3, 2}, // 3: middle
    {4, 0, 5, 0}, // 4: lower-left
    {4, 3, 5, 3}, // 5: lower-right
    {6, 1, 6, 2}  // 6: bottom
};

long long C[64][64];

inline long long safeAdd(long long a, long long b) {
    if (a >= INF - b) return INF;
    return a + b;
}

inline long long safeMul(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    if (a > INF / b) return INF;
    return a * b;
}

void init() {
    for (int n = 0; n < 64; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            C[n][k] = safeAdd(C[n-1][k-1], C[n-1][k]);
        }
    }
}

long long dp[10][64][2], cnt[10][64][2];
bool valid[10][(1<<7)];
Data d[10][(1<<7)];
int n, k;
/*
long long calc(int pos, int cost, bool isBlank, bool canZero) {
	if (pos == n) {
		return 1;
	}
	if (dp[pos][cost][isBlank][canZero] != -1) {
		return dp[pos][cost][isBlank][canZero];
	}
	dp[pos][cost][isBlank][canZero] = 0;

	for (int mask = 0; mask < (1<<7); ++mask) {
		if (!valid[pos][mask]) continue;
		if (CNT(mask) + cost > k) continue;
		auto [ok, zero, digit] = d[pos][mask];
		
		long long sum = 0;
		if (ok && isBlank) {
			auto tmp = calc(pos + 1, cost + CNT(mask), true, canZero);
			sum = safeAdd(sum, tmp);
		}

		if (zero && canZero) {
			auto tmp = calc(pos + 1, cost + CNT(mask), isBlank, true);
			sum = safeAdd(sum, tmp);
		}

		if (digit > 0) {
			auto tmp = calc(pos + 1, cost + CNT(mask), false, true);
			sum = safeAdd(sum, safeMul(digit, tmp));
		}

		if (dp[pos][cost][isBlank][canZero] < sum) {
			dp[pos][cost][isBlank][canZero] = sum;
		}
	}
	return dp[pos][cost][isBlank][canZero];
}
*/
bool print=true;
vector<string> grid(7);
void solve() {
    cin >> n >> k;
    for (int r = 0; r < 7; ++r) cin >> grid[r];
	for (int i = 0; i < n; ++i) {
		for (int mask = 0; mask < (1<<7); ++mask) {
			valid[i][mask] = false;
		}
	}

    vector<array<char,7>> initState(n);
    int totalW = 0;
    for (int pos = 0; pos < n; ++pos) {
        int baseC = pos * 5;
        for (int s = 0; s < 7; ++s) {
            auto &sp = positions[s];
            char a = grid[sp.r1][baseC + sp.c1];
            char ch = a;
            initState[pos][s] = ch;
            if (ch == 'W') totalW++;
        }
    }

    for (int pos = 0; pos < n; ++pos) {
        auto &st = initState[pos];
        vector<int> f;
        for (int s = 0; s < 7; ++s) f.push_back(s);

        int m = (int)f.size();
        for (int mask = 0; mask < (1<<m); ++mask) {
            int cost = __builtin_popcount(mask);
            bool repaired[7] = {0};
            for (int bit = 0; bit < m; ++bit)
                if (mask & (1<<bit))
                    repaired[f[bit]] = true;

            auto ok_pat = [&](const string &pat)->bool {
                for (int s = 0; s < 7; ++s) {
                    char init = st[s];
                    if (init == 'W' || repaired[s]) continue;
                    int stuck = (init == '1' ? 1 : 0);
                    int t = pat[s] - '0';
                    if (stuck != t) return false;
                }
                return true;
            };

            int cnt = 0;
			bool zero = false;
			bool ok = ok_pat(EMPTY);
            for (int d = 0; d < 10; ++d) {
                if (ok_pat(DIGITS[d])) {
                    if (d == 0) zero = true;
					else ++cnt;
                }
            }
            d[pos][mask] = {ok, zero, cnt};
			valid[pos][mask] = true;
        }
    }
	

	memset(dp, -1, sizeof(dp));
	memset(cnt, -1, sizeof(cnt));

    dp[0][0][1]=0;
    cnt[0][0][1]=1;

    vector<vector<vector<int>>> F(n,vector<vector<int>>(k+1,vector<int>(2,0)));
    F[0][0][1]=1;
    for(int i=0;i+1<n;i++) for(int cost=0;cost<=k;cost++) for(int t=0;t<=1;t++){
        for(int mask=0;mask<(1<<7);mask++){
            if (!valid[i][mask]) continue;
            int ncost=cost+CNT(mask);
            if (ncost>k) continue;
            auto [ok, zero, digit] = d[i][mask];
            int nt=(t && ok);
            F[i+1][ncost][nt]+=F[i][cost][t];
        }
    }
    
    for(int i=0;i<n;i++) for(int cost=0;cost<=k;cost++) for(int t=0;t<=1;t++){
        if(dp[i][cost][t]==-1) continue;
        for(int mask=0;mask<(1<<7);mask++){
            if (!valid[i][mask]) continue;
            int ncost=cost+CNT(mask);
            if (ncost > k) continue;
            auto [ok, zero, digit] = d[i][mask];
            int nval=dp[i][cost][t]*(digit+(int)zero)+digit*t,ncnt=cnt[i][cost][t];
            if(!(digit+(int)zero)) ncnt=F[i][cost][t];
            if(i==n-1) nval+=(zero && t);
            int nt=(t && ok);
            if(nval>dp[i+1][ncost][nt]) dp[i+1][ncost][nt]=nval,cnt[i+1][ncost][nt]=ncnt;
            else if(nval==dp[i+1][ncost][nt]) cnt[i+1][ncost][nt]+=ncnt;
        }
    }

    int ans=-1,ways=-1;
    for(int i=0;i<=k;i++) for(int j=0;j<=1;j++){
        if(dp[n][i][j]>ans) ans=dp[n][i][j],ways=cnt[n][i][j];
        else if(dp[n][i][j]==ans) ways+=cnt[n][i][j];
    }
    if(print) cout << ans << ' ' << ways << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    cin.tie(0), cout.tie(0)->sync_with_stdio(0);
    init();
    int testcases = 1;
    cin >> testcases;
    for (int test = 1; test <= testcases; test++) {
        solve();
        /*
        if(test==1) if(n==2 && k==7) print=false;
        if(!print && test==37){
            cout << n << ' ' << k << '\n';
            for(int i=0;i<7;i++) cout << grid[i] << '\n';
        }
        */
    }
}
