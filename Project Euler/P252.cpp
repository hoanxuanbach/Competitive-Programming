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
 
//const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

struct point{
    int x,y,dist;
    double rad;
    point(int _x=0,int _y=0):x(_x),y(_y){
        rad=atan2(y,x);
        dist=x*x+y*y;
    }
    point operator-(point a)const{
        return point(x-a.x,y-a.y);
    }
    int cross(point a){
        return x*a.y-y*a.x;
    }
    friend bool operator<(point &a,point &b){
        if(a.cross(b)) return a.rad<b.rad;
        else return a.dist<b.dist;
    }
};

const int maxn = 505;
int f[maxn][maxn];

void solve(){


    auto cal = [&](vector<point> P){
        int n=(int)P.size();
        sort(P.begin(),P.end());
        memset(f,0,sizeof(f));

        int res=0;
        for(int i=0;i<n;i++){
            int j=i-1;
            while(j>=0 && P[i].cross(P[j])==0) j--;
            bool ins=(j==(i-1));
            while(j>=0){
                int k=j-1;
                while(k>=0 && (P[i]-P[j]).cross(P[k]-P[j])<0) k--;
                int s=abs(P[i].cross(P[j]));
                if(k>=0) s+=f[j][k];
                if(ins) f[i][j]=s;
                res=max(res,s);
                j=k;
            }
            if(ins){
                for(int j=1;j<i;j++) f[i][j]=max(f[i][j],f[i][j-1]);
            }
        }

        return res;
    };

    int N;cin >> N;
    vector<point> P(N);

    vector<int> S(2*N+1);
    S[0]=290797;
    for(int i=1;i<=2*N;i++){
        S[i]=S[i-1]*S[i-1]%50515093;
        if(i%2==0) P[i/2-1]=point(S[i-1]%2000-1000,S[i]%2000-1000);
    }
    int res=0;
    for(int i=0;i<N;i++){
        vector<point> T;
        for(int j=0;j<N;j++) if(P[j].y>P[i].y || (P[j].y==P[i].y && P[j].x>P[i].x)){
            point X=P[j]-P[i];
            T.emplace_back(X);
        }
        res=max(res,cal(T));
    }
    double ans=res*0.5;
    cout << setprecision(1) << fixed << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
