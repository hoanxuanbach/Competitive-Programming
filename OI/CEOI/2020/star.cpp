#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5+5;
const int mod = 1e9+7;
 
struct node{
    int c=0,sz=0;
    array<int,2> a;
    node(){a={0,0};}
    friend node operator+(node x,node y){
        node res;
        res.c=x.c|y.c;
        res.sz=x.sz+y.sz;
        for(int i=0;i<=1;i++){
            int ni=i|y.c;
            if(ni){
                (res.a[0]+=(i?x.a[0]:x.sz-x.a[0]))%=mod;
                (res.a[1]+=(i?x.a[1]:x.sz-x.a[1]))%=mod;
            }
 
            ni=x.c|i;
            if(ni){
                (res.a[0]+=(i?y.a[0]:y.sz-y.a[0]))%=mod;
                (res.a[1]+=(i?y.a[1]:y.sz-y.a[1]))%=mod;
            }
        }      
        return res;
    }
    void add(){
        sz++;
        if(c) (a[0]+=1)%=mod,(a[1]+=1)%=mod;
        else (a[0]+=1)%=mod;
    }
}dp[maxn],sum[maxn];
 
int n;
ll D;
vector<int> edge[maxn];
node rev(node cur){
    node res=cur;
    res.c^=1;
    res.a[0]=res.sz-res.a[0];
    res.a[1]=res.sz-res.a[1];
    return res;
}
 
void dfs(int u,int p){
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
        sum[u]=sum[u]+rev(dp[v]);
    }
    dp[u]=sum[u];dp[u].add();
}
 
node val[maxn];
void redfs(int u,int p){
    sum[u]=sum[u]+rev(val[u]);sum[u].add();
 
    node cur;cur=cur+rev(val[u]);
    for(int v:edge[u]){
        if(v==p) continue;
        val[v]=cur;cur=cur+rev(dp[v]);
    }
    cur=node();
    reverse(edge[u].begin(),edge[u].end());
    for(int v:edge[u]){
        if(v==p) continue;
        val[v]=val[v]+cur;
        cur=cur+rev(dp[v]);
        val[v].add();
        redfs(v,u);
    }
}
 
array<int,2> mul0(array<int,2> val,array<array<int,2>,2> ss){
    array<int,2> res={0,0};
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) (res[j]+=1LL*val[i]*ss[i][j]%mod)%=mod;
    return res;
}
array<array<int,2>,2> mul1(array<array<int,2>,2> val,array<array<int,2>,2> ss){
    array<array<int,2>,2> res={0,0};
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) for(int k=0;k<=1;k++) (res[i][j]+=1LL*val[i][k]*ss[k][j]%mod)%=mod;
    return res;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> D;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    val[1].c=1;
    redfs(1,0);
    array<array<int,2>,2> ss;
    ss[0]=ss[1]={0,0};
    for(int u=1;u<=n;u++){
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) (ss[j][i]+=(i?sum[u].a[j]:sum[u].sz-sum[u].a[j]))%=mod;
    }
    array<int,2> val={0,0};
    for(int u=1;u<=n;u++) val[sum[u].c]++;
    D--;
    while(D){
        if(D&1) val=mul0(val,ss);
        ss=mul1(ss,ss);D>>=1;
    }
    cout << (1LL*sum[1].a[0]*val[0]+1LL*sum[1].a[1]*val[1])%mod << '\n';
}