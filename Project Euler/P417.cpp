#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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

void solve(){
    int N;cin >> N;N++;
    vector<int> f(N);
    for(int i=2;i<N;i++) if(!f[i]){
        for(int j=i;j<N;j+=i) f[j]=i;
    }
    
    vector<int> p(N);
    cout << "first" << endl;
    for(int x=1;x<N;x++){
        if(x%10000==0) cout << x << endl;
        for(int i=x;i+1<N;i+=x) if(f[i+1]==(i+1) && (i+1)!=2 && (i+1)!=5 && !p[i+1]){
            if(power(10,x,i+1)==1) p[i+1]=x;
        }
    }
    cout << "second" << endl;
    for(int x=2;x<N;x++) if(x!=2 && x!=5 && f[x]==x){
        int k=x;
        while(k*x<N && power(10,p[x],k*x)==1){
            k*=x;
            p[k]=p[x];
        }
        while(k*x<N){
            p[k*x]=p[k]*x;
            k*=x;
        }
    }

    cout << "third" << endl;
    int res=0;
    for(int i=3;i<N;i++){
        if(!p[i]){
            
            int x=i;
            while(x%2==0) x/=2;
            while(x%5==0) x/=5;
            if(x!=i){
                p[i]=p[x];
                continue;
            }

            int j=f[x],k=1;
            while(x%j==0) x/=j,k*=j;

            int a=p[x],b=p[k];
            p[i]=a*b/__gcd(a,b);
        }
    }
    for(int i=3;i<N;i++) res+=p[i];
    cout << res << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
