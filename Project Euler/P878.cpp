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

const int D = 5000;
void solve(){
    int T=0,N,K,L=0;
    cin >> N >> K;
    while((1LL<<L)<=N) L++;
    while((1LL<<T)<=K) T++;
    L=max(L,T);

    auto cal = [&](int x,int y){
        int val=0;
        for(int i=0;i<L;i++) if(x>>i&1) val^=(y<<i);
        val<<=1;
        for(int i=0;i<L;i++){
            if(x>>i&1) val^=(1LL<<(2*i));
            if(y>>i&1) val^=(1LL<<(2*i));
        }
        return val;
    };

    vector<vector<int>> f(K+1);
    for(int a=0;a<=D;a++) for(int b=0;b<=D;b++){
        int x=cal(a,b);
        if(x<=K) f[x].push_back(a),f[x].push_back(b);
    }
    //22713174
    int res=0;
    for(int X=0;X<=K;X++){
        cout << X << endl;
        set<int> S;

        queue<int> cand;
        auto update = [&](int a){
            //cout << "update " << a << endl;
            int k=0;
            while((1LL<<k)<=a) k++;
            int d=min(L,max(k+1,T));

            int M=max({2*k,2*d,k+d})+1;

            vector<int> f(M),cf(M);
            for(int i=0;i<min(M,L);i++) cf[i]=(X>>i&1);
            for(int i=0;i<min(k,L);i++) cf[2*i]^=(a>>i&1);

            for(int i=0;i<=d;i++){
                f[2*i]^=(1LL<<i);
                for(int j=0;j<k;j++) if(a>>j&1) f[i+j+1]^=(1LL<<i);
            }
            vector<int> g(d+1),cg(d+1);
            auto add = [&](int x,int val){
                //cout << "add " << x << ' ' << val << endl;
                for(int i=d;i>=0;i--) if(x>>i&1){
                    if(g[i]) x^=g[i],val^=cg[i];
                    else{
                        g[i]=x;
                        cg[i]=val;
                        return true;
                    }
                }
                if(val) return false;
                else return true;
            };
            bool ok=true;
            for(int i=0;i<M;i++) if(!add(f[i],cf[i])) ok=false;
            if(!ok) return false;
            //cout << "ok" << endl;
            function<void(int,int)> dfs = [&](int i,int x){
                if(x>N) return;
                if(i==d+1){
                    if(S.find(x)==S.end()){
                        S.insert(x);
                        cand.push(x);
                    }
                    if(a<=x) res++;
                    return;
                }
                if(!g[i]){
                    for(int j=0;j<=1;j++){
                        if(j && i>60) return;
                        dfs(i+1,x|(j<<i));
                    }
                }
                else{
                    int b=cg[i];
                    for(int j=0;j<i;j++) if(g[i]>>j&1) b^=(x>>j&1);
                    if(b && i>60) return;
                    dfs(i+1,x|(b<<i));
                }
            };
            dfs(0,0);
            return true;
        };
        //cout << '*' << st << endl;
        sort(f[X].begin(),f[X].end());
        f[X].erase(unique(f[X].begin(),f[X].end()),f[X].end());
        for(int a:f[X]){
            S.insert(a);
            cand.push(a);
        }
        while(!cand.empty()){
            int a=cand.front();cand.pop();
            update(a);
        }
    }

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
