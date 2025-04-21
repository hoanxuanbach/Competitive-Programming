#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=(a*a)%mod;n>>=1;
    }
    return res;
}
int n,m,k;
map<int,int[2]> h,w;
bool check[2];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    int ans=0,res1=power(2,n),res2=power(2,m);
    for(int i=1;i<=k;i++){
        char ch;cin >> ch;
        int x,y,c=(ch=='+')+1;cin >> x >> y;
        if(h[x][y%2]!=0 && h[x][y%2]!=c) res1=0;
        if(w[y][x%2]!=0 && w[y][x%2]!=c) res2=0;
        h[x][y%2]=c;w[y][x%2]=c;
    }
    for(auto it:h){
        if(it.second[0]==it.second[1]) res1=0;
        else res1=(res1*power(2,mod-2))%mod;
    }
    for(auto it:w){
        if(it.second[0]==it.second[1]) res2=0;
        else res2=(res2*power(2,mod-2))%mod;
    }
    check[0]=check[1]=true;
    for(auto it:h){
        if(it.second[0]!=0) check[(it.first&1)^(it.second[0]-1)^1]=false;
        if(it.second[1]!=0) check[(it.first&1)^(it.second[1]-1)]=false;
    }
    if(res1==0) check[0]=check[1]=false;
    ans=(res1+res2)%mod;
    ans=(ans+mod-check[0]-check[1])%mod;
    cout << ans << '\n';
}
