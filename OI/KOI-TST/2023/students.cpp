#include <bits/stdc++.h>
using namespace std;
const int maxn = 250005;
const int inf = 1e9;
#define pii pair<int,int>
#define fi first

vector<int> lt[maxn],rt[maxn];
int l[2][maxn],r[2][maxn];
int dl[maxn][2],dr[maxn][2];

namespace Segtree{
    int L[4*maxn],R[4*maxn];
    void build(int l,int r,int id){
        L[id]=0;R[id]=inf;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    void update(int l,int r,int id,int p,int tl,int tr){
        if(l==r){
            L[id]=tl;R[id]=tr;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,tl,tr);
        else update(mid+1,r,id<<1|1,p,tl,tr);
        L[id]=max(L[id<<1],L[id<<1|1]);
        R[id]=min(R[id<<1],R[id<<1|1]);
    }
}

pair<int,vector<int>> complaint(int n, vector<int> L, vector<int> R) {
    int m=(int)L.size();
    for(int i=0;i<m;i++){
        L[i]++;R[i]++;
        lt[L[i]].push_back(i);
        rt[R[i]].push_back(i);
    }
    {
        int Max=0;
        for(int i=1;i<=n;i++){
            for(int id:rt[i-1]) Max=max(Max,L[id]);
            l[0][i]=Max;
        }
        int Min=n+1;
        for(int i=n;i>=1;i--){
            for(int id:lt[i+1]) Min=min(Min,R[id]);
            r[0][i]=Min;
        }
    }
    {
        int pos=0;
        Segtree::build(1,m,1);
        for(int i=1;i<=n;i++){
            for(int id:rt[i-1]) if(L[id]>pos) Segtree::update(1,m,1,id+1,L[id],R[id]);
            while(Segtree::L[1]>Segtree::R[1]){
                pos++;
                for(int id:lt[pos]) if(R[id]<i) Segtree::update(1,m,1,id+1,0,inf);
            }
            l[1][i]=pos;
        }
        Segtree::build(1,m,1);
        pos=n+1;
        for(int i=n;i>=1;i--){
            for(int id:lt[i+1]) if(R[id]<pos) Segtree::update(1,m,1,id+1,L[id],R[id]);
            while(Segtree::L[1]>Segtree::R[1]){
                pos--;
                for(int id:rt[pos]) if(i<L[id]) Segtree::update(1,m,1,id+1,0,inf);
            }
            r[1][i]=pos;
        }
    }
    {
        /*
        for(int i=1;i<=n;i++){
            cout << l[0][i] << ' ' << l[1][i] << ' ' << r[0][i] << ' ' << r[1][i] << '\n';
        }
        */
        for(int i=1;i<=n;i++){
            dl[i][0]=dl[i][1]=inf;
            for(int j=0;j<2;j++) for(int k=0;k<=1-j;k++){
                dl[i][j|k]=min(dl[i][j|k],dl[l[k][i]][j]+1);
            }
        }
        for(int i=n;i>=1;i--){
            dr[i][0]=dr[i][1]=inf;
            for(int j=0;j<2;j++) for(int k=0;k<=1-j;k++){
                dr[i][j|k]=min(dr[i][j|k],dr[r[k][i]][j]+1);
            }
        }
    }
    int cnt=n+1;
    vector<int> res;
    for(int i=1;i<=n;i++){
        if(l[0][i]==0 && r[0][i]==n+1){
            if(cnt>0) cnt=0,res={i-1};
            else if(cnt==0) res.push_back(i-1);
        }
    }
    for(int i=1;i<=n;i++){
        int Min=inf;
        for(int j=0;j<=1;j++) for(int k=0;k<=1-j;k++) Min=min(Min,dl[i][j]+dr[i][k]-1);
        if(cnt>Min) cnt=Min,res={i-1};
        else if(Min==cnt) res.push_back(i-1);
    }
    return {cnt+1,res};
}