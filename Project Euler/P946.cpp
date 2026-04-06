#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}


const int M = 1e6;
void solve(){
    int N;cin >> N;

    vector<int> f(M),P;
    for(int i=2;i<M;i++) if(!f[i]){
        P.push_back(i);
        for(int j=i;j<M;j+=i) f[j]=i;
    }
    int t=-1;

    int a=2,b=3,c=3,d=2,k=0,res=0;
    while(k<N){
        if(c!=0 && d!=0 && (a/c)==(b/d)){
            int x=a/c;
            a-=c*x;b-=d*x;
            swap(a,c),swap(b,d);
            res+=x;k++;
            if(k%10000==0) cout << k << endl;
        }
        else{
            int s=1;
            if(t<0 || P[t]==0){
                t++;
                assert(t<(int)P.size());
                s=2;
            }
            else P[t]--;
            swap(a,b);a+=b*s;
            swap(c,d);c+=d*s;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
