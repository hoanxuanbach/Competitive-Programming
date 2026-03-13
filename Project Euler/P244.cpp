#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e8+7;
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

int d[(1<<16)+5][20];
int cnt[(1<<16)+5][20],sum[(1<<16)+5][20];

void solve(){
    memset(d,-1,sizeof(d));
    int S=0,T=0;
    for(int i=0;i<=3;i++){
        S^=1<<(4*i+2);
        S^=1<<(4*i+3);
        T^=1<<(4*i+((i&1)^1));
        T^=1<<(4*i+((i&1)^1)+2);
    }

    vector<pii> qq;
    qq.push_back({S,0});
    d[S][0]=0;cnt[S][0]=1;
    while(!qq.empty()){
        vector<pii> nq;
        for(auto [mask,t]:qq){
            if(mask==T && !t){
                cout << sum[T][0] << '\n';
                return;
            }
            auto add = [&](int nt,int w){
                int nmask=mask;
                int k=mask>>nt&1;
                if(k) nmask^=(1<<nt)^(1<<t);
                if(d[nmask][nt]==-1){
                    d[nmask][nt]=d[mask][t]+1;
                    nq.push_back({nmask,nt});
                }
                if(d[nmask][nt]==d[mask][t]+1){
                    cnt[nmask][nt]=(cnt[nmask][nt]+cnt[mask][t])%mod;
                    sum[nmask][nt]=(sum[nmask][nt]+sum[mask][t]*243+cnt[mask][t]*w)%mod;
                }
            };
            int x=t/4,y=t%4;
            if(x) add(t-4,'D');
            if(x<3) add(t+4,'U');
            if(y) add(t-1,'R');
            if(y<3) add(t+1,'L');
        }
        swap(qq,nq);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
