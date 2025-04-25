#include<bits/stdc++.h>
using namespace std;
const int maxn = 1500005;
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}

int n,k,par[maxn];
vector<int> edge[maxn];

int dist[maxn],ind[maxn],h[maxn];
bool dia[maxn],used[maxn],del[maxn];
vector<int> col;
int cnt,sz,num[maxn];

void dfs_dist(int u,int p){
    par[u]=p,dist[u]=dist[p]+1;
    for(int v:edge[u]) if(v!=p) dfs_dist(v,u);
}

int dfs(int u,int p){
    dist[u]=dist[p]+1;
    for(int v:edge[u]) if(v!=p && !dia[v]) ind[v]=ind[u],h[u]=max(h[u],1+dfs(v,u));
    return h[u];
}
void update(int l,int r,int val){
    num[l]=1LL*num[l]*val%mod;
    num[r]=1LL*num[r]*power(val,mod-2)%mod;
}

int get_ways(int u,int p,int d){
    if(!d || used[u]) return 1;

    int res=1;
    for(int v:edge[u]) if(v!=p && !dia[v]) res=1LL*res*get_ways(v,u,d-1)%mod;
    return (res+1)%mod;
}

void dfs_ways(int u,int p){
    if(!dia[u]){
        int dl=dist[u]+ind[u],dr=dist[u]+sz-1-ind[u];
        int ml=dl+h[u],mr=dr+h[u];
        if(ml+1<k && mr+1>=k){
            if(dr<k){
                int val=get_ways(u,p,k-dr-1);
                update(sz%k,ind[u],val);
            }
            return;
        }
        else if(ml+1>=k && mr+1<k){
            if(dl<k){
                int val=get_ways(u,p,k-dl-1);
                update(ind[u]+1,k,val);
            }
            return;
        }
        else if(ml+1>=k && mr+1>=k){
            int d0=-2*n,d1=-2*n;
            for(int v:edge[u]) if(v!=p && !dia[v]){
                if(h[v]+1>d0) d1=d0,d0=h[v]+1;
                else d1=max(d1,h[v]+1);
            }
            if(d0+d1+1>=k){
                int cur=dl%k;
                for(int x:col){
                    if(cur==x) continue;
                    int dd=(k+x-cur)%k;
                    if(dd<=d1 && 2*dd+1<=k) del[x]=true;
                    if(min(d0,dd-1)+min(d1,dd-1)+1>=k) del[x]=true;
                }
            }
        }
    }
    for(int v:edge[u]) if(v!=p && !dia[v]) dfs_ways(v,u);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    dist[0]=-1;
    vector<int> D;
    {
        dfs_dist(1,0);
        int X=max_element(dist+1,dist+n+1)-dist;
        dfs_dist(X,0);
        int Y=max_element(dist+1,dist+n+1)-dist;
        D.push_back(Y);
        while(Y!=X) D.push_back(Y=par[Y]);
    }
    sz=(int)D.size();
    for(int u:D) dia[u]=true;
    for(int i=0;i<sz;i++) ind[D[i]]=i,dfs(D[i],0);
    if(sz<k){
        int res=1;
        for(int i=0;i<n;i++) res=res*2%mod;
        cout << "YES\n" << res << '\n';
        return 0;
    }
    for(int i=0;i<k;i++) num[i]=1;
    for(int u=1;u<=n;u++){
        if(dia[u]) continue;
        int dl=dist[u]+ind[u],dr=dist[u]+sz-1-ind[u];
        int ml=dl+h[u],mr=dr+h[u];
        if(ml+1<k && mr+1<k) used[u]=true,cnt++;
        else if(ml+1>=k && mr+1>=k){
            int cl=dl%k,cr=((ind[u]-dist[u])%k+k)%k;
            if(cl!=cr) del[cl]=del[cr]=true;
        }
    }
    for(int i=0;i<k;i++) if(!del[i]) col.push_back(i);
    for(int u:D) dfs_ways(u,0);

    bool check=false;
    for(int i=0;i<k;i++) if(!del[i]) check=true;

    int total=0;
    for(int i=0;i<k;i++){
        if(i) num[i]=1LL*num[i]*num[i-1]%mod;
        if(!del[i]) total=(total+num[i])%mod;
    }
    while(cnt--) total=total*2%mod;
    cout << (check?"YES\n":"NO\n") << total << '\n';
}