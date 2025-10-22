#include<bits/stdc++.h>
using namespace std;
#define int long long 

void solve(){
    int n;cin >> n;
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int ans=0;
    vector<int> mn(n+1),mx(n+1);
    function<void(int,int)> dnc = [&](int l,int r){
        if(l==r){
            ans++;
            return;
        }
        int m=(l+r)>>1;
        dnc(l,m);dnc(m+1,r);

        for(int i=l;i<=r;i++) mn[i]=mx[i]=-1;    
        function<void(int,int)> dfs = [&](int u,int p){
            for(int v:g[u]){
                if(v==p || v<l || v>r) continue;
                mx[v]=max(v,mx[u]);
                mn[v]=min(v,mn[u]);
                dfs(v,u);
            }
        };
        
        mn[m]=mx[m]=m;dfs(m,0);

        int L=l,R=r;
        if(mn[m+1]==-1 || mx[m]==-1) return;
        for(int i=m+2;i<=r;i++){
            if(mn[i]==-1){
                R=i-1;
                break;
            }
            mn[i]=min(mn[i],mn[i-1]),mx[i]=max(mx[i],mx[i-1]);
        }

        for(int i=m-1;i>=l;i--){
            if(mn[i]==-1){
                L=i+1;
                break;
            }
            mn[i]=min(mn[i],mn[i+1]),mx[i]=max(mx[i],mx[i+1]);
        }

        /*
        L<=x<=m, m<y<=R 
        mn[x]=x,mx[y]=y;
        mn[y]>=x,mx[x]<=y 
        */

        int ly=m+1,ry=m,cl=0,cr=0;
        for(int x=m;x>=L;x--){
            if(mn[x]!=x) continue;
            while(ly<=R && mx[x]>ly){
                cl+=(mx[ly]==ly);
                ly++;
            }
            while(ry<R && mn[ry+1]>=x){
                ry++;
                cr+=(mx[ry]==ry);
            }
            if(ly<=ry) ans+=cr-cl;
        }
    };
    dnc(1,n);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}