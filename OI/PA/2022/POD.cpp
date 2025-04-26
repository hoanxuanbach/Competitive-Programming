#include<bits/stdc++.h>
using namespace std;
const int maxn=500005;
const int inf=2e9;
int n,k,a[maxn];
bool check[maxn],ok=true;
void solve(){
    for(int i=1;i<n;i++){
        if(a[i]>=a[i+1]){
            check[i-1]=1;check[i]=1;check[i+1]=1;
            return;
        }
    }
    ok=false;
}
int Max[maxn];
void solve2(){
    for(int i=n;i>=1;i--) Max[i]=max(Max[i+1],a[i]);
    int Min=inf;
    for(int i=1;i<n;i++){
        Min=min(Min,a[i]);
        if(Min>=Max[i+1]){
            check[i]=1;
            return;
        }
    }
    ok=false;
}
void solve3(){
    int pos=1;
    for(int i=2;i<=n;i++){
        if(a[i]>a[pos]) pos=i;
    }
    if(pos==n){
        int Min=inf;
        for(int i=1;i<n-1;i++){
            Min=min(Min,a[i]);
            if(a[i+1]<=Min){
                check[i]=1;
                check[i+1]=1;
                return;
            }
        }
        ok=false;
    }
    else{
        check[pos]=1;
        check[pos-1]=1;
    }
}
signed main(){
    //freopen("POD.INP","r",stdin);
    //freopen("POD.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    if(k>=4) solve();
    else if(k==3) solve3();
    else solve2();
    if(!ok) cout << "NIE\n";
    else{
        k--;
        for(int i=1;i<n;i++){
            if(check[i]) k--;
        }
        for(int i=1;i<n;i++){
            if(k && !check[i]){k--;check[i]=1;}
        }
        cout << "TAK\n";
        for(int i=1;i<n;i++){
            if(check[i]) cout << i << ' ';
        }
        cout << '\n';
    }
}
