#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

const int inv2 = (mod+1)/2;
const int inv3 = (mod+1)/3;
const int inv6 = inv2*inv3%mod;

const int M = 10000000;
const int N = 12340005;
int p[N],f[N],g[N],h[N];

void solve(){
    auto cal = [&](int n){
        return (int)(((__int128)n*(n+1)*(n+2)/6-n)%mod);
    };
    auto get = [&](int n,int x){
        int k=n/x;
        return (k*n-k*(k+1)/2*x)%mod;
    };
    int n,m;cin >> n >> m;
    if(n>m) swap(n,m);
    int nn=n%mod,mm=m%mod;
    
    f[1]=g[1]=h[1]=1;
    for(int i=2;i<M;i++){
        if(!p[i]) for(int j=i;j<M;j+=i) p[j]=i;
        if((i/p[i])%p[i]==0) f[i]=f[i/p[i]]*p[i];
        else f[i]=f[i/p[i]]*(p[i]-1);
        g[i]=f[i]*i%mod;
        h[i]=g[i]*i%mod;
    }
    for(int i=2;i<M;i++){
        f[i]=(f[i]+f[i-1])%mod;
        g[i]=(g[i]+g[i-1])%mod;
        h[i]=(h[i]+h[i-1])%mod;
    }

    //cout << "start " << endl;

    vector<int> P;
    auto add = [&](int d){
        int s=sqrtl(d);
        for(int i=1;i<s;i++) P.push_back(d/(i+1)+1);
        for(int i=2;i<=d/s;i++) P.push_back(i);
    };

    add(n);
    add(m);
    P.push_back(n);
    sort(P.begin(),P.end());

    map<int,int> mf,mg,mh;
    function<int(int)> F = [&](int d){
        if(d<0) return 0LL;
        if(d<M) return f[d];
        if(mf.find(d)!=mf.end()) return mf[d];
        int md=d%mod;
        int ret=(md*(md+1)/2)%mod;
        /*
        i = sum(d|i) phi(d)
        d*(d+1)/2-F(d/2)-F(d/3)
        */
        int s=sqrtl(d);
        for(int i=1;i<s;i++){
            int val=(d/i-d/(i+1))%mod*f[i]%mod;
            ret=(ret+mod-val)%mod;
        }
        for(int i=2;i<=d/s;i++) ret=(ret+mod-F(d/i))%mod;
        return mf[d]=ret;
    };
    auto f2 = [&](int d){
        d%=mod;
        return d*(d+1)%mod*(2*d+1)%mod*inv6%mod;
    };
    function<int(int)> G = [&](int d){
        if(d<0) return 0LL;
        if(d<M) return g[d];
        if(mg.find(d)!=mg.end()) return mg[d];
        int ret=f2(d);
        /*
        sum(i*i)
        - 2*G(d/2) - 3*G(d/3)  ... - d*G(d/d)
        */
        int s=sqrtl(d);
        for(int i=1;i<s;i++){
            int l=d/(i+1),r=d/i;
            l%=mod;r%=mod;
            int val=(r-l)*(l+1+r)/2;
            val=val%mod*g[i]%mod;
            ret=(ret+mod-val)%mod;
        }
        for(int i=2;i<=d/s;i++) ret=(ret+mod-i*G(d/i)%mod)%mod;
        return mg[d]=ret;
    };
    function<int(int)> H = [&](int d){
        if(d<0) return 0LL;
        if(d<M) return h[d];
        if(mh.find(d)!=mh.end()) return mh[d];
        int md=d%mod;
        int ret=(md*(md+1)/2)%mod;
        ret=ret*ret%mod;
        /*
        i*i
        -2*2*H(d/2)-3*3*G(d/3)-...-d*G(d/d)
        */
        int s=sqrtl(d);
        for(int i=1;i<s;i++){
            int l=d/(i+1),r=d/i;
            int val=(f2(r)-f2(l)+mod)%mod;
            val=val%mod*h[i]%mod;
            ret=(ret+mod-val)%mod;
        }
        for(int i=2;i<=d/s;i++) ret=(ret+mod-i*i%mod*H(d/i)%mod)%mod;
        return mh[d]=ret;
    };

    int res=cal(nn)*cal(mm)%mod;
    int cnt=0;
    auto del = [&](int l,int r){
        cnt++;
        if(cnt%1000==0) cout << "del " << l << ' ' << r << endl;
        int nk=n/l,mk=m/l;
        nk%=mod;mk%=mod;

        int A=0,B=0,C=0;
        {
            int a=nk*nn%mod,b=(nk*(nk+1)/2)%mod;
            int c=mk*mm%mod,d=(mk*(mk+1)/2)%mod;
            C=a*c%mod;
            A=b*d%mod;
            B=(2*mod-a*d%mod-b*c%mod)%mod;
        }

        int val=A*(H(r-1)-H(l-1)+mod)%mod+B*(G(r-1)-G(l-1)+mod)+C*(F(r-1)-F(l-1)+mod);
        val%=mod;
        res=(res+mod-val)%mod;
    };
    int X=2;
    for(int x:P){
        if(x<=1) continue;
        del(X,x);X=x;
        if(x==n) break;
    }

    /*
    for(int x=2;x<n;x++){
        int val=get(n,x)*get(m,x)%mod*f[x]%mod;
        res=(res+mod-val)%mod;
    }
    123400000000 234500000000
    */
    int val=(nn*(nn-1)/2)%mod*mm%mod*(mm-1)%mod;
    res=(res+mod-val)%mod;
    res=(res+mod)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
