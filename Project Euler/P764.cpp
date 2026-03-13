#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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

void solve(){
    int L=60;
    vector<int> pw(L+1,1);
    for(int i=1;i<=L;i++) pw[i]=pw[i-1]*2;

    int N;cin >> N;
    int S=sqrtl(N);
    vector<int> f(S+1);
    for(int i=2;i<=S;i++) if(!f[i]){
        for(int j=i;j<=S;j+=i) f[j]=i;
    }
    int res=0;
    for(int y=1;y<=S;y++){
        if(y%10000==0) cout << y << endl;
        int x=y,k=0;
        while(x%2==0) x/=2,k++;
        vector<int> P;
        bool ok=true;
        while(x>1){
            int j=f[x],d=1;
            while(x%j==0) x/=j,d*=j;
            d*=d;
            if(d>inf/d){
                ok=false;
                break;
            }
            P.push_back(d*d);
        }
        if(!ok) continue;
        int sz=(int)P.size();
        
        int d=1;
        for(int i=0;i<=min(4*k,L);i++) if(4*k-i<=L){
            for(int mask=0;mask<(1<<sz);mask++){
                int a=pw[i],b=pw[4*k-i];
                bool ok=true;
                for(int j=0;j<sz;j++){
                    if(mask>>j&1){
                        if(a>inf/P[j]){
                            ok=false;
                            break;
                        }
                        a*=P[j];
                    }
                    else{
                        if(b>inf/P[j]){
                            ok=false;
                            break;
                        }
                        b*=P[j];
                    }
                }
                
                if(!ok) continue;
                if(a>=b) continue;
                if((a+b)&1) continue;
                a=(a+b)/2,b-=a;
                if(b%4!=0) continue;
                b/=4;

                bool g=(a%2==0 && b%2==0 && y%2==0);
                if(a<=N && !g){
                    res=(res+a+b+y)%mod;
                }
            }
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
