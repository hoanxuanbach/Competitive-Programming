#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;

struct node{
    int mx=0,sum=0;
    node(int a=0,int b=0){
        mx=a,sum=b;
    }
    friend node operator+(node a,node b){
        node res;
        res.mx=max(a.mx,b.mx-a.sum);
        res.sum=a.sum+b.sum;
        return res;
    }
};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];

    vector<node> pre(n+1),suf(n+1);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+node(a[i-1],b[i-1]);
    for(int i=n-1;i>=0;i--) suf[i]=node(a[i],b[i])+suf[i+1];
    
    int ans=inf;
    for(int i=0;i<n;i++){
        node res=suf[i]+pre[i];
        ans=min(ans,res.mx);
    }
    cout << ans << '\n';
}