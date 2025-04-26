// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
const int maxn = 105;
const double TL = 0.99;
const double Stemp= 1e9;
const double Etemp = 1e-4;
double query_temp(double tm){
    return Stemp*pow(Etemp/Stemp,(double)tm/TL);
}
int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

int n,A,B,d[maxn],dd[maxn];
vector<int> edge[maxn];

int Max=-1,sum;
int res[maxn],cur[maxn],p[maxn];

int cal(){
    /*
    for(int i=1;i<=n;i++){
        cout << cur[i] << ' ';
    }
    cout << '\n';
    */
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    for(int i=1;i<=n;i++){
        d[i]=dd[i];
        if(!d[i]) pq.push({cur[i],i});
    }
    for(int i=1;i<=n;i++){
        int u=pq.top().second;
        pq.pop();p[i]=u;
        for(int v:edge[u]){
            d[v]--;
            if(!d[v]) pq.push({cur[v],v});
        }
    }
    int total=0;
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if(p[i]<p[j]) total+=p[j]-p[i];
    if(total>Max){
        Max=total;
        for(int i=1;i<=n;i++) res[i]=p[i];
    }
    return total;
}

void solve(){
    cin >> n >> A >> B;
    rng.seed(69420);
    for(int i=1;i<=n;i++){
        if(i+A<=n){
            edge[i+A].push_back(i);
            dd[i]++;
        }
        if(B>1 && i*B<=n){
            edge[i*B].push_back(i);
            dd[i]++;
        }
        //cout << dd[i] << ' ';
    }
    //cout << '\n';
    for(int t=0;t<3;t++){
        for(int i=1;i<=n;i++) cur[i]=i;
        sum=cal();
        auto st = clock();
        while(true){
            auto tm=1.0*(clock()-st)/CLOCKS_PER_SEC;
            if(tm>TL) break;
            auto T = query_temp(tm);
            int u=rand_int(1,n),v=rand_int(1,n);
            swap(cur[u],cur[v]);
            int nw=cal();
            if(nw>sum || exp((nw-sum)/T)>=pp(rng)) sum=nw;
            else swap(cur[u],cur[v]);
        }
    }
    for(int i=1;i<=n;i++) cout << res[i] << ' ';
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
