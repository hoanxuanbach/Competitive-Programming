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

void solve(){
    int L,N,K;cin >> L >> N >> K;
    vector<array<int,3>> T(N);
    for(int i=0;i<N;i++) cin >> T[i][0] >> T[i][1] >> T[i][2];
    sort(T.begin(),T.end(),[&](array<int,3> x,array<int,3> y){
        return x[0]+x[1]+x[2]>y[0]+y[1]+y[2];
    });

    vector<int> res(K+1);
    vector<set<pii>> S(K+1);
    for(int i=1;i<=K;i++){
        S[i].insert({0,inf});
        S[i].insert({L,inf});
    }
    auto cut = [&](int k,int x){
        auto it=S[k].lower_bound({x,0LL});
        if(it->first==x) return;
        it=prev(it);
        S[k].insert({x,it->second});
    };

    auto add = [&](int k,vector<array<int,3>> &g,int l,int r,int w){
        cut(k,l);cut(k,r);
        auto it=S[k].lower_bound({l,0LL});
        if(it->second<=w){
            g.push_back({l,r,w});
            return;
        }
        int x=l;
        while(x<r && it->second>=w){
            int v=it->second;
            it=S[k].erase(it);
            g.push_back({x,it->first,v});
            x=it->first;
        }
        if(x<r) g.push_back({x,r,w});
        S[k].insert({l,w});
    };
    auto cal = [&](int l,int r,int w,int k){
        k-=w;
        r=min(r,k);
        if(l>=r) return 0LL;
        return (k-l)*(k-l)-(k-r)*(k-r);
    };

    for(auto [x,y,z]:T){

        int k=x+y+z;
        vector<array<int,3>> G;
        //cout << '*' << x << ' ' << y << ' ' << z << '\n';
        G.push_back({x,L,y});
        for(int i=1;i<=K;i++){
            //cout << i << '\n';
            vector<array<int,3>> nG;
            for(auto [l,r,w]:G){
                //cout << l << ' ' << r << ' ' << w << '\n';
                int s=(int)nG.size();
                add(i,nG,l,r,w);
                for(int j=s;j<(int)nG.size();j++){
                    if(nG[j][2]!=w){
                        res[i]-=cal(nG[j][0],nG[j][1],nG[j][2],k);
                        res[i]+=cal(nG[j][0],nG[j][1],w,k);
                    }
                }
            }
            int d=(nG.empty()?x:nG.back()[1]);
            if(d<L) nG.push_back({d,L,y});
            swap(G,nG);
        }
    }
    for(int i=1;i<=K;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
