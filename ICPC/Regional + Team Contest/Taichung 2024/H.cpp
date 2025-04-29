/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define isz(x) (int)x.size()
using namespace std;

template<class data_t, data_t _mod>
struct modular_fixed_base{
#define IS_INTEGRAL(T) (is_integral_v<T> || is_same_v<T, __int128_t> || is_same_v<T, __uint128_t>)
#define IS_UNSIGNED(T) (is_unsigned_v<T> || is_same_v<T, __uint128_t>)
    static_assert(IS_UNSIGNED(data_t));
    static_assert(_mod >= 1);
    static constexpr bool VARIATE_MOD_FLAG = false;
    static constexpr data_t mod(){
        return _mod;
    }
    template<class T>
    static vector<modular_fixed_base> precalc_power(T base, int SZ){
        vector<modular_fixed_base> res(SZ + 1, 1);
        for(auto i = 1; i <= SZ; ++ i) res[i] = res[i - 1] * base;
        return res;
    }    
    static vector<modular_fixed_base> _INV;
    static void precalc_inverse(int SZ){
        if(_INV.empty()) _INV.assign(2, 1);
        for(auto x = _INV.size(); x <= SZ; ++ x) _INV.push_back(_mod / x * -_INV[_mod % x]);
    }
    // _mod must be a prime
    static modular_fixed_base _primitive_root;
    static modular_fixed_base primitive_root(){
        if(_primitive_root) return _primitive_root;
        if(_mod == 2) return _primitive_root = 1;
        if(_mod == 998244353) return _primitive_root = 3;
        data_t divs[20] = {};
        divs[0] = 2;
        int cnt = 1;
        data_t x = (_mod - 1) / 2;
        while(x % 2 == 0) x /= 2;
        for(auto i = 3; 1LL * i * i <= x; i += 2){
            if(x % i == 0){
                divs[cnt ++] = i;
                while(x % i == 0) x /= i;
            }
        }
        if(x > 1) divs[cnt ++] = x;
        for(auto g = 2; ; ++ g){
            bool ok = true;
            for(auto i = 0; i < cnt; ++ i){
                if(modular_fixed_base(g).power((_mod - 1) / divs[i]) == 1){
                    ok = false;
                    break;
                }
            }
            if(ok) return _primitive_root = g;
        }
    }
    constexpr modular_fixed_base(){ }
    modular_fixed_base(const double &x){ data = _normalize(llround(x)); }
    modular_fixed_base(const long double &x){ data = _normalize(llround(x)); }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr> modular_fixed_base(const T &x){ data = _normalize(x); }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr> static data_t _normalize(const T &x){
        int sign = x >= 0 ? 1 : -1;
        data_t v =  _mod <= sign * x ? sign * x % _mod : sign * x;
        if(sign == -1 && v) v = _mod - v;
        return v;
    }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr> operator T() const{ return data; }
    modular_fixed_base &operator+=(const modular_fixed_base &otr){ if((data += otr.data) >= _mod) data -= _mod; return *this; }
    modular_fixed_base &operator-=(const modular_fixed_base &otr){ if((data += _mod - otr.data) >= _mod) data -= _mod; return *this; }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr> modular_fixed_base &operator+=(const T &otr){ return *this += modular_fixed_base(otr); }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr> modular_fixed_base &operator-=(const T &otr){ return *this -= modular_fixed_base(otr); }
    modular_fixed_base &operator++(){ return *this += 1; }
    modular_fixed_base &operator--(){ return *this += _mod - 1; }
    modular_fixed_base operator++(int){ modular_fixed_base result(*this); *this += 1; return result; }
    modular_fixed_base operator--(int){ modular_fixed_base result(*this); *this += _mod - 1; return result; }
    modular_fixed_base operator-() const{ return modular_fixed_base(_mod - data); }
    modular_fixed_base &operator*=(const modular_fixed_base &rhs){
        if constexpr(is_same_v<data_t, unsigned int>) data = (unsigned long long)data * rhs.data % _mod;
        else if constexpr(is_same_v<data_t, unsigned long long>){
            long long res = data * rhs.data - _mod * (unsigned long long)(1.L / _mod * data * rhs.data);
            data = res + _mod * (res < 0) - _mod * (res >= (long long)_mod);
        }
        else data = _normalize(data * rhs.data);
        return *this;
    }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr>
    modular_fixed_base &inplace_power(T e){
        if(e == 0) return *this = 1;
        if(data == 0) return *this = {};
        if(data == 1 || e == 1) return *this;
        if(data == mod() - 1) return e % 2 ? *this : *this = -*this;
        if(e < 0) *this = 1 / *this, e = -e;
        if(e == 1) return *this;
        modular_fixed_base res = 1;
        for(; e; *this *= *this, e >>= 1) if(e & 1) res *= *this;
        return *this = res;
    }
    template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr>
    modular_fixed_base power(T e) const{
        return modular_fixed_base(*this).inplace_power(e);
    }
    modular_fixed_base &operator/=(const modular_fixed_base &otr){
        make_signed_t<data_t> a = otr.data, m = _mod, u = 0, v = 1;
        if(a < _INV.size()) return *this *= _INV[a];
        while(a){
            make_signed_t<data_t> t = m / a;
            m -= t * a; swap(a, m);
            u -= t * v; swap(u, v);
        }
        assert(m == 1);
        return *this *= u;
    }
#define ARITHMETIC_OP(op, apply_op)\
modular_fixed_base operator op(const modular_fixed_base &x) const{ return modular_fixed_base(*this) apply_op x; }\
template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr>\
modular_fixed_base operator op(const T &x) const{ return modular_fixed_base(*this) apply_op modular_fixed_base(x); }\
template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr>\
friend modular_fixed_base operator op(const T &x, const modular_fixed_base &y){ return modular_fixed_base(x) apply_op y; }
    ARITHMETIC_OP(+, +=) ARITHMETIC_OP(-, -=) ARITHMETIC_OP(*, *=) ARITHMETIC_OP(/, /=)
#undef ARITHMETIC_OP
#define COMPARE_OP(op)\
bool operator op(const modular_fixed_base &x) const{ return data op x.data; }\
template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr>\
bool operator op(const T &x) const{ return data op modular_fixed_base(x).data; }\
template<class T, typename enable_if<IS_INTEGRAL(T)>::type* = nullptr>\
friend bool operator op(const T &x, const modular_fixed_base &y){ return modular_fixed_base(x).data op y.data; }
    COMPARE_OP(==) COMPARE_OP(!=) COMPARE_OP(<) COMPARE_OP(<=) COMPARE_OP(>) COMPARE_OP(>=)
#undef COMPARE_OP
    friend istream &operator>>(istream &in, modular_fixed_base &number){
        long long x;
        in >> x;
        number.data = modular_fixed_base::_normalize(x);
        return in;
    }
//#define _SHOW_FRACTION
    friend ostream &operator<<(ostream &out, const modular_fixed_base &number){
        out << number.data;
    #if defined(LOCAL) && defined(_SHOW_FRACTION)
        cerr << "(";
        for(auto d = 1; ; ++ d){
            if((number * d).data <= 1000000){
                cerr << (number * d).data;
                if(d != 1) cerr << "/" << d;
                break;
            }
            else if((-number * d).data <= 1000000){
                cerr << "-" << (-number * d).data;
                if(d != 1) cerr << "/" << d;
                break;
            }
        }
        cerr << ")";
    #endif
        return out;
    }
    data_t data = 0;
#undef _SHOW_FRACTION
#undef IS_INTEGRAL
#undef IS_UNSIGNED
};
template<class data_t, data_t _mod> vector<modular_fixed_base<data_t, _mod>> modular_fixed_base<data_t, _mod>::_INV;
template<class data_t, data_t _mod> modular_fixed_base<data_t, _mod> modular_fixed_base<data_t, _mod>::_primitive_root;

