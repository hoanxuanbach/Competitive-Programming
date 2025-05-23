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

void solve() {
    i64 l, r;
    cin >> l >> r;

    l <<= 1, r <<= 1; ++r;
    vector<int> pr(2e6), pr2(r - l);
    for (i64 i = 2; i < isz(pr); ++i) if (not pr[i]) {
        for (i64 j = i * i; j < isz(pr); j += i) pr[j] = true;
        for (i64 j = max(i * 2ll, (l + i - 1) / i * i); j < r; j += i) {
            pr2[j - l] = true;
        }
    }

    vector<int> nxt(r - l, -1);
    for (int i = r - l - 1; i >= 0; --i) {
        nxt[i] = i + 1 < r - l ? nxt[i + 1] : -1;
        if (not pr2[i]) nxt[i] = i;
    }

    vector<int> prv(r - l, -1);
    for (int i = 0; i < r - l; ++i) {
        prv[i] = i - 1 >= 0 ? prv[i - 1] : -1;
        if (not pr2[i]) prv[i] = i;
    }

    auto gl = [&](i64 cl, i64 cr) -> array<i64, 2> {
        --cr;
        i64 mid = (cl + cr) / 2;
        mid = prv[mid - l];
        if (mid == -1 or mid + l <= cl) {
            return {-1, -1};
        }
        return {mid + l, cr + 1};
    };

    auto gr = [&](i64 cl, i64 cr) -> array<i64, 2> {
        --cr;
        i64 mid = (cl + cr + 1) / 2;
        mid = nxt[mid - l];
        if (mid == -1 or mid + l >= cr) {
            return {-1, -1};
        }
        return {cl, mid + l + 1};
    };

    modular res = 0;
    vector<map<i64, int>> mp(r - l + 1); mp[r - l][l] = 1;
    for (int i = r - l; i >= 0; --i) if (not mp[i].empty()) {
        modular cur = 0;
        for (auto [cl, val] : mp[i]) {
            auto cr = cl + i;

            auto nl = gl(cl, cr);
            // cout << cl << " " << cr << " -> " << nl[0] << " " << nl[1] << endl;
            if (nl[0] != -1) {
                mp[nl[1] - nl[0]][nl[0]] += val;
            }
            auto nr = gr(cl, cr);
            if (nr[0] != -1) {
                mp[nr[1] - nr[0]][nr[0]] += val;
            }

            cur += val;
        }
        res = cur;
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
    int t = 1; cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
