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

const int inf = 1e18;
const int maxn = 2e6+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

const int lim = 200000;

void solve(){
    int n;cin >> n;

    int k=lim;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i],k=min(k,a[i]);

    int dd=0,res=0,mx=0;
    for(int i=1;i<=n;i++){
        mx=max(mx,a[i]);a[i]-=k;
        if(!a[i]) dd=n-i; 
    }

    vector<int> b(n+1);
    for(int i=1;i<=n;i++) b[(i+dd-1)%n+1]=a[i];

    vector<array<int,3>> op;

    vector<pii> P;
    for(int i=1;i<=n;i++){
        if(b[i]>b[i-1]) P.push_back({b[i]-b[i-1],i});
        else if(b[i-1]>b[i]){
            int cnt=b[i-1]-b[i];
            while(cnt){
                auto [d,l]=P.back();P.pop_back();
                int cc=min(d,cnt);
                d-=cc;cnt-=cc;res+=cc;
                op.push_back({l,i-1,cc});
                if(d) P.push_back({d,l});
            }
        }
    }

    set<array<int,3>> S;
    for(auto x:op) S.insert(x);
    op.clear();
    
    while(k && !S.empty()){
        auto x=*S.begin();S.erase(S.begin());
        auto it=S.upper_bound({x[1],inf,inf});
        if(it==S.end()) op.push_back(x);
        else{
            auto y=*it;S.erase(it);
            x[2]--;y[2]--;k--;
            if(x[2]) S.insert(x);
            if(y[2]) S.insert(y);
            it=S.lower_bound({x[0],y[1],0LL});
            if(it!=S.end() && (*it)[0]==x[0] && (*it)[1]==y[1]){
                int d=1+(*it)[2];S.erase(it);
                S.insert({x[0],y[1],d});
            }
            else S.insert({x[0],y[1],1});
            op.push_back({y[0],x[1],1});
        }
    }


    res+=k;
    if(k) op.push_back({1,n,k});
    for(auto x:S) op.push_back(x);

    cout << res << '\n';
    if(res<=lim){
        for(auto [l,r,d]:op){
            l=(l+n-dd-1)%n+1;
            r=(r+n-dd-1)%n+1;
            for(int i=0;i<d;i++) cout << l << ' ' << r << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}


