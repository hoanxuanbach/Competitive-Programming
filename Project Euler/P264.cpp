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
    int P;cin >> P;

    double R = P*P/16.0;
    double D = P/2.0;
    int M = 40*D+100;

    vector<int> f(M+1),phi(M+1,1);
    for(int i=2;i<=M;i++) if(!f[i]) for(int j=i;j<=M;j+=i) f[j]=i;
    for(int i=2;i<=M;i++){
        if((i/f[i])%f[i]==0) phi[i]=phi[i/f[i]]*f[i];
        else phi[i]=phi[i/f[i]]*(f[i]-1);
    }

    double res = 0;
    set<array<pii,3>> S;
    auto dist = [&](pii x,pii y){
        int fst=y.first-x.first,sec=y.second-x.second;
        return sqrtl(fst*fst+sec*sec);
    };
    auto add = [&](pii x,pii y,pii z){
        //cout << "add " << x.first << ' ' << x.second << ' ' << y.first << ' ' << y.second << ' ' << z.first << ' ' << z.second << endl;
        if(x==y || x==z || y==z) return;
        double val = dist(x,y)+dist(x,z)+dist(y,z);
        if(val>P) return;
        array<pii,3> cur={x,y,z};
        sort(cur.begin(),cur.end());
        if(S.find(cur)==S.end()){
            S.insert(cur);
            res+=val;
        }
    };

    {//d = 0
        for(int x=-5;x<=5;x++){
            int y=25-x*x;
            int sy=sqrtl(y);
            if(sy*sy!=y) continue;
            add({x,sy},{-x,-sy},{5,0});
            add({x,-sy},{-x,sy},{5,0});
        }
    }

    for(int p=0;p*p<=M;p++){
        int mxq = sqrtl(M-p*p);
        for(int q=-mxq;q<=mxq;q++){
            if(p==0){
                if(q!=1) continue;
            }
            if(__gcd(p,abs(q))!=1) continue;

            int m=p*p+q*q;
            int a=40*p%m,b=100%m;
            int d=__gcd(a,m);
            if(b%d!=0) continue;
            a/=d;b/=d;
            int mm=m/d;

            int G=0;
            if(mm>1) G=b*power(a,phi[mm]-1,mm)%mm;
            
            int mxg=(int)(D/sqrtl(m))+2;

            auto eval = [&](int g){
                if(g==0) return;
                int T=3*g*g*m-40*g*p+100;
                if(T<=0 || T%m!=0) return;
                int t=sqrtl(T/m);
                if(t*t*m!=T) return;

                if(((g*p+t*q)&1) || ((g*q-t*p)&1)) return;

                int ax=5-g*p,ay=-g*q;
                int bx=(g*p+t*q)/2,by=(g*q-t*p)/2;
                int cx=(g*p-t*q)/2,cy=(g*q+t*p)/2;
                add({ax,ay},{bx,by},{cx,cy});
            };

            for(int k=0;;k--){
                int g=G+k*mm;
                if(abs(g)>mxg) break;
                eval(g);
            }
            for(int k=1;;k++){
                int g=G+k*mm;
                if(abs(g)>mxg) break;
                eval(g);
            }
        }
    }
    cout << setprecision(4) << fixed << res << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
