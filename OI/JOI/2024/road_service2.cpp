#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
const int maxl = 25;
const int inf = 1e9;
#define pii array<int,2>

int par[2*maxn],lt[2*maxn],rt[2*maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u!=v) par[v]=u;
}

int L,R,n,m,q,sum[maxn],nxt[maxn],pre[maxn];
pii S[maxn][maxl];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q;
    for(int i=0;i<n*m;i++) par[i]=i,lt[i]=n,rt[i]=0;
    for(int i=0;i<n;i++) for(int j=0;j<m-1;j++){
        char C;cin >> C;
        if(C=='1') unions(i*m+j,i*m+j+1);
    }
    for(int i=0;i<n-1;i++) for(int j=0;j<m;j++){
        char C;cin >> C;
        if(C=='1') unions(i*m+j,(i+1)*m+j);
    }
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        int p=findpar(i*m+j);
        lt[p]=min(lt[p],i);
        rt[p]=max(rt[p],i);
    }
    for(int i=0;i<n*m;i++){
        if(lt[i]>rt[i]) continue;
        nxt[lt[i]]=max(nxt[lt[i]],rt[i]);
        //cout << "range " << lt[i] << ' ' << rt[i] << '\n';
    }
    for(int i=1;i<n;i++) nxt[i]=max({i,nxt[i],nxt[i-1]});
    for(int i=1;i<n;i++){
        if(nxt[i-1]<=i-1) sum[i]++;
        sum[i]+=sum[i-1];
    }
    for(int i=0;i<n;i++){
        int x;cin >> x;
        pre[i]=(i?pre[i-1]:-1);
        if(x==1) pre[i]=i;
    }
    for(int i=0;i<n;i++) S[i][0]={i,max(i,pre[nxt[i]])};
    auto g = [&](int i,int j,int k){
        if(i<0) return -1;
        return S[i][j][k];
    };
    auto up = [&](int x){
        if(x==-1) return -1;
        else return max(x,nxt[x]);
    };
    for(int j=1;j<20;j++){
        for(int i=0;i<n;i++){
            S[i][j][0]=max(g(g(i,j-1,0),j-1,1),g(g(i,j-1,1),j-1,0));
            S[i][j][1]=max({g(g(i,j-1,1),j-1,1),g(i,j,0),g(i,j,1),g(up(g(i,j-1,0)),j-1,0)});
        }
    }
    while(q--){
        int sz;cin >> sz;
        vector<int> cc;
        for(int i=0;i<sz;i++){
            int x,y;cin >> x >> y;x--;y--;
            x=findpar(x*m+y);
            cc.push_back(x);
        }
        sort(cc.begin(),cc.end());
        cc.erase(unique(cc.begin(),cc.end()),cc.end());
        if((int)cc.size()==1){
            cout << 0 << '\n';
            continue;
        }
        vector<pii> a;
        L=n,R=0;
        for(int x:cc){
            L=min(L,rt[x]);
            R=max(R,lt[x]);
            a.push_back({lt[x],rt[x]});
        }
        if(L<R && sum[R]-sum[L]>0){
            cout << -1 << '\n';
            continue;
        }
        sort(a.begin(),a.end(),[&](pii x,pii y){
            return pii{x[0],-x[1]}<pii{y[0],-y[1]};
        });
        {
            vector<pii> st;
            for(pii x:a){
                while(!st.empty() && st.back()[1]>=x[1]) st.pop_back();
                st.push_back(x);
            }
            a=st;
        }
        auto f = [&](int p){
            if(p==-1) return -1;
            int pos=upper_bound(a.begin(),a.end(),pii{p,inf})-a.begin();
            if(pos>0 && p<=a[pos-1][1]) return -1;
            return pos;
        };
        int ans=1;
        pii dp={-1,pre[L]};
        while(dp[1]<R){
            int t0=f(dp[0]),t1=f(dp[1]);
            //cout << '*' << t0 << ' ' << t1 << '\n';
            if(t0>=0 && t1>=0){
                auto get = [&](pii a,int i){
                    int a0=g(a[0],i,1),a1=g(a[1],i,0);
                    int b0=g(up(a[0]),i,0),b1=g(a[1],i,1);
                    return pii{max(a0,a1),max({a0,a1,b0,b1})};
                };
                int mx=R,pos=t1;
                if(pos<(int)a.size()) mx=min(mx,a[pos][0]);
                for(int i=19;i>=0;i--){
                    auto [x,y]=get(dp,i);
                    if(x<mx && y<mx) dp={x,y},ans+=(1<<i);
                }
            }
            if(dp[1]>=R) break;
            auto jmp = [&](int x){
                if(x==-1) return L;
                int res=nxt[x];
                int pos=upper_bound(a.begin(),a.end(),pii{x,inf})-a.begin();
                if(pos<(int)a.size()) res=min(res,a[pos][1]);
                return res;
            };
            pii ndp{dp[1],-1};
            ndp[1]=max({pre[jmp(dp[1])],jmp(dp[0]),dp[1]});
            ans++;dp=ndp;
            //cout << '*' << dp[0] << ' ' << dp[1] << '\n';
        }
        cout << ans << '\n';
    }
}
