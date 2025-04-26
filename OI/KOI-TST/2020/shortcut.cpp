#include"shortcut.h"
#include<bits/stdc++.h>
using namespace std;
using i32=int;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 250005;
int N,D[maxn];
vector<int> X,Y;

int d(int a,int b){
    return abs(X[a]-X[b])+abs(Y[a]-Y[b]);
}
int d2(int l,int r){
    if(l>r) swap(l,r);
    return D[r]-D[l];
}

int nxt[maxn];
int L1[maxn],R1[maxn],R2[maxn];

bool check(int L){
    int p=0;
    for(int i=0;i<N;i++){
        while(p<N && d2(i,p)<=L) p++;
        nxt[i]=p;
    }
    if(nxt[0]==N) return true;

    int T=nxt[0];
    for(int i=T;i<N;i++) R1[i]=i;
    p=T;
    for(int i=T-1;i>=0;i--){
        while(p<N && d2(0,i)+d(i,p)+d2(T,p)<=L) p++;
        R1[i]=p;
    }

    T=N-1;
    while(d2(T,N-1)<=L) T--;
    for(int i=0;i<=T;i++) L1[i]=i;
    p=T;
    for(int i=T+1;i<N;i++){
        while(p>=0 && d2(i,N-1)+d(i,p)+d2(T,p)<=L) p--;
        L1[i]=p;
    }

    p=0;
    for(int i=0;i<N;i++){
        p=max(p,i);
        while(p<N && d2(0,i)+d(i,p)+d2(p,N-1)>L) p++;
        R2[i]=p;
    }

    p=0;
    int pp=0;
    deque<pii> dq;
    for(int i=0;i<N;i++){
        p=max(p,i);
        while(p<N && (dq.empty() || d(i,p)+d2(i,p)-dq.front().fi<=L)){
            p++;
            if(p==N) break;
            while(pp<N && nxt[pp]<=p){
                int val=d2(pp,nxt[pp]);
                while(!dq.empty() && dq.back().fi>=val) dq.pop_back();
                dq.push_back({val,pp++});
            }
        }
        R1[i]=min(R1[i],p);
        if(!dq.empty() && dq.front().se==i) dq.pop_front();
    }
    for(int i=0;i<N;i++){
        if(R2[i]<R1[i]){
            int x=R1[i]-1;
            if(L1[x]<i) return true;
        }
    }
    return false;
}

int shortcut(i32 _N, vector<int> _X, vector<int> _Y) {
    N=_N;X=_X;Y=_Y;
    for(int i=1;i<N;i++) D[i]=D[i-1]+d(i-1,i);
    int l=0,r=D[N-1],res=D[N-1];
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
#undef int