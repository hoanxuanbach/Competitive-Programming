#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1003443221;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    freopen("1002.txt","r",stdin);
    string ss;cin >> ss;
    vector<int> a;

    int X=0;
    for(char c:ss){
        if(c==',') a.push_back(X),X=0;
        else X=X*10+c-'0';
    }
    a.push_back(X);

    int n = (int)a.size()/2;
    vector<int> pos(n,-1);

    int T=n;
    vector<vector<int>> g(T);

    vector<int> A(8*n,-1),B(8*n,-1);
    auto new_node = [&](){
        g.emplace_back();
        return T++;
    };
    auto edge = [&](int u,int v){
        if(u!=-1 && v!=-1) g[u].push_back(v);
    };
    function<void(int,int,int,int)> update = [&](int l,int r,int id,int x){
        if(l==r){
            if(A[id]==a[x]) A[id]=B[id]=-1;
            else A[id]=B[id]=a[x];
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x);
        else update(mid+1,r,id<<1|1,x);

        if(A[id<<1]!=-1 || A[id<<1|1]!=-1) A[id]=new_node(),B[id]=new_node();
        else A[id]=B[id]=-1;

        edge(A[id],A[id<<1]);edge(A[id],A[id<<1|1]);
        edge(B[id<<1],B[id]);edge(B[id<<1|1],B[id]);
    };
    function<void(int,int,int,int,int)> add = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            edge(a[tr],A[id]);
            edge(B[id],a[tr]);
            return;
        }
        int mid=(l+r)>>1;
        add(l,mid,id<<1,tl,tr);add(mid+1,r,id<<1|1,tl,tr);
    };
    for(int i=0;i<2*n;i++){
        if(i%1000==0) cout << i << endl;
        if(pos[a[i]]==-1){
            pos[a[i]]=i;
            update(0,2*n-1,1,i);
        }
        else{
            add(0,2*n-1,1,pos[a[i]]+1,i);
            update(0,2*n-1,1,pos[a[i]]);
        }
    }
    
    int res=0;
    array<int,2> cnt={0,0};
    vector<int> col(T,-1);
    function<void(int)> dfs = [&](int u){
        if(u<n) cnt[col[u]]++;
        for(int v:g[u]){
            if(col[v]!=-1) continue;
            col[v]=col[u]^(v<n);
            dfs(v);
        }
    };
    for(int i=0;i<n;i++) if(col[i]==-1){

        col[i]=0;
        cnt={0,0};
        col[i]=0;dfs(i);
        res+=max(cnt[0],cnt[1]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
