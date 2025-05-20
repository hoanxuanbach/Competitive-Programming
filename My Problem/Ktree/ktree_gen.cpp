#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int maxa = 1e9;
const int Max = 2e5;
 
vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
    int n = code.size() + 2;
    vector<int> degree(n, 1);
    for (int i : code)
        degree[i]++;
 
    int ptr = 0;
    while (degree[ptr] != 1)
        ptr++;
    int leaf = ptr;
 
    vector<pair<int, int>> edges;
    for (int v : code) {
        edges.emplace_back(leaf, v);
        if (--degree[v] == 1 && v < ptr) {
            leaf = v;
        } else {
            ptr++;
            while (degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n-1);
    return edges;
}
 
int n,q,dep[maxn],par[maxn][20];
int L[maxn],R[maxn],T,cn[maxn],c[maxn];
vector<int> edge[maxn];
 
void dfs(int u,int p){
    L[u]=++T;cn[T]=u;
    dep[u]=dep[p]+1;
    par[u][0]=p;
    for(int i=1;i<18;i++) par[u][i]=par[par[u][i-1]][i-1];
    for(int v:edge[u]) if(v!=p) dfs(v,u);
    R[u]=T;
}
 
int bit[2][maxn];
void update(int t,int x,int val){
    for(int i=x;i<=n;i+=(i&(-i))) bit[t][i]+=val;
}
int query(int t,int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[t][i];
    return res;
}
 
int main(int argc, char* argv[]){
	registerGen(argc, argv, 1);
	int min_n = atoi(argv[1]),max_n=atoi(argv[2]),subtask =atoi(argv[3]);
	n=rnd.next(min_n,max_n),q=rnd.next(min_n,max_n);
	int S=min(4,Max/n);
    if(!subtask) maxa = 4;
    cout << n << ' ' << q << '\n';
    for(int i=1;i<=n;i++){
        c[i]=rnd.next(0,1);
        cout << c[i] << " \n"[i==n];
    }
    vector<int> prufer_code(n-2,0);
    for(int i=0;i<n-2;i++) prufer_code[i]=rnd.next(0,n-1);
    vector<pair<int,int>> edges = pruefer_decode(prufer_code);
    for(auto [u,v]:edges){
        u++;v++;
        int w=rnd.next(-maxa*(subtask!=4),maxa);
        cout << u << ' ' << v << ' ' << w << '\n';
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++) update(c[i],L[i],1);
    for(int i=1;i<=q;i++){
        int id=rnd.next(1,2);
        if(!subtask) id=(i&1)+1;
        if(id==1){
            int u=rnd.next(1,n);
            cout << id << ' ' << u << '\n';
            update(c[u],L[u],-1);
            c[u]^=1;
            update(c[u],L[u],1);
        }
        else{
            int v=rnd.next(1,n),u=v,d=rnd.next(0,dep[v]-1);
            for(int j=0;j<18;j++) if(d>>j&1) u=par[u][j];
            int c0=query(0,R[u])-query(0,L[u]-1);
            int c1=query(1,R[u])-query(1,L[u]-1);
            int t=rnd.next(0,1);
            if(t==0 && !c0) t=1;
            else if(t==1 && !c1) t=0;
            int k=rnd.next(1,min(3,(t?c1:c0)));
            if(!subtask) k=min(3,(t?c1:c0));
            if(subtask!=3) cout << id << ' ' << u << ' ' << v << ' ' << t << ' ' << k << '\n';
            else cout << id << ' ' << u << ' ' << u << ' ' << t << ' ' << k << '\n';
        }
    }
}
/*
ktree_gen 5 5 1 >$
<#list 1..4 as i>
    ktree_gen 2000 2000 1 ${i} > $
</#list>
<#list 1..6 as i>
    ktree_gen 8000 8000 2 ${i} > $
</#list>
<#list 1..6 as i>
    ktree_gen 200000 200000 3${i} > $
</#list>
<#list 1..8 as i>
    ktree_gen 200000 200000 4 ${i} > $
</#list>
<#list 1..16 as i>
    ktree_gen 200000 200000 5 ${i} > $
</#list>
*/
