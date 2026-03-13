#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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
    int N;cin >> N;
    vector<int> f(N,-1),X;f[0]=f[1]=-2;
    for(int i=2;i<N;i++) if(f[i]==-1){
        for(int j=i*2;j<N;j+=i) f[j]=-2;
        if(i%5==1){
            f[i]=(int)X.size();
            X.push_back(i);
        }
    }
    int sz=(int)X.size();
    vector<vector<int>> d(sz);
    for(int x=2;x<N;x++){
        if(f[x]>=-1){
            for(int i=x;i+1<N;i+=x) if(f[i+1]>=0) d[f[i+1]].push_back(x);
        }
    }

    int res=0;
    for(int id=0;id<sz;id++){
        if(id%1000==0) cout << id << endl;
        int p=X[id],g=2;
        while(true){
            bool ok=true;
            for(int x:d[id]){
                int k=(p-1)/x;
                if(power(g,k,p)==1){
                    ok=false;
                    break;
                }
            }
            if(ok) break;
            g++;
        }
        int k=(p-1)/5;
        int t=power(g,k,p);
        vector<int> root(5);root[0]=1;
        for(int i=1;i<5;i++) root[i]=root[i-1]*t%p;
        
        vector<int> jmp(5);
        for(int i=0;i<5;i++){
            int nxt=root[i]*power(root[i]+1,k,p)%p;
            for(int j=0;j<5;j++) if(root[j]==nxt) jmp[i]=j;
        }        
        res++;
        for(int i=0;i<5;i++){
            vector<bool> vis(5);
            int u=i;
            while(!vis[u]) vis[u]=true,u=jmp[u];
            if(u==i) res+=k;
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
