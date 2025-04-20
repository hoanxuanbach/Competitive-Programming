#include<bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
const int maxn = 1e5+5;
const int mod = 1e9;

int sx,sy;
vector<int> cx,cy;

vector<int> pos[maxn];
int sum[maxn],cnt[maxn],ls[maxn],lc[maxn],rs[maxn],rc[maxn];
int nsum[maxn],ncnt[maxn];

i32 DistanceSum(i32 N, i32 *X, i32 *Y) {
    for(int i=0;i<N;i++){
        cx.push_back(X[i]);
        cy.push_back(Y[i]);
    }
    sort(cx.begin(),cx.end());
    sort(cy.begin(),cy.end());
    cx.erase(unique(cx.begin(),cx.end()),cx.end());
    cy.erase(unique(cy.begin(),cy.end()),cy.end());
    sx=(int)cx.size();sy=(int)cy.size();
    for(int i=0;i<N;i++){
        X[i]=lower_bound(cx.begin(),cx.end(),X[i])-cx.begin()+1;
        Y[i]=lower_bound(cy.begin(),cy.end(),Y[i])-cy.begin()+1;
    }
    auto cal = [&](){
        vector<piii> pre;
        for(int t=1;t<=sx;t++) pos[t].clear();
        for(int i=0;i<N;i++) pos[X[i]].push_back(Y[i]);
        int cnt=0;
        vector<int> val;
        vector<vector<int>> edge;
        for(int t=1;t<=sx;t++){
            sort(pos[t].begin(),pos[t].end());
            vector<piii> cur;
            for(int y:pos[t]){
                if(cur.empty() || cur.back().fi.se+1<y){
                    cur.push_back({{y,y},cnt++});
                    edge.push_back({});val.push_back(1);
                }
                else cur.back().fi.se++,val[cur.back().se]++;
            }
            int p=0;
            for(auto [x,u]:cur){
                auto [l,r]=x;
                //cout << t << ' ' << l << ' ' << r << ' ' << u << '\n';
                auto add = [&](int lt,int rt){
                    int L=max(l,lt),R=min(r,rt);
                    return (L<=R);
                };
                while(p<(int)pre.size() && pre[p].fi.se<=r){
                    auto [xt,v]=pre[p++];
                    if(add(xt.fi,xt.se)){
                        edge[u].push_back(v);
                        edge[v].push_back(u);
                        //cout << "edge " << u << ' ' << v << '\n';
                    }
                }
                if(p<(int)pre.size() && add(pre[p].fi.fi,pre[p].fi.se)){
                    edge[u].push_back(pre[p].se);
                    edge[pre[p].se].push_back(u);
                    //cout << "edge " << u << ' ' << pre[p].se << '\n';
                }
            }
            pre=cur;
        }
        int res=0;
        function<void(int,int)> dfs = [&](int u,int p){
            for(int v:edge[u]){
                if(v!=p) dfs(v,u),val[u]+=val[v];
            }
            res=(res+val[u]*(N-val[u]))%mod;
        };
        dfs(0,-1);
        //cout << '\n';
        return res;
    };
    int total=cal();
    swap(sx,sy);
    for(int i=0;i<N;i++) swap(X[i],Y[i]);
    total=(total+cal())%mod;
    return total;
}
#undef int
