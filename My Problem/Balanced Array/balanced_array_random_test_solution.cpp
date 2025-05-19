#include<bits/stdc++.h>
using namespace std;
const int maxa = 200005;
const int K = 1000;
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    vector<int> pre(maxa);
    
    int mx=0;
    long long res=0;
 
    vector<int> cnt(maxa);
    for(int i=1;i<=n;i++){
        mx=max(mx,pre[a[i]]);
        pre[a[i]]=i;
        res+=i-mx;
 
        int cur=0,num=0;
        for(int j=i;j>=max(1,i-K);j--){
            num+=!cnt[a[j]];
            cnt[a[j]]++;
            cur=max(cur,cnt[a[j]]);
            if(j<=mx && cur*num==i-j+1) res++;
        }
        for(int j=i;j>=max(1,i-K);j--) cnt[a[j]]=0;
    }
    cout << res << '\n';
}
