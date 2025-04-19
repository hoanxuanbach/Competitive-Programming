#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
const ll inf=1e18;

std::vector<ll> calculate_necessary_time(
    int N, int M, ll S, int Q, std::vector<int> A, std::vector<int> B,
    std::vector<ll> L, std::vector<ll> C, std::vector<int> U,
    std::vector<int> V, std::vector<ll> T) {

    vector<vector<ll>> c(N,vector<ll>(N,S));
    vector<vector<ll>> l(N,vector<ll>(N,S));
    for(int i=0;i<M;i++){
        c[A[i]][B[i]]=c[B[i]][A[i]]=C[i];
        l[A[i]][B[i]]=l[B[i]][A[i]]=L[i];
    }
    for(int i=0;i<N;i++){
        c[i][i]=l[i][i]=0;
    }
    auto dijisktra = [&](int p,int s){
        vector<ll> d(N,inf);
        vector<bool> used(N,false);
        d[s]=c[p][s];
        for(int _=0;_<N;_++){
            int u=-1;
            for(int i=0;i<N;i++) if(!used[i] && (u==-1 || d[i]<d[u])) u=i;
            used[u]=true;
            for(int v=0;v<N;v++){
                if(used[v] || c[u][v]>=S) continue;
                ll dd=d[u]+l[u][v];
                if(d[u]%S+l[u][v]>c[u][v]) dd+=S-d[u]%S;
                d[v]=min(d[v],dd);
            }
        }
        return d;
    };

    vector<vector<vector<ll>>> d(N,vector<vector<ll>>(N,vector<ll>(N,inf)));
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(c[i][j]<S) d[i][j]=dijisktra(i,j);

    vector<ll> res(Q,inf);
    for(int i=0;i<Q;i++){
        res[i]=d[U[i]][U[i]][V[i]]+(S-T[i])%S;
    }

    for(int st=0;st<N;st++){
        vector<pair<ll,int>> qq;
        for(int i=0;i<Q;i++) if(U[i]==st) qq.push_back({T[i],i});
        sort(qq.begin(),qq.end());
        vector<vector<pair<ll,int>>> ord(N);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++) if(i!=j && c[i][j]<S) ord[i].push_back({c[i][j]-l[i][j],j});
            sort(ord[i].rbegin(),ord[i].rend());
        }
        vector<int> pos(N,0);
        vector<ll> dd(N,inf);
        dd[st]=0;

        while(!qq.empty()){
            pair<ll,int> Max={-1,-1};
            for(int i=0;i<N;i++) if(pos[i]<(int)ord[i].size()) Max=max(Max,{ord[i][pos[i]].fi-dd[i],i});
            while(!qq.empty() && qq.back().fi>Max.fi){
                int id=qq.back().se;qq.pop_back();
                res[id]=min(res[id],dd[V[id]]);
                for(int i=0;i<N;i++){
                    if(dd[i]==inf) continue;
                    res[id]=min(res[id],S-T[id]+d[i][i][V[id]]);
                }
            }
            if(Max.fi==-1) break;
            int u=Max.se;
            int v=ord[u][pos[Max.se]++].se;
            for(int i=0;i<N;i++) if(d[u][v][i]<S) dd[i]=min(dd[i],d[u][v][i]-Max.fi);
        }
    }

    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    ll S;
    int n,m,q;cin >> n >> m >> S >> q;
    vector<int> A(m),B(m);
    vector<ll> C(m),L(m);
    for(int i=0;i<m;i++) cin >> A[i] >> B[i] >> L[i] >> C[i];
    vector<int> U(q),V(q);
    vector<ll> T(q);
    for(int i=0;i<q;i++) cin >> U[i] >> V[i] >> T[i];
    vector<ll> res=calculate_necessary_time(n,m,S,q,A,B,L,C,U,V,T);
    for(int i=0;i<q;i++) cout << res[i] << '\n';
}
