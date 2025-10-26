#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
const int maxn = 5e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
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

vector<int> d[maxn];
void solve(){
    int n,k;cin >> n >> k;
    combi(n);

    for(int i=1;i<=n;i++) d[i].clear();
    vector<vector<int>> g(n+1);
    for(int i=2;i<=n;i++){
        int x;cin >> x;
        g[x].push_back(i);
    }

    if(k==1){
        cout << n << '\n';
        return;
    }
    else if(k==2){
        cout << n*(n-1)%mod << '\n';
        return;
    }

    function<void(int)> dfs = [&](int u){
        for(int v:g[u]) dfs(v);
        
        if(g[u].empty()){
            d[u].push_back(1);
            return;
        }

        for(int i=1;i<(int)g[u].size();i++) if((int)d[g[u][i]].size()>(int)d[g[u][0]].size()) swap(g[u][i],g[u][0]);
        swap(d[u],d[g[u][0]]);
        d[u].push_back(1);

        for(int i=1;i<(int)g[u].size();i++){
            int v=g[u][i],pos=(int)d[u].size()-2;
            for(int j=(int)d[v].size()-1;j>=0;j--){
                d[u][pos]+=d[v][j];
                pos--;
            }
        }
    };
    dfs(1);

    int total=0,lst=n;
    vector<int> cur(n,0);
    cur.insert(cur.end(),d[1].begin(),d[1].end());


    function<void(int)> dfs2 = [&](int u){

        for(int i=lst;i<(int)cur.size();i++) total=(total+C(cur[i],k-1))%mod;
        if(g[u].empty()) return;

        for(int i=1;i<(int)g[u].size();i++){
            int v=g[u][i],pos=(int)d[u].size()-2;
            for(int j=(int)d[v].size()-1;j>=0;j--){
                d[u][pos]-=d[v][j];
                pos--;
            }
        }
        d[u].pop_back();
        swap(d[u],d[g[u][0]]);


        cur.push_back(0);
        for(int v:g[u]){
            int pos=(int)cur.size()-1;
            for(int j=(int)d[v].size()-1;j>=0;j--) cur[pos-2]-=d[v][j],cur[pos]+=d[v][j],pos--;

            int pre=lst;
            lst=min(lst,pos+1);
            dfs2(v);
            lst=pre;

            pos=(int)cur.size()-1;
            for(int j=(int)d[v].size()-1;j>=0;j--) cur[pos-2]+=d[v][j],cur[pos]-=d[v][j],pos--;
        }
        cur.pop_back();

        swap(d[u],d[g[u][0]]);
        d[u].push_back(1);
        for(int i=1;i<(int)g[u].size();i++){
            int v=g[u][i],pos=(int)d[u].size()-2;
            for(int j=(int)d[v].size()-1;j>=0;j--){
                d[u][pos]+=d[v][j];
                pos--;
            }
        }
    };

    dfs2(1);
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}