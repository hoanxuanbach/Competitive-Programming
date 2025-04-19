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
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int Bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int N,Q,D,A,B;
int L[maxn],R[maxn],dp[maxn];
int num[maxn],res[maxn];
vector<pii> qq[maxn];

void solve(){
    cin >> N >> Q >> D >> A >> B;
    for(int i=1;i<=N;i++) cin >> L[i] >> R[i];
    L[N+1]=inf;

    vector<pii> p;
    deque<pii> dq;
    dq.push_back({0,L[1]-1});
    p.push_back({0,L[1]-1});
    for(int i=1;i<=N;i++){
        int l=R[i]+1-D,r=L[i+1]-1-D;
        while(!dq.empty()){
            if(dq.front().se<l) dq.pop_front();
            else break;
        }
        if(!dq.empty()){
            dp[i]=max(dq.front().fi,l)+D;
            if(dp[i]<=r+D){
                dq.push_back({dp[i],r+D});
                p.push_back({dp[i],r+D});
            }
        }
        else dp[i]=inf;
    }

    N=(int)p.size();
    for(int i=0;i<N;i++){
        L[i]=p[i].fi;
        R[i]=p[i].se;
    }
    auto get_pos = [&](int x){
        int l=0,r=N-1,pos=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(L[mid]<=x) pos=mid,l=mid+1;
            else r=mid-1;
        }
        return pos;
    };
    if(A*D<=B){
        for(int i=1;i<N;i++){
            int pos=get_pos(L[i]-D);
            num[i]=num[pos]+1;
        }
        for(int i=1;i<=Q;i++){
            int X;cin >> X;
            int pos=get_pos(X);
            if(X>R[pos]) cout << -1 << '\n';
            else cout << A*X+num[pos]*(B-A*D) << '\n';
        }
    }
    else{
        set<pii> ss;
        ss.insert({0,0});
        auto add = [&](int l,int r,int x){
            //cout << "add " << l << ' ' << r << ' ' << x << '\n';
            if(l>r) return;
            auto it=ss.upper_bound({l,inf});it--;
            while(it!=ss.end() && it->fi<=r){
                int sl=it->fi,val=it->se;
                it=ss.erase(it);
                int sr=(it==ss.end()?D-1:it->fi-1);
                if(sl<l) ss.insert({sl,val});
                if(r<sr) ss.insert({r+1,val});
            }
            ss.insert({l,x});
        };
        for(int i=1;i<=Q;i++){
            int X;cin >> X;
            int pos=get_pos(X);
            if(X>R[pos]) res[i]=-1;
            else res[i]=A*X,qq[pos].push_back({X,i});
        }
        /*
        for(int i=0;i<N;i++){
            cout << L[i] << ' ' << R[i] << ' ';
            cout << '\n';
        }
        */
        for(int i=0;i<N-1;i++) qq[i].push_back({R[i],-1});
        for(int i=0;i<N;i++){
            for(auto [x,id]:qq[i]){
                //cout << x << ' ';
                auto it=ss.upper_bound({x%D,inf});it--;
                int val=it->se,cnt=(x/D)-val;x-=cnt*D;
                int pos=get_pos(x-D);
                if(pos>=0) cnt+=num[pos]+1;
                //cout << x << ' ' << val << ' ' << id << ' ' << cnt << '\n';
                if(id==-1) num[i]=cnt;
                else res[id]+=cnt*(B-A*D);
            }
            if(i+1<N){
                int l=R[i]+1,r=L[i+1]-1;
                if(r-l+1>=D){
                    add(0,r%D,r/D+1);
                    add(r%D+1,D-1,r/D);
                }
                else{
                    if(l%D<=r%D) add(l%D,r%D,r/D+1);
                    else{
                        add(l%D,D-1,r/D);
                        add(0,r%D,r/D+1);
                    }
                }
            }
        }
        for(int i=1;i<=Q;i++) cout << res[i] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
