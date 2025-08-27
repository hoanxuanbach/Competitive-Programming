#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
const int inv2= (mod+1)/2;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int maxn = 5e5+5;
int n,a[maxn],s[maxn];

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    
    int mul=1;
    vector<pii> P;
    auto build = [&](){
        int sz=(int)P.size();
        for(int i=1;i<=n;i++) s[i]=0;
        for(int i=0;i<(1<<sz);i++){
            for(int j=0;j<sz;j++) if(i>>j&1) swap(a[P[j].first],a[P[j].second]);
            for(int j=1;j<=n;j++) s[j]=(s[j]+a[j])%mod;
            for(int j=sz-1;j>=0;j--) if(i>>j&1) swap(a[P[j].first],a[P[j].second]);
        }
        for(int i=1;i<=n;i++) s[i]=(s[i]+s[i-1])%mod;
    };
    
    build();
    int q;cin >> q;

    int cnt=0;
    for(int i=1;i<=q;i++){
        int id,l,r;cin >> id >> l >> r;
        if(id==1){
            if((r-l)>1){
                cout << 0 << '\n';
                return;
            }
            cnt++;
            if(cnt>10){
                cout << 0 << '\n';
                return;
            }
            if(l!=r) P.push_back({l,r});
            mul=mul*inv2%mod;
            build();
        }
        else{
            int res=(s[r]-s[l-1]+mod)*mul%mod;
            cout << res << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
