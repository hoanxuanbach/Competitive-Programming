#include<bits/stdc++.h>
using namespace std;
const int maxn = 40005;

int A=2,B=5;
/*Random
7
3 4
1 6
1 5
7 2
7 3
4 1

*/
/*Line
7
1 2
2 3
3 4
4 5
5 6
6 7
*/

int f[maxn];
vector<pair<int,int>> g[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }

    int root = -1;
    for(int i=1;i<=n;i++) if((int)g[i].size()==1) root=i;

    vector<int> c(n);
    function<int(int,int,int)> get = [&](int u,int x,int p){
        if(u==x) return 0;
        for(auto [v,id]:g[u]){
            if(id==p) continue;
            int val=get(v,x,id);
            if(val!=-1){
                if(p) val+=(c[p]!=c[id]);
                return val;
            }
        }
        return -1;
    };

    int cnt_ask = 0;
    vector<pair<vector<int>,int>> query;
    auto ask = [&](){
        if(cnt_ask==31) assert(false);

        c[0]=0;
        cnt_ask++;
        cout << "? ";
        for(int i=1;i<n;i++) cout << c[i] << ' ';
        cout << endl;
        int val;
        //val=get(A,B,0);
        cin >> val;
        //cout << val << '\n';
        query.push_back({c,val});
        return val;
    };

    auto build = [&](int U){
        vector<bool> used(n+1,true);
        used[U]=false;
        for(auto [cc,val]:query){
            function<void(int,int,int)> dfs = [&](int u,int p,int d){
                if(d!=val) used[u]=false;
                for(auto [v,id]:g[u]){
                    if(p==id) continue;
                    int nd=d+(p && cc[p]!=cc[id]);
                    dfs(v,id,nd);
                }
            };
            dfs(U,0,0);
        }
        vector<int> cand;
        for(int i=1;i<=n;i++) if(used[i]) cand.push_back(i);
        return cand;
    };

    vector<pair<int,int>> order;
    function<void(int,int)> dfs = [&](int u,int p){
        for(auto [v,id]:g[u]){
            if(id==p) continue;
            order.push_back({v,id});
            c[id]=c[p]^1;
            dfs(v,id);
        }
    };
    dfs(root,0);
    for(int i=0;i<(int)order.size();i++) f[order[i].second]=i;

    int dist=ask();

    if(dist){
        
        int l=dist,r=n-2;
        while(l<r){
            int mid=(l+r)>>1;
            //cout << '*' << mid+1 << '\n';
            function<void(int,int,int)> cal = [&](int u,int p,int x){
                for(auto [v,id]:g[u]){
                    if(v==p) continue;
                    //cout << "edge " << id << ' ' << mid << '\n';
                    if(f[id]<=mid) c[id]=x,cal(v,u,x);
                    else c[id]=x^1,cal(v,u,x^1);
                }
            };
            cal(root,0,0);
            if(ask()) l=mid+1;
            else r=mid;
        }
        
        int U=order[l].first;

        vector<int> cand=build(U);
        
        l=0,r=(int)cand.size()-1;
        vector<int> d(n+1);
        while(l<r){
            int mid=(l+r)>>1;
            d.assign(n+1,0);
            for(int i=0;i<=mid;i++) d[cand[i]]=1;
            function<int(int,int)> dfs2 = [&](int u,int p){
                int ret=d[u];
                for(auto [v,id]:g[u]){
                    if(v==p) continue;
                    c[id]=dfs2(v,u);
                    ret|=c[id];
                }
                return ret;
            };
            dfs2(U,0);

            if(ask()) l=mid+1;
            else r=mid;
        }    
        
        int V=cand[l];
        cout << "! " << U << ' ' << V << endl;
    }
    else{
        int deg=0;
        function<void(int,int)> dfs2 = [&](int u,int p){
            for(int i=0;i<(int)g[u].size();i++) if(g[u][i].first==p){
                g[u].erase(g[u].begin()+i);
                break;
            }
            deg=max(deg,(int)g[u].size());
            for(auto [v,id]:g[u]) dfs2(v,u);
        };
        dfs2(root,0);
        
        int L=0;
        while((1<<L)<deg) L++;
        
        int X=0;
        for(int x=0;x<L;x++){
            for(int i=1;i<=n;i++){
                for(int j=0;j<(int)g[i].size();j++) c[g[i][j].second]=(j>>x&1);
            }
            if(ask()) X^=(1<<x);
        }
        vector<array<int,3>> P;
        for(int i=1;i<=n;i++) for(int j=0;j<(int)g[i].size();j++){
            int k=j^X;
            if(k<j) P.push_back({i,j,k});
        }

        int l=0,r=(int)P.size()-1;
        while(l<r){
            int mid=(l+r)>>1;
            c.assign(n,0);
            for(int i=0;i<=mid;i++){
                auto [u,x,y]=P[i];
                c[g[u][y].second]=1;
            }
            if(ask()) r=mid;
            else l=mid+1;
        }
        auto [u,x,y]=P[l];
        cout << "! " << g[u][x].first << ' ' << g[u][y].first << endl;
    }
}
