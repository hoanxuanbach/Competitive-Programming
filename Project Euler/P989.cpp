#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+9;
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

const int T = 383008016;
const int invT = power(T,mod-2);
const int TA = (T+1+mod)/2;
const int TB = (mod+1-T)/2;

void solve(){
    int N;cin >> N;

    int S=sqrtl(N);
    
    vector<int> p(S+1);
    for(int i=2;i<=S;i++) if(!p[i]) for(int j=i;j<=S;j+=i) p[j]=i;

    vector<int> h(S+1,1);
    for(int i=2;i<=S;i++){
        if((i/p[i])%p[i]==0) h[i]=0;
        else h[i]=-h[i/p[i]];
    }

    auto get = [&](int n,int x){
        int s=sqrtl(n);
        int fx=power(x,mod-2);
        
        
        int ret=0;
        {
            int L=1,R=0;
            int fL=x,fR=1,dL=x*x%mod*x%mod,dR=x,X=0;

            int mul=power(fx,5),dd=mul,dx=mul;
            for(int t=1;;t++){
                int l=3*t,r=sqrtl(n+5*t*t);
                if(l>r) break;
                
                while(R<r){
                    R++;
                    fR=fR*dR%mod;
                    dR=dR*x%mod*x%mod;
                    X=(X+fR)%mod;
                }
                while(L<l){
                    X=(X-fL+mod)%mod;
                    fL=fL*dL%mod;
                    dL=dL*x%mod*x%mod;
                    L++;
                }
                ret=(ret+X*mul)%mod;     
                
                dd=dd*dx%mod*dx%mod;
                mul=mul*dd%mod;
            }
        }
        {
            int L=1,R=0;
            int fL=x*x%mod,fR=1,dR=x*x%mod,dL=dR*dR%mod,X=0;

            int mul=fx,dx=power(fx,5),dd=1;
            for(int t=0;;t++){
                int l=3*t+1,r=(sqrtl(4*n+20*t*t+20*t+5)-1)/2;
                if(l>r) break;

                //for(int m=l;m<=r;m++) base=(base+power(x,m*(m+1)-5*t*(t+1)-1))%mod;

                while(R<r){
                    R++;
                    fR=fR*dR%mod;
                    dR=dR*x%mod*x%mod;
                    X=(X+fR)%mod;
                }
                while(L<l){
                    X=(X-fL+mod)%mod;
                    fL=fL*dL%mod;
                    dL=dL*x%mod*x%mod;
                    L++;
                }
                ret=(ret+X*mul)%mod;
                dd=dd*dx%mod*dx%mod;
                mul=mul*dd%mod;
            }
        }
        return ret;
    };

    int res=0,cnt=0;
    for(int i=1;i<=S;i++){
        if(!h[i]) continue;

        cnt++;
        if(cnt%100==0) cout << i << endl;

        int A=power(TA,i*i);
        int B=power(TB,i*i);

        (res+=h[i]*(get(N/(i*i),A)-get(N/(i*i),B)+mod))%=mod;
    }

    res=(res+mod)*invT%mod;
    cout << res << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
