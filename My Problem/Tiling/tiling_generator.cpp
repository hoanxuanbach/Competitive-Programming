#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
 
const int MAX_T = 10000;
const int MAX_S = 10000;
const int MAX_N = 100;
const int MAX_A = 1e9;
 
template <class T>
pair<T, T> get_range(const string &name, T min_default, T max_default) {
    if (has_opt(name)) {
        auto res = opt<T>(name);
        return {res, res};
    }
    if (has_opt("min-" + name)) {
        min_default = opt<T>("min-" + name);
    }
    if (has_opt("max-" + name)) {
        max_default = opt<T>("max-" + name);
    }
    return {min_default, max_default};
}
 
template <class T>
T get_value(const string &name, T val_default) {
    if (has_opt(name)) {
        auto res = opt<T>(name);
        return res;
    }
    return val_default;
}
 
vector<int> getn_random(int min_n, int max_n, int MAX_T, int budget) {
    vector<int> res;
    while (budget >= min_n && res.size() < MAX_T) {
        int lo = min_n, hi = min(max_n, budget);
        int n = rnd.next(lo, hi);
        res.push_back(n);
        budget -= n;
    }
    return res;
}

void test_generator(int s,string mode){
    int n=rnd.next(max(1,s/MAX_N),min(s,MAX_N));
    if(mode == "line") n = 1;
    int m=min(MAX_N,s/n);

    cout << n << ' ' << m << '\n';
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int w = 0;
            if(mode == "01") w = rnd.next(0,1);
            else w = rnd.next(0,MAX_A);
            if(j) cout << ' ';
            cout << w;
        }
        cout << '\n';
    }


}

 
int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
 
    const string mode = opt<string>("mode");
    const int T = get_value("T", MAX_T);
    const int budget = get_value("S", MAX_S);
 
    auto [min_s, max_s] = get_range("s", 1, MAX_S);

    if(mode == "line") tie(min_s,max_s) = get_range("s",1,MAX_N);
    else if(mode == "full") min_s = max_s = MAX_S;

    vector<int> s_vals = getn_random(min_s, max_s, T, budget);

    cout << (int)s_vals.size() << '\n';
    for(int s: s_vals) test_generator(s,mode);
 
    return 0;
}
