#include <bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
const int maxn = 1e5+5;
const int inf = 1e18;

vector<int> edge[maxn];
int N,K,W[maxn],T;
int cc[2][2][2];

struct node{
    int val[2][2][2],l=-1,r=-1,w=0;
    node(){
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) val[i][j][k]=inf;
    }
    void add(node &x){
        if(l==-1){
            l=x.l;r=x.r;
            for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++){
                val[i^1][j][k]=min(val[i^1][j][k],x.val[i][j][k]);
                val[i][j][k]=min(val[i][j][k],x.val[i][j][k]+x.w);
            }
        }
        else{
            for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) cc[i][j][k]=inf;
            for(int a0=0;a0<2;a0++){
                for(int a1=0;a1<2;a1++){
                    for(int l0=0;l0<2;l0++) for(int r0=0;r0<2;r0++) for(int l1=0;l1<2;l1++) for(int r1=0;r1<2;r1++){
                        cc[a0][l0][r1]=min(cc[a0][l0][r1],val[a0][l0][r0]+x.val[a1][l1][r1]+(a0^a1^1)*x.w+(r0^l1^1)*W[r]);
                    }
                }
            }
            r=x.r;
            for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++) val[i][j][k]=cc[i][j][k];
        }
    }
}dp[maxn];

int place_police(vector<i32> P, vector<int> _C, vector<int> _W){
    N=(int)_C.size()+1;K=(int)_W.size();
    for(int i=0;i<K;i++) W[i]=_W[i];
    for(int i=0;i<N-1;i++){
        edge[P[i]].push_back(i+1);
        dp[i+1].w=_C[i];
    }
    for(int i=0;i<N;i++) if(edge[i].empty()){
        dp[i].l=dp[i].r=T++;
        dp[i].val[0][0][0]=dp[i].val[1][1][1]=0;
        //cout << i << ' ' << T-1 << '\n';
    }
    //cout << K << '\n';
    for(int i=N-1;i>=0;i--){
        for(int v:edge[i]) dp[i].add(dp[v]);
    }
    int res=inf;
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++){
        res=min(res,dp[0].val[i][j][k]+(j^k^1)*W[K-1]);
        //cout << i << ' ' << j << ' ' << k << ' ' << dp[0].val[i][j][k] << '\n';
    }
    return res;
}

#undef int