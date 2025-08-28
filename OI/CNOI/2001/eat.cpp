#include<bits/stdc++.h>
using namespace std;
#define maxn 50005
#define pii pair<int,int>
int r[maxn],par[maxn],add[maxn],n,k,ans=0;
pii findpar(int u){
    if(u!=par[u]){
        pii x=findpar(par[u]);
        return {x.first,(x.second+add[u])%3};
    }
    return {u,add[u]%3};
}
void unions(int u,int v,int x){
    pii pu=findpar(u),pv=findpar(v);
    if(pu.first==pv.first){
        if((pu.second+x)%3!=pv.second) ans++;
        return;
    }
    if(r[pu.first]>r[pv.first]){
        par[pv.first]=pu.first;
        r[pu.first]+=r[pv.first];
        add[pv.first]+=((pu.second+x-pv.second-add[pu.first])%3+3)%3;
    }
    else{
        par[pu.first]=pv.first;
        r[pv.first]+=r[pu.first];
        add[pu.first]+=((pv.second-x-pu.second-add[pv.first])%3+3)%3;
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++) r[i]=1;
    for(int i=1;i<=n;i++) par[i]=i;
    for(int i=1;i<=k;i++){
        int t,x,y;cin >> t >> x >> y;
        if(x>n || y>n) ans++;
        else if(t==1) unions(x,y,0);
        else unions(x,y,1);
    }
    cout << ans << '\n';
}