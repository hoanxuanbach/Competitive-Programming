#include<bits/stdc++.h>
using namespace std;
#define maxn 50005
#define pii pair<int,int>
int n,k,deg[maxn],ans,len,num[maxn],res;
vector<int> edge[maxn],ver;
set<pii> s;
bool check[maxn];
bool ok(int mask){
    for(int i=0;i<len;i++){
        if(((mask>>i)&1)==0) continue;
        for(int j=0;j<i;j++){
            if(((mask>>j)&1)==0) continue;
            int a=ver[i],b=ver[j];
            if(*lower_bound(edge[a].begin(),edge[a].end(),b)!=b) return false;
        }
    }
    return true;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> deg[i];s.insert({deg[i],i});
        for(int j=1;j<=deg[i];j++){
            int x;cin >> x;x++;
            edge[i].push_back(x);
        }
        sort(edge[i].begin(),edge[i].end());
    }
    for(int i=1;i<=n;i++){
        pii p=*s.begin();check[p.second]=true;
        s.erase(s.begin());ver={p.second};
        for(int v:edge[p.second]){
            if(check[v]) continue;
            ver.push_back(v);
        }
        len=(int)ver.size();
        for(int mask=(1<<len)-1;mask>=(1<<ans);mask--){
            int cnt=0;
            for(int j=0;j<len;j++) cnt+=(mask>>j)&1;
            if(cnt<=ans) continue;
            if(ok(mask)) ans=cnt;
        }
        for(int v:edge[p.second]){
            if(check[v]) continue;
            s.erase({deg[v],v});deg[v]--;
            s.insert({deg[v],v});
        }
    }
    cout << ans << '\n';
}
