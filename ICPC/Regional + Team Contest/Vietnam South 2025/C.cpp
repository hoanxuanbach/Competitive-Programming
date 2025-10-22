#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5+5;
const int LG = 20;

struct node{
    int nxt[26],suf=0,ex=0,len=0;
    ll num=0;
    node(){memset(nxt,0,sizeof(nxt));}
};
struct Aho_Corasick{
    int k=0;
    node T[maxn];
    vector<int> edge[maxn];
    //aho(){}
    void add_string(string &s,int val){
        int u=0;
        for(char c:s){
            int a=c-'a';
            if(T[u].nxt[a]==0){
                T[u].nxt[a]=++k;
                T[k].len=T[u].len+1;
            }
            u=T[u].nxt[a];
        }
        T[u].num+=val;
    }
    void bfs(){
        queue<int> q;q.push(0);
        while(!q.empty()){
            int u=q.front(),pre=T[u].suf;q.pop();
            for(int i=0;i<26;i++){
                if(T[u].nxt[i]==0) T[u].nxt[i]=T[pre].nxt[i];
                else{
                    int v=T[u].nxt[i];
                    q.push(v);T[v].suf=(u!=0)?T[pre].nxt[i]:0;
                    edge[T[v].suf].push_back(v);
                    //cout << T[v].suf << ' ' << v << '\n';
                }
            }
        }
    }

    int lst=0;
    void dfs(int u){
        T[u].ex=lst;

        int pre=lst;

        if(T[u].num) lst=u;
        for(int v:edge[u]) dfs(v);
        
        lst=pre;
    }
    void build(){bfs();dfs(0);}
}aho;

void solve(){
    int n,q;cin >> n >> q;
    
    vector<string> S(n);
    vector<int> cost(n);
    for(int i=0;i<n;i++){
        cin >> S[i] >> cost[i];
        aho.add_string(S[i],cost[i]);
    }
    aho.build();

    string T;cin >> T;
    int m=(int)T.size();

    vector<int> pos(m+1,0);
    for(int i=0;i<m;i++) pos[i+1]=aho.T[pos[i]].nxt[T[i]-'a'];

    vector<vector<pair<int,int>>> f(m+1);
    for(int i=1;i<=m;i++){
        int x=pos[i];
        while(x){
            if(aho.T[x].num){
                f[i].push_back({i-aho.T[x].len+1,aho.T[x].num});
                //cout << i << ' ' << x  << ' ' << i-aho.T[x].len+1 << ' ' << aho.T[x].num << '\n';
            }
            x=aho.T[x].ex;
        }
    }

    vector<vector<pair<int,int>>> qq(m+1);
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        l=max(l,1);r=min(r,m);
        qq[r].push_back({l,i});
    }

    vector<ll> res(q+1);

    vector<ll> bit(m+1);
    auto update = [&](int x,int val){
        for(int i=x;i<=m;i+=(i&(-i))) bit[i]+=val;
    };
    auto query = [&](int x){
        ll sum=0;
        for(int i=x;i>=1;i-=(i&(-i))) sum+=bit[i];
        return sum;
    };
    
    for(int i=1;i<=m;i++){
        for(auto [l,val]:f[i]) update(m-l+1,val);
        for(auto [l,id]:qq[i]) res[id]=query(m-l+1);
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    int test=1;//cin >> test;
    while(test--) solve();
}