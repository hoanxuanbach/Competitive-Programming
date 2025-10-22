#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 998244353;

#define pii pair<int,int>
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 220;
const ll inf = 1e18;

template<class T> struct mod_int {
	static constexpr int mod() { return T::mod; }

	int v;
	mod_int(long long _v = 0) : v(norm(_v)) {}

	inline int norm(long long a) { return a < 0 ? a % mod() + mod() : a % mod(); }
	mod_int neg() const { return v == 0 ? 0 : mod() - v; }

	template <typename U> explicit operator U() const { return v; }
	mod_int operator - () const { return neg(); }
	mod_int operator + () const { return mod_int(*this); }
	mod_int& operator -- () { if (v == 0) v = mod(); -- v; return *this; }
	friend mod_int operator -- (mod_int& a, signed) { mod_int r = a; --a; return r; }
	mod_int& operator ++ () { ++ v; if (v == mod()) v = 0; return *this; }
	friend mod_int operator ++ (mod_int& a, signed) { mod_int r = a; ++a; return r; }
	
#define defop(type, op) \
	friend inline type operator op (type a, const type &b) { return a op##= b; } \
	type& operator op##= (const type &oth)

	defop(mod_int, +) { if ((v += oth.v) >= mod()) v -= mod(); return *this; }
	defop(mod_int, -) { if ((v -= oth.v) < 0) v += mod(); return *this; }
	defop(mod_int, *) { return *this = norm(1ll * v * oth.v); }
	defop(mod_int, /) { return *this *= oth.inv(); }

	inline mod_int pow(long long b) const {
		mod_int a = *this, r = 1;
		for (; b; b >>= 1, a *= a)
			if (b & 1) r *= a;
		return r;
	}
	inline mod_int inv() const { return pow(mod() - 2); }

#undef defop

#define compare(op) friend bool operator op \
(const mod_int& lhs, const mod_int& rhs) { return lhs.v op rhs.v; }
	compare(==) compare(!=) compare(<) compare(<=) compare(>) compare(>=)
#undef compare

	friend std::ostream& operator << (std::ostream& out, const mod_int& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& inp, mod_int& n) { long long x; inp >> x; n = mod_int(x); return inp; }
};

struct modular { static constexpr int mod = static_cast<int>(998244353); };

// struct modular { static int mod; }; int modular::mod = 1;

using Mint = mod_int<modular>;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

struct matrix{
    int n,m;
    Mint x[maxn][maxn];
    matrix(int n=-1,int m=-1):n(n),m(m){
        memset(x,0,sizeof(x));
    }
    friend matrix operator*(matrix a,matrix b){
        matrix c(a.n,b.m);
        for(int i=0;i<a.n;i++){
            for(int j=0;j<b.m;j++){
                for(int k=0;k<a.m;k++){
                    c.x[i][j]+=a.x[i][k]*b.x[k][j];
                }
            }
        }
        return c;
    }
};

void solve(){
    ll N,R,X,Y;cin >> N >> R >> X >> Y;
    int M;cin >> M;
    vector<ll> x(M),y(M);
    for(int i=0;i<M;i++) cin >> x[i] >> y[i];

    int P,K;cin >> P >> K;P--;

    int S=M*(K+1);

    matrix mov(S,S);
    for(int i=0;i<M;i++) for(int j=0;j<M;j++){
        if(((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))>R*R) continue;
        for(int k=0;k<=K;k++){
            int nk=k;
            if(j==P) nk=min(nk+1,K);
            mov.x[i*(K+1)+k][j*(K+1)+nk]++;
            //cout << "mov " << i << ' ' << k << ' ' << j << ' ' << nk << ' ' << mov.x[i*(K+1)+k][j*(K+1)+nk] << '\n';
        }
    }
    
    Mint res=0,total=0;
    bool ok=0;

    matrix cur(1,S);N--;
    for(int i=0;i<M;i++){
        if((X-x[i])*(X-x[i])+(Y-y[i])*(Y-y[i])>R*R) continue;
        ok=1;
        int k=min((int)(i==P),K);
        cur.x[0][i*(K+1)+k]++;
    }

    while(N){
        if(N&1) cur=cur*mov;
        mov=mov*mov;N>>=1;
    }

    for(int i=0;i<M;i++){
        for(int k=0;k<=K;k++) total+=cur.x[0][i*(K+1)+k];
        res+=cur.x[0][i*(K+1)+K];
    }

    if(!ok) {
    	if (K == 0) {
    		res=1;
    	} else {
    		res=0;
    	}
    	total=1;
    }
    cout << res << ' ' << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

/*
3 3 1 1
3
3 3
3 4
4 3
3 2

3 3 1 1
3
4 4
3 4
4 3
3 1

8 2 1 1
3
2 1
1 2
9 9
3 2
*/
