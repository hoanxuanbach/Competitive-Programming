#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int mod = 1e9+7;

template <class T> class BIT {
  private:
	int size;
	vector<T> bit;
	vector<T> arr;

  public:
	BIT(int size) : size(size), bit(size + 1), arr(size) {}

	void set(int ind, T val) { add(ind, val - arr[ind]); }

	void add(int ind, T val) {
		arr[ind] += val;
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] += val; }
	}

	T pref_sum(int ind) {
		ind++;
		T total = 0;
		for (; ind > 0; ind -= ind & -ind) { total += bit[ind]; }
		return total;
	}
};

struct PrimeCounter {
	vector<int> primes;
	vector<int> mnprimes;
	ll ans;
	ll y;
	vector<pair<pair<ll, int>, char>> queries;

	ll count_primes(ll n) {
		/*
		 * this y is actually n / y
		 * also no logarithms, welcome to reality, this y is the best for
		 * n=10^12 or n=10^13
		 */
		y = std::pow(n, 0.64);
		if (n < 100) { y = n; }

		// linear sieve
		primes.clear();
		mnprimes.assign(y + 1, -1);
		ans = 0;
		for (int i = 2; i <= y; ++i) {
			if (mnprimes[i] == -1) {
				mnprimes[i] = primes.size();
				primes.push_back(i);
			}
			for (int k = 0; k < primes.size(); ++k) {
				int j = primes[k];
				if (i * j > y) { break; }
				mnprimes[i * j] = k;
				if (i % j == 0) { break; }
			}
		}
		if (n < 100) { return primes.size(); }
		ll s = n / y;

		for (int p : primes) {
			if (p > s) { break; }
			ans++;
		}
		// pi(n / y)
		int ssz = ans;

		// F with two pointers
		int ptr = primes.size() - 1;
		for (int i = ssz; i < primes.size(); ++i) {
			while (ptr >= i && (ll)primes[i] * primes[ptr] > n) { ptr--; }
			if (ptr < i) { break; }
			ans -= ptr - i + 1;
		}

		// phi, store all queries
		phi(n, ssz - 1);

		sort(queries.begin(), queries.end());
		int ind = 2;
		int sz = primes.size();

		// the order in fenwick will be reversed, because prefix sum in a
		// fenwick is just one query
		BIT<int> fw(sz);
		for (auto [na, sign] : queries) {
			auto [n, a] = na;
			while (ind <= n) { fw.add(sz - 1 - mnprimes[ind++], 1); }
			ans += (fw.pref_sum(sz - a - 2) + 1) * sign;
		}
		queries.clear();
		return ans - 1;
	}

	void phi(ll n, int a, int sign = 1) {
		if (n == 0) { return; }
		if (a == -1) {
			ans += n * sign;
			return;
		}
		if (n <= y) {
			queries.emplace_back(pair<int, int>{n, a}, sign);
			return;
		}
		phi(n, a - 1, sign);
		phi(n / primes[a], a - 1, -sign);
	}
}P;

int C[100000005];
#define int long long
void solve(){
    int N;cin >> N;
    
    int sub=0,sum=0;
    int S=sqrtl(N);
    
    int T=100000000;
    for(int i=2;i<T;i++){
        if(!C[i]){
            C[i]=1;
            for(int j=i*i;j<T;j+=i) C[j]=1;
        }
        else C[i]=0;
        C[i]+=C[i-1];
    }

    vector<int> cnt(S+1);
    for(int i=1;i<=S;i++){
        if(N/i>=T) cout << '*' << i << endl;
        if(N/i>=T) cnt[i]=P.count_primes(N/i);
        else cnt[i]=C[N/i];
    }
    for(int i=1;i<S;i++){
        int cc=(cnt[i]-cnt[i+1])%mod;
        //cout << N/i << ' ' << P.cnt[i] << '\n';
        sum=(sum+cc*i)%mod;
        sub=(sub+cc*i%mod*i)%mod;
    }

    S=N/S+1;
    vector<int> p(S);
    for(int i=2;i<S;i++) if(!p[i]){
        int x=i;
        while(x<=N){
            sum=(sum+N/x)%mod;
            sub=(sub+(__int128)(N/x)*(N/x)%mod)%mod;
            x*=i;
        }
        for(int j=i;j<S;j+=i) p[j]=1;
    }
    int res=2*((__int128)sum*N%mod-sub+mod)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
