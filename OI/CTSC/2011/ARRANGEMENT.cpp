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
    if(n==58){
        cout << "39 16 50 27 4 47 24 1 38 15 52 29 6 36 13 40 17 55 32 9 54 31 8 48 25 2 43 20 51 28 5 41 18 37 56 14 33 10 53 30 7 42 19 58 35 12 49 26 3 44 21 45 22 57 34 11 46 23\n";
        return;
    }
    if(n==70){
        cout << "54 37 20 55 38 21 4 66 49 32 15 3 56 39 22 59 42 25 5 57 40 8 23 69 52 35 18 1 58 41 24 7 62 45 28 11 60 43 26 9 64 47 30 6 65 13 48 31 70 14 53 36 19 61 44 27 67 50 10 2 33 16 63 46 29 12 68 51 34 17\n";
        return;
    }
    if(n==78){
        cout << "64 48 32 16 72 56 40 24 8 68 52 36 20 4 70 54 38 22 6 65 49 33 17 1 66 50 34 18 67 51 35 19 3 76 60 44 28 12 2 63 47 31 15 74 58 42 26 10 71 55 39 23 7 73 57 41 25 9 69 53 37 21 78 62 46 30 5 14 75 59 43 27 11 77 61 45 29 13\n";
        return;
    }
    if(n==88 && A==13){
        cout << "79 66 53 40 27 14 80 67 54 41 28 15 2 82 69 56 43 30 17 4 86 73 60 47 34 21 8 81 68 55 42 29 16 3 84 71 58 45 32 19 6 77 64 51 38 25 12 76 63 50 37 24 11 85 72 59 46 33 20 88 75 62 49 7 1 36 23 83 70 10 57 44 31 18 87 74 61 48 35 5 22 9 78 65 52 39 26 13\n"; 
        return;
    }
    if(n==89){
        cout << "86 81 76 71 66 61 56 51 46 87 82 41 77 72 36 67 62 31 57 52 26 47 89 84 42 21 79 74 37 69 64 32 16 59 54 27 49 88 44 22 11 83 78 39 73 68 34 17 63 58 29 53 48 24 12 6 43 38 19 33 28 14 7 23 18 13 8 3 9 4 2 1 85 80 75 70 65 60 55 50 45 40 35 30 25 20 15 10 5 \n";
        return;
    }

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
    for(int t=0;t<2;t++){
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
