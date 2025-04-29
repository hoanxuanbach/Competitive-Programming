#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 100005
const int mod=1e9+7;
vector<int> d[maxn];
int a[maxn],phi[maxn],n,pr[maxn],ans,num[maxn];
bool check[maxn];
void setphi(){
    phi[1]=1;
    for(int i=2;i<=100000;i++){
        if(pr[i]==0){
            for(int j=i;j<=100000;j+=i) pr[j]=i;
        }
        int d=pr[i];
        if(i%(d*d)==0) phi[i]=phi[i/d]*d;
        else phi[i]=phi[i/d]*(d-1);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;setphi();
    for(int i=1;i<=n;i++){
        cin >> a[i];
        for(int j=1;j<=sqrt(a[i]);j++){
            if(a[i]%j==0){
                d[i].push_back(j);
                if(j*j!=a[i]) d[i].push_back(a[i]/j);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            for(int v:d[j]) num[v]++;
        }
        int res=0;
        for(int j=i;j<=n;j+=i){
            for(int v:d[j]){
                if(check[v]) continue;
                res=(res+(phi[v]*((num[v]*num[v])%mod))%mod)%mod;
                check[v]=true;num[v]=0;
            }
        }
        for(int j=i;j<=n;j+=i){
            for(int v:d[j]) check[v]=false;
        }
        ans=(ans+phi[i]*res)%mod;
    }
    cout << ans << '\n';
}
