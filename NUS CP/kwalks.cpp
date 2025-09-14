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

const int N=500;

void solve(){
    int n,m,K;cin >> n >> m >> K;
    
    int nn=n;
    bitset<N> empty;
    vector<bitset<N>> B(n);
    for(int i=0;i<m;i++){
        int u,v,w;cin >> u >> v >> w;u--;v--;
        int x=u;
        for(int j=0;j<w;j++){
            if(j==w-1) B[x][v]=1;
            else{
                B[x][n]=1;
                B.push_back(empty);
                x=n++;
            }
        }
        x=v;
        for(int j=0;j<w;j++){
            if(j==w-1) B[x][u]=1;
            else{
                B[x][n]=1;
                B.push_back(empty);
                x=n++;
            }
        }
    }
    assert(n<=N);
    vector<bitset<N>> S(n);
    for(int i=0;i<n;i++) S[i][i]=1;

    auto unite = [&](vector<bitset<N>> &X,vector<bitset<N>> Y){
        for(int i=0;i<n;i++){
            bitset<N> T;
            for(int j=0;j<n;j++) if(X[i][j]) T|=Y[j];
            swap(X[i],T);
        }
    };

    int KK=K;
    while(K){
        if(K&1) unite(S,B);
        unite(B,B);K>>=1;
    }

    bool over=false;
    int md=10000000;
    K=KK;swap(n,nn);
    if(K>=md) over=true,K%=md;
    for(int x=0;x<n;x++){
        vector<int> d(nn,-1);
        queue<int> q;q.push(x);d[x]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v=0;v<nn;v++) if(S[u][v] && d[v]==-1){
                d[v]=d[u]+1;
                q.push(v);
            }
        }
        for(int y=0;y<n;y++){
            if(d[y]==-1) cout << -1 << ' ';
            else if(!d[y]) cout << 0 << ' ';
            else{
                int T=d[y]*K;
                bool cur=over;
                if(T>=md) cur=true,T%=md;
                if(cur){
                    string out=to_string(T);
                    while((int)out.size()<7) out="0"+out;
                    cout << out << ' ';
                }
                else cout << T << ' ';
            }
        }
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
