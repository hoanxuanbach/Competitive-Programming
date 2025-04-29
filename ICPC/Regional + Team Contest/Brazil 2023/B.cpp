#include<bits/stdc++.h>
using namespace std;
#define int long long
#define piii pair<pair<int,int>,int>
const int mod=1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int l1,r1,l2,r2,l3,r3;
map<piii,int> mp;
int solve(int x,int y,int z,int k=29){
    if(k==-1) return 1;
    if(mp.find({{x,y},z})!=mp.end()) return mp[{{x,y},z}];
    int x1=x,y1=y,z1=z,res=0;
    if(x&(1<<k)) x1=(1<<k)-1;
    if(y&(1<<k)) y1=(1<<k)-1;
    if(z&(1<<k)) z1=(1<<k)-1;
    res=(res+solve(x1,y1,z1,k-1))%mod;
    if((x&(1<<k)) && (y&(1<<k))) res=(res+solve(x-(1<<k),y-(1<<k),z1,k-1))%mod;
    if((x&(1<<k)) && (z&(1<<k))) res=(res+solve(x-(1<<k),y1,z-(1<<k),k-1))%mod;
    if((y&(1<<k)) && (z&(1<<k))) res=(res+solve(x1,y-(1<<k),z-(1<<k),k-1))%mod;
    return mp[{{x,y},z}]=res;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> l1 >> r1 >> l2 >> r2 >> l3 >> r3;
    int ans=(solve(r1,r2,r3)-solve(l1-1,r2,r3)-solve(r1,l2-1,r3)-solve(r1,r2,l3-1)+solve(l1-1,l2-1,r3)+solve(l1-1,r2,l3-1)+solve(r1,l2-1,l3-1)-solve(l1-1,l2-1,l3-1))%mod;
    ans=(ans+mod)%mod;
    int mul=(r1-l1+1)*(r2-l2+1)%mod*(r3-l3+1)%mod;
    ans=ans*power(mul,mod-2)%mod;
    ans=(1-ans+mod)%mod;
    cout << ans << '\n';
}
