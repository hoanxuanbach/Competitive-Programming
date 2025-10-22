#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 1e9;

void solve(){
    int n,m;cin >> n >> m;
    vector<int> p(n),g(n);
    for(int i=0;i<n;i++) cin >> p[i],g[p[i]]=i;

    vector<int> l(m),r(m),f(m);
    
    set<pair<int,int>> A,B;
    for(int i=0;i<m;i++){
        cin >> l[i] >> r[i],f[i]=i;
        l[i]--;r[i]--;
        A.insert({l[i],i});
        B.insert({r[i],i});
    }

    int res=0;
    function<int(int)> ff = [&](int u){
        if(u!=f[u]) return f[u]=ff(u);
        return u;
    };
    auto unite = [&](int u,int v){
        u=ff(u);v=ff(v);
        if(u==v) return;
        f[v]=u;
        l[u]=max(l[u],l[v]);
        r[u]=min(r[u],r[v]);
    };

    for(int i=0;i<n;i++){
        int x=g[i],t=-1,cnt=0;
        while(!A.empty() && A.rbegin()->first>x){
            int id=A.rbegin()->second;
            A.erase({l[id],id});
            B.erase({r[id],id});
            if(t==-1) t=id;
            else unite(t,id);
            cnt++;
        }
        while(!B.empty() && B.begin()->first<x){
            int id=B.begin()->second;
            B.erase({r[id],id});
            A.erase({l[id],id});
            if(t==-1) t=id;
            else unite(t,id);
            cnt++;
        }
        if(cnt) res+=(cnt-1)*i;
        if(t!=-1){
            t=ff(t);
            A.insert({l[t],t});
            B.insert({r[t],t});
        }
    }
    int cnt=(int)A.size();
    res+=(cnt-1)*n;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}