const unsigned int mod = (119 << 23) + 1; // 998244353
// const unsigned int mod = 1e9 + 7; // 1000000007
// const unsigned int mod = 1e9 + 9; // 1000000009
// const unsigned long long mod = (unsigned long long)1e18 + 9;
using modular = modular_fixed_base<decay_t<decltype(mod)>, mod>;

template<class T>
struct combinatorics{
#ifdef LOCAL
    #define ASSERT(c) assert(c)
#else
    #define ASSERT(c) 42
#endif
    // O(n)
    static vector<T> precalc_fact(int n){
        vector<T> f(n + 1, 1);
        for(auto i = 1; i <= n; ++ i) f[i] = f[i - 1] * i;
        return f;
    }
    // O(n * m)
    static vector<vector<T>> precalc_C(int n, int m){
        vector<vector<T>> c(n + 1, vector<T>(m + 1));
        for(auto i = 0; i <= n; ++ i) for(auto j = 0; j <= min(i, m); ++ j) c[i][j] = i && j ? c[i - 1][j - 1] + c[i - 1][j] : T(1);
        return c;
    }
    int SZ = 0;
    vector<T> inv, fact, invfact;
    combinatorics(){ }
    // O(SZ)
    combinatorics(int SZ): SZ(SZ), inv(SZ + 1, 1), fact(SZ + 1, 1), invfact(SZ + 1, 1){
        for(auto i = 1; i <= SZ; ++ i) fact[i] = fact[i - 1] * i;
        invfact[SZ] = 1 / fact[SZ];
        for(auto i = SZ - 1; i >= 0; -- i){
            invfact[i] = invfact[i + 1] * (i + 1);
            inv[i + 1] = invfact[i + 1] * fact[i];
        }
    }
    // O(1)
    T C(int n, int k) const{
        ASSERT(0 <= min(n, k) && max(n, k) <= SZ);
        return n >= k ? fact[n] * invfact[k] * invfact[n - k] : T{0};
    }
    // O(1)
    T P(int n, int k) const{
        ASSERT(0 <= min(n, k) && max(n, k) <= SZ);
        return n >= k ? fact[n] * invfact[n - k] : T{0};
    }
    // O(1)
    T H(int n, int k) const{
        ASSERT(0 <= min(n, k));
        if(n == 0) return 0;
        return C(n + k - 1, k);
    }
    // Multinomial Coefficient
    T mC(int n, const vector<int> &a) const{
        ASSERT((int)a.size() >= 2 && accumulate(a.begin(), a.end(), 0) == n);
        ASSERT(0 <= min(n, *min_element(a.begin(), a.end())) && max(n, *max_element(a.begin(), a.end())) <= SZ);
        T res = fact[n];
        for(auto x: a) res *= invfact[x];
        return res;
    }
    // Multinomial Coefficient
    template<class... U, typename enable_if<(is_integral_v<U> && ...)>::type* = nullptr>
    T mC(int n, U... pack){
        ASSERT(sizeof...(pack) >= 2 && (... + pack) == n);
        return (fact[n] * ... * invfact[pack]);
    }
    // O(min(k, n - k))
    T naive_C(long long n, long long k) const{
        ASSERT(0 <= min(n, k));
        if(n < k) return 0;
        T res = 1;
        k = min(k, n - k);
        ASSERT(k <= SZ);
        for(auto i = n; i > n - k; -- i) res *= i;
        return res * invfact[k];
    }
    // O(k)
    T naive_P(long long n, int k) const{
        ASSERT(0 <= min<long long>(n, k));
        if(n < k) return 0;
        T res = 1;
        for(auto i = n; i > n - k; -- i) res *= i;
        return res;
    }
    // O(k)
    T naive_H(long long n, int k) const{
        ASSERT(0 <= min<long long>(n, k));
        return naive_C(n + k - 1, k);
    }
    // O(1)
    bool parity_C(long long n, long long k) const{
        ASSERT(0 <= min(n, k));
        return n >= k ? (n & k) == k : false;
    }
    // Number of ways to place n '('s and k ')'s starting with m copies of '(' such that in each prefix, number of '(' is equal or greater than ')'
    // Catalan(n, n, 0): n-th catalan number
    // Catalan(s, s+k-1, k-1): sum of products of k catalan numbers where the index of product sums up to s.
    // O(1)
    T Catalan(int n, int k, int m = 0) const{
        ASSERT(0 <= min({n, k, m}));
        return k <= m ? C(n + k, k) : k <= n + m ? C(n + k, k) - C(n + k, k - m - 1) : T();
    }
#undef ASSERT
};

void solve() {
    int n, k;
    cin >> n >> k;
    --n;

    combinatorics<modular> combi(n + 1);

    modular pfx = 0, res = 1;
    vector<modular> dp(n + 1);
    dp[0] = 1, pfx += dp[0] - (k == 1 ? dp[0] : modular(0));
    for (int i = 1; i < n + 1; ++i) {
        dp[i] = pfx;
        pfx += dp[i];
        if (i + 1 >= k) pfx -= dp[i + 1 - k];
        res += dp[i] * combi.C(n, i) * 2;
    }
    cout << res << endl;
}

signed main() {

#ifndef CDuongg
    if (fopen(taskname".inp", "r"))
        assert(freopen(taskname".inp", "r", stdin)), assert(freopen(taskname".out", "w", stdout));
#else
    freopen("bai3.inp", "r", stdin);
    freopen("bai3.out", "w", stdout);
    auto start = chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; //cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
