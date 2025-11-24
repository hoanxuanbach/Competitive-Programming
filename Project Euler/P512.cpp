#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;cin >> n;
    vector<int> p(n),f(n);f[1]=1;

    long long res=1;
    for(int i=2;i<n;i++) if(i&1){
        if(!p[i]){
            for(int x=i;x<n;x+=i) p[x]=i;
        }
        int x=p[i];
        if((i/x)%x==0) f[i]=f[i/x]*x;
        else f[i]=f[i/x]*(x-1);
        res+=f[i];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
