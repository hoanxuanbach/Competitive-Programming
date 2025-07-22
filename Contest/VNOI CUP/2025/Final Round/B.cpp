#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2=(mod+1)/2;
const int maxn = 2e3+5;
const int maxa = 1505*1505;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(1);
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int cur[maxa];
int c[maxn][maxn];

struct DS{
    int n,sz;
    bool vis[maxn];
    int cc[maxn][2*maxn],sum[maxn],pos[maxn];

    bool check(int i){
        if(vis[i]) return false;
        while(pos[i]<sz && cc[i][pos[i]]==0) pos[i]++;
        if(pos[i]==sz || cc[i][pos[i]]==sum[i]) return vis[i]=true;
        else return false;
    }

    void build(int m,int _sz){
        sz=_sz;
        for(int i=1;i<=n;i++) vis[i]=false,sum[i]=m,pos[i]=0;
    }

}col,row;

void solve(){   
    int n,m;cin >> n >> m;

    row.n=n;col.n=m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin >> c[i][j];
    
    int cnt=0;
    vector<int> color;
    auto reset = [&](){
        for(int x:color) cur[x]=-1;
    };
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        if(cur[c[i][j]]==-1){
            cur[c[i][j]]=cnt++;
            color.push_back(c[i][j]);
            if(cnt>n+m){
                reset();
                cout << "NO\n";
                return;
            }
        }
    }

    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        int id=cur[c[i][j]];
        row.cc[i][id]++;
        col.cc[j][id]++;
        c[i][j]=id;
    }
    reset();

    row.build(m,cnt);
    col.build(n,cnt);

    queue<int> q;
    for(int i=1;i<=n;i++) if(row.check(i)) q.push(i);
    for(int i=1;i<=m;i++) if(col.check(i)) q.push(-i);

    vector<array<int,3>> res;

    while(!q.empty()){
        int id=q.front();q.pop();
        if(id>0){
            int i=id;
            if(row.pos[i]<cnt) res.push_back({0,i,row.pos[i]});
            for(int j=1;j<=m;j++){
                if(c[i][j]==-1) continue;
                row.cc[i][c[i][j]]--;row.sum[i]--;
                col.cc[j][c[i][j]]--;col.sum[j]--;
                c[i][j]=-1;
                if(col.check(j)) q.push(-j);
            }
        }
        else{
            int j=-id;
            if(col.pos[j]<cnt) res.push_back({1,j,col.pos[j]});
            for(int i=1;i<=n;i++){
                if(c[i][j]==-1) continue;
                row.cc[i][c[i][j]]--;row.sum[i]--;
                col.cc[j][c[i][j]]--;col.sum[j]--;
                c[i][j]=-1;
                if(row.check(i)) q.push(i);
            }
        }
    }

    bool check=true;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        if(c[i][j]!=-1){
            check=false;
            row.cc[i][c[i][j]]=0;
            col.cc[j][c[i][j]]=0;
        }
    }
    if(!check){
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    cout << (int)res.size() << '\n';
    reverse(res.begin(),res.end());
    for(auto [t,id,x]:res) cout << t << ' ' << id << ' ' << color[x] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    memset(cur,-1,sizeof(cur));
    int test=1;cin >> test;
    while(test--) solve();
}