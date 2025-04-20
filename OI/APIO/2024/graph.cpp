#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5+5;
const int maxl = 20;

int n,a[maxn],lt[maxn][maxl],rt[maxn][maxl];
int Min[4*maxn],Max[4*maxn],p[maxn];

void build(int l,int r,int id){
    if(l==r){
        Min[id]=Max[id]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    Max[id]=max(Max[id<<1],Max[id<<1|1]);
    Min[id]=min(Min[id<<1],Min[id<<1|1]);
    //cout << "segtree " << l << ' ' << r << ' ' << Min[id] << ' ' << Max[id] << '\n';
}
int query(int l,int r,int id,int tl,int tr,int t){
    if(tr<l || r<tl) return (t?0:n);
    if(tl<=l && r<=tr) return (t?Max[id]:Min[id]);
    int mid=(l+r)>>1;
    int a=query(l,mid,id<<1,tl,tr,t),b=query(mid+1,r,id<<1|1,tl,tr,t);
    return (t?max(a,b):min(a,b));
}

void init_permutation(int N, std::vector<int> A) {
    n=N;
    for(int i=0;i<N;i++){
        a[i+1]=A[i];
        p[a[i+1]]=i+1;
    }
    build(1,n,1);
    vector<int> mx,mn;
    //cout << "lt: \n";
    for(int i=1;i<=n;i++){
        while(!mx.empty() && a[mx.back()]<a[i]) mx.pop_back();
        while(!mn.empty() && a[mn.back()]>a[i]) mn.pop_back();
        if(i>1){
            if(a[i-1]<a[i]){
                int pos=(mx.empty()?0:mx.back());
                lt[i][0]=*upper_bound(mn.begin(),mn.end(),pos);
            }
            else{
                int pos=(mn.empty()?0:mn.back());
                lt[i][0]=*upper_bound(mx.begin(),mx.end(),pos);
            }
        }
        else lt[i][0]=0;
        mn.push_back(i);
        mx.push_back(i);
        //cout << lt[i][0] << ' ';
    }
    //cout << '\n';
    mn.clear();mx.clear();
    rt[n+1][0]=n+1;
    //cout << "rt: \n";
    for(int i=n;i>=1;i--){
        while(!mx.empty() && a[mx.back()]<a[i]) mx.pop_back();
        while(!mn.empty() && a[mn.back()]>a[i]) mn.pop_back();
        if(i<n){
            if(a[i+1]<a[i]){
                int pos=(mx.empty()?n+1:mx.back());
                rt[i][0]=*upper_bound(mn.begin(),mn.end(),pos,greater<int>());
            }
            else{
                int pos=(mn.empty()?n+1:mn.back());
                rt[i][0]=*upper_bound(mx.begin(),mx.end(),pos,greater<int>());
            }
        }
        else rt[i][0]=n+1;
        mn.push_back(i);
        mx.push_back(i);
        //cout << rt[i][0] << ' ';
    }
    //cout << '\n';
    for(int i=1;i<=18;i++){
        for(int j=1;j<=n+1;j++) rt[j][i]=rt[rt[j][i-1]][i-1];
        for(int j=0;j<=n;j++) lt[j][i]=lt[lt[j][i-1]][i-1];
    }
}

int calc_f(int l, int r) {
    l++;r++;
    if(l==r) return 0;
    int mx=p[query(1,n,1,l,r,1)];
    int mn=p[query(1,n,1,l,r,0)];
    if(mn>mx) swap(mn,mx);
    //cout << "value " << mn << ' ' << mx << '\n';
    int cnt=1;
    for(int i=18;i>=0;i--){
        if(rt[l][i]<=mn){
            cnt+=(1<<i);
            l=rt[l][i];
        }
        if(lt[r][i]>=mx){
            cnt+=(1<<i);
            r=lt[r][i];
        }
    }
    return cnt;
}
