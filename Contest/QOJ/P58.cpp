#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int L=18;
void solve(){
    int n;cin >> n;
    vector<int> a(n);
    vector<pii> P;
    for(int i=0;i<n;i++){
        cin >> a[i];
        P.push_back({a[i],i});
    }
    sort(P.begin(),P.end());
    for(int i=0;i<n;i++) a[P[i].second]=i+1;

    auto cal = [&](){
        vector<pii> P;
        vector<int> res(n);
        for(int i=0;i<n;i++) P.push_back({a[i],i});
        sort(P.begin(),P.end(),greater<pii>());

        vector<int> bit(n+1);
        auto update = [&](int x,int val){
            for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
        };
        auto query = [&](int x){
            int cnt=0;
            for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
            return cnt;
        };
        auto get = [&](int d){
            int x=0;
            for(int i=L;i>=0;i--){
                if(x+(1<<i)>n) continue;
                if(bit[x+(1<<i)]<=d) d-=bit[x+(1<<i)],x+=(1<<i);
            }
            return x;
        };

        vector<vector<pii>> f(n);
        for(auto [d,x]:P){
            if(x+1<n) f[x+1].push_back({d,1});
            int k=query(x+1);
            int pos=get(2*k);
            if(pos<n) f[pos].push_back({d,-1});
            update(x+1,1);
        }

        bit.assign(n+1,0);
        for(int i=0;i<n;i++){
            if(i) res[i]=res[i-1];
            for(auto [d,val]:f[i]) update(d,val);
            res[i]+=query(a[i]);
        }

        return res;
    };
    vector<int> S=cal();
    for(int i=0;i<n;i++) a[i]=n-a[i]+1;
    vector<int> T=cal();
    for(int i=0;i<n;i++) cout << min(S[i],T[i]) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
