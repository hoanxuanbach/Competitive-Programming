/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define pb push_back
#define ff first
#define ss second
#define isz(x) (int)x.size()
using namespace std;

const int mxN = 2e5 + 5;
const int mod = 998244353;
const i64 oo = 1e18;

template<size_t S>
struct basis_Z2{
    int count = 0;
    vector<bitset<S>> data;
    vector<int> pivot;
    struct modifier_type{
        int type;
        // 0: row[to] ^= row[from]
        // 2: insert row[from] into row[to]
        int from, to;
    };
    vector<modifier_type> log;
    basis_Z2(const vector<bitset<S>> &a = {}){
        for(auto &v: a) insert(v);
    }
    int rank() const{
        return (int)data.size();
    }
    // O(rank * width / w)
    bitset<S> reduce(bitset<S> v) const{
        for(auto i = 0; i < rank(); ++ i) if(v[pivot[i]]) v ^= data[i];
        return v;
    }
    // Insert a row while maintaining the lower triangular form
    // O(rank * width / w)
    bool insert(bitset<S> v){
        for(auto i = 0; i < rank(); ++ i) if(v[pivot[i]]){
            v ^= data[i];
            log.push_back({0, i, count});
        }
        if(v.none()) return ++ count, false;
        int p = S - 1;
        while(!v[p]) -- p;
        for(auto i = 0; i < rank(); ++ i) if(data[i][p]){
            data[i] ^= v;
            log.push_back({0, count, i});
        }
        int t = lower_bound(pivot.begin(), pivot.end(), p) - pivot.begin();
        pivot.insert(pivot.begin() + t, p);
        data.insert(data.begin() + t, v);
        log.push_back({2, count, t});
        return ++ count, true;
    }
    // Returns {
    //  lexicographically_smallest_sol,
    //  sol_basis_vector_1,
    //  ...,
    //  sol_basis_vector_k
    // }
    // O(rank * width / w)
    template<bool construct_solution = true>
    optional<vector<bitset<S>>> solve(vector<int> b) const{
        assert(count == (int)b.size());
        for(auto &m: log){
            if(m.type == 0) b[m.to] ^= b[m.from];
            else rotate(b.begin() + m.to, b.begin() + m.from, b.begin() + m.from + 1);
        }
        for(auto i = rank(); i < count; ++ i) if(b[i]) return {};
        vector<bitset<S>> res(1);
        bitset<S> is_free;
        is_free.set();
        for(auto i = 0; i < rank(); ++ i){
            if(b[i]) res[0].set(pivot[i]);
            is_free.reset(pivot[i]);
        }
        if(!construct_solution) return res;
        for(auto j = 0; j < S; ++ j) if(is_free[j]){
            bitset<S> v;
            v.set(j);
            for(auto i = rank() - 1; i >= 0 && pivot[i] > j; -- i){
                bitset<S> temp;
                temp.set(pivot[i]);
                v |= data[i] & temp;
            }
            res.push_back(v);
        }
        return res;
    }
};

int binpow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = 1ll * res * x % mod;
        x = 1ll * x * x % mod; y >>= 1;
    }
    return res;
}

int n, a[mxN];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    basis_Z2<30> xbs;
    for (int i = 2; i <= n; ++i) {
        a[i] ^= a[1];
        xbs.insert(bitset<30>(a[i]));
    }
    int cnt = xbs.rank();
    cout << binpow(2, cnt * (n - cnt) + cnt * (cnt - 1) / 2) << endl;
}

signed main() {

#ifndef CDuongg
    if(fopen(taskname".inp", "r"))
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
   cout << "Check array size pls sir" << endl;
#endif

}
