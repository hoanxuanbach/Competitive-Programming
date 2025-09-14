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
const int inf = 9e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int L=60;
void solve(){
    int n,m;cin >> n >> m;

    int X=0;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i],X^=a[i];

    vector<vector<int>> f(L+1);
    for(int i=0;i<=L;i++){
        for(int j=0;j<n;j++) if(!(a[j]>>i&1)) f[i].push_back(j);
        int T=(1LL<<i)-1;
        sort(f[i].begin(),f[i].end(),[&](int x,int y){
            return (a[x]&T)>(a[y]&T);
        });
    }

    int K=-1;
    for(int i=L;i>=0;i--){
        if(X>>i&1){
            if(f[i].empty()) K=i;
            break;
        }
    }

    int ans=inf;
    vector<vector<pii>> S;

    vector<pii> P;
    vector<int> pos,vis(n);

    vector<int> b=a;
    auto roll = [&](int x){
        while((int)P.size()>x){
            auto &[u,d]=P.back();P.pop_back();
            X^=b[u];b[u]-=d;vis[u]--;X^=b[u];
            if(!vis[u]) pos.pop_back();
        }
    };
    auto add = [&](int x,int i){
        int k=(((b[x]>>i)+1)<<i)-b[x];
        X^=b[x];b[x]+=k;X^=b[x];
        if(!vis[x]) pos.push_back(x);
        P.push_back({x,k});vis[x]++;
        return k;
    };
    function<int(int)> cal = [&](int x){
        int res=0;
        int sz=(int)P.size();
        for(int i=x;i>=0;i--){
            if(!(X>>i&1)) continue;
            int p=(pos.empty()?0:pos[0]);
            for(int j:f[i]) if(!vis[j]){
                p=j;
                break;
            }
            res+=add(p,i);
        }
        roll(sz);
        return res;
    };
    function<void(int,int)> dfs = [&](int x,int val){
        if((int)S.size()==m) return;
        if(!X){
            vector<pii> p;
            for(int u:pos) p.push_back({u,b[u]-a[u]});
            S.push_back(p);
            return;
        }
        if(x==-1) return;
        if(!(X>>x&1)) return dfs(x-1,val);
        //cout << "dfs " << x << ' ' << val << ' ' << X << '\n';
        int sz=(int)P.size();
        for(int &i:f[x]){
            if((int)S.size()==m) return;
            if(vis[i]) continue;
            int w=add(i,x);
            //cout << "get " << x << ' ' << i << ' ' << w << ' ' << X << '\n';
            if(val+w+cal(x)==ans){
                dfs(x-1,val+w);
                roll(sz);
            }
            else{
                roll(sz);
                return;
            }
        }

        if((int)S.size()==m) return;

        vector<int> tmp=pos;
        for(int &i:tmp){
            if((int)S.size()==m) return;
            int w=add(i,x);
            if(val+w+cal(x)==ans){
                dfs(x-1,val+w);
                roll(sz);
            }
            else{
                roll(sz);
                return;
            }
        }
    };
    if(K==-1){
        ans=cal(L);
        dfs(L,0);
    }
    else{
        for(int i=K+1;i<=L;i++){
            if((int)f[i].size()<=1) continue;
            ans=min(ans,add(f[i][0],i)+add(f[i][1],i)+cal(i));
            roll(0);
        }

        for(int i=K+1;i<=L;i++){
            if((int)f[i].size()<=1) continue;
            int sz=(int)f[i].size();
            for(int x=0;x<sz;x++){
                if((int)S.size()==m) break;
                int vx=add(f[i][x],i);
                for(int y=x+1;y<sz;y++){
                    if((int)S.size()==m) break;
                    int vy=add(f[i][y],i);
                    if(vx+vy+cal(i)==ans) dfs(i,vx+vy);
                    else{
                        roll(1);
                        break;
                    }
                    roll(1);
                }
                roll(0);
            }
        }
    }   

    cout << ans << '\n' << (int)S.size() << '\n';
    for(auto p:S){
        cout << (int)p.size() << '\n';
        sort(p.begin(),p.end());
        for(auto k:p) cout << k.first+1 << ' ';
        cout << '\n';
        for(auto k:p) cout << k.second << ' ';
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int C,test=1;cin >> C >> test;
    while(test--) solve();
}
