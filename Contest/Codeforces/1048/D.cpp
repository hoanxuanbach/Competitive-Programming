#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int CP(int n,int k){
    return fac[n]*dfac[n-k]%mod;
}

void solve(){
    int n,m,q;cin >> n >> m >> q;combi(q);
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i],a[i]-=i;
    
    vector<pii> P(q);
    for(int i=0;i<q;i++) cin >> P[i].second >> P[i].first,P[i].first-=P[i].second;
    for(int i=1;i<=n;i++) P.push_back({a[i],-i});
    sort(P.begin(),P.end());

    for(int x=1;x<=n;x++){
        int L=0,R=m-n,res=0;
        
        array<int,3> mn={0,0,0},mx={0,0,0},eq={0,0,0};
        for(int i=0;i<n+q;i++){
            if(P[i].second<0) continue;
            if(P[i].second==x) eq[2]++;
            else if(P[i].second<x) mx[2]++;
            else mn[2]++;
        }
        auto get = [&](int l,int r){
            if(l>r) return 0LL;
            array<int,4> val={0,0,0,0};
            int cnt=mx[0]+mn[2],cq=q-cnt;
            if(eq[1]){//first eq
                val[3]=(val[3]+eq[1]*fac[cq-1]%mod)%mod;
            }
            if(mx[1]){//first mx[1]
                int seq=eq[1]+mn[0]+mn[1]+eq[0];
                int err=mx[2]+eq[2];
                int mul=mx[1]*CP(cq-1,mx[1]-1)%mod,ncq=cq-mx[1];
                if(seq) val[3]=(val[3]+mul*seq%mod*fac[ncq-1])%mod;
                else if(!err) val[2]=(val[2]+mul)%mod;
            }
            if(mn[1]){//first mn[1]
                int seq=eq[2]+mx[2]+eq[1]+mx[1];
                int err=mn[0]+eq[0];
                int mul=mn[1]*CP(cq-1,mn[1]-1),ncq=cq-mn[1];
                if(seq) val[3]=(val[3]+mul*seq%mod*fac[ncq-1])%mod;
                else if(!err) val[1]=(val[1]+mul)%mod;
            }  
            if(!cq) val[0]=(val[0]+1)%mod; 
            int res=val[3];
            if(l<=a[x] && a[x]<=r) res=(res+val[0])%mod;
            if(l<=a[x]) res=(res+val[1])%mod;
            if(a[x]<=r) res=(res+val[2])%mod;
            return res*CP(q,cnt)%mod;
        };
        vector<int> cur;
        auto cal = [&](int l,int r){
            for(int i:cur){
                if(i<x) mx[2]--,mx[1]++;
                else if(i==x) eq[2]--,eq[1]++;
                else mn[2]--,mn[1]++;
            }
            res=(res+l*get(l,r))%mod;
            for(int i:cur){
                if(i<x) mx[1]--,mx[0]++;
                else if(i==x) eq[1]--,eq[0]++;
                else mn[1]--,mn[0]++;
            }
            int k=((r-l)*(l+1+r)/2)%mod;
            res=(res+k*get(l+1,r))%mod;
        };
        for(int i=0;i<n+q;i++){
            if(L<P[i].first){
                cal(L,P[i].first-1),L=P[i].first;
                cur.clear();
            }
            if(P[i].second>0) cur.push_back(P[i].second);
        }
        if(L<=R) cal(L,R);

        res=(res+x*fac[q])%mod;
        cout << res << ' ';
    }
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
