#include "secret.h"
#include<bits/stdc++.h>
using namespace std;
#define MAX_VALUE 1000000000
#define maxn 1005
int dist[maxn][maxn],a[maxn],n;
/*
int Secret(int X,int Y){
    return (X + 2 * (Y / 2) < MAX_VALUE) ? (X + 2 * (Y / 2)) : MAX_VALUE;
}
*/
void update(int l,int r){
    if(l>r) return;
    if(l==r){
        dist[l][r]=a[r];
        return;
    }
    int mid=(l+r)>>1;
    dist[mid][mid]=a[mid];
    if(l<mid) dist[mid][mid-1]=a[mid-1];
    for(int i=mid+1;i<=r;i++) dist[mid][i]=Secret(dist[mid][i-1],a[i]);
    for(int i=mid-2;i>=l;i--) dist[mid][i]=Secret(a[i],dist[mid][i+1]);
    update(l,mid-1);update(mid+1,r);
}
int get(int l,int r,int tl,int tr){
    int mid=(l+r)>>1;
    if(mid>=tl && mid<=tr){
        if(mid==tl) return dist[mid][tr];
        else return Secret(dist[mid][tl],dist[mid][tr]);
    }
    if(mid<tl) return get(mid+1,r,tl,tr);
    else return get(l,mid-1,tl,tr);
}
void Init(int N, int A[]){
    n=N;
    for(int i=0;i<N;i++) a[i+1]=A[i];
    update(1,n);
}
int Query(int L, int R) {
    L++;R++;
    return get(1,n,L,R);
}
/*
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    Init(n,a);
    int q;cin >> q;
    while(q--){
        int l,r;cin >> l >> r;
        cout << Query(l,r) << '\n';
    }
}
*/