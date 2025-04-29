#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
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

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n),b(m);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> b[i];
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    
    vector<int> cc(n-1);
    for(int i=0;i<n-1;i++) cc[i]=a[i]^a[i+1];
    
    vector<int> cnt;
    vector<array<int,2>> nxt;
    nxt.push_back({0,0});
    cnt.push_back(0);
    auto add = [&](int x){
        int u = 0;
        for(int i=29;i>=0;i--){
            cnt[u]++;
            int d=(x>>i&1);
            if(!nxt[u][d]){
                nxt[u][d]=(int)nxt.size();
                nxt.push_back({0,0});
                cnt.push_back(0);
            }
            u=nxt[u][d];
        }
        cnt[u]++;
    };
    auto get = [&](int x,int k){
        int u = 0;
        for(int i=29;i>=k;i--){
            int d=(x>>i&1);
            if(!nxt[u][d]) return 0LL;
            u=nxt[u][d];
        }
        return cnt[u];
    };
    for(int i=0;i<m;i++) add(b[i]);

    int total=0;
    auto cal = [&](int num,int k){
        for(int i=0;i<m;i++){
            int cnt=get(b[i]^num,k);
            if(!(num>>k)) cnt--;
            total+=cnt;
        }
    };    

    function<void(int,int,vector<int>)> dfs = [&](int k,int num,vector<int> cc){
        if(k<0){
            cal(num,0);
            return;
        }
        int cur=0;
        for(int x:cc) cur|=1<<(x>>k&1);
        if(cur&1){
            vector<int> nw;
            for(int x:cc) if(!(x>>k&1)) nw.push_back(x);
            dfs(k-1,num,nw);
        }
        else{
            cal(num,k);
            dfs(k-1,num|(1<<k),cc);
        }
    };
    dfs(29,0,cc);
    cout << total/2 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
