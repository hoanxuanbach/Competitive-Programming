#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
//int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=10000005;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int ss[maxn];
array<int,3> A[maxn];
bool use[maxn];

int la[maxa],lb[maxa],lt[maxn];

struct pt{
    int x,y,id;
    pt(int _x=0,int _y=0,int _id=-1):x(_x),y(_y),id(_id){}
    pt operator + (const pt &p)const{
        return pt{x+p.x,y+p.y,-1};
    }
    pt operator - (const pt &p)const{
        return pt{x-p.x,y-p.y,-1};
    }
    int operator *(const pt &p)const{
        return (ld)x/(ld)y>(ld)p.x/(ld)p.y;
    }
    friend bool operator<(pt a,pt b){return make_pair(a.y,a.x)<make_pair(b.y,b.x);}
    friend bool operator>(pt a,pt b){return make_pair(a.y,a.x)>make_pair(b.y,b.x);}
    friend bool operator==(pt a,pt b){return make_pair(a.y,a.x)==make_pair(b.y,b.x);}
};

void solve(){
    int N,L,T;cin >> N >> L >> T;
    int total=0;

    for(int i=0;i<N;i++) cin >> A[i][0] >> A[i][1] >> A[i][2],total+=A[i][1]*A[i][2];
    sort(A,A+N);
    A[N]={T,0,0};

    //cout << T/G << '\n';
    //for(int i=0;i<=N;i++) cout << A[i][0]/G << ' ' << A[i][1]/G << '\n';

    vector<pii> P;
    for(int i=0;i<N;i++) P.push_back({A[i][2],i});
    sort(P.begin(),P.end());

    for(int i=0;i<=N;i++) use[i]=true;

    auto compare = [&](pt a,pt b){
        return (ld)a.x/a.y < (ld)b.x/b.y;
    };

    int X=1;
    for(int i=0;i<N;i++){
        int cnt=P[i].fi-X+1;
        if(cnt){
            vector<pii> pos;
            for(int j=N-1;j>=0;j--){
                ss[j]=ss[j+1];
                if(use[j]) ss[j]+=A[j][1];
            }

            vector<pt> v;
            for(int j=0;j<=N;j++){
                if(use[j]){
                    //cout << "use " << j << '\n';
                    pt x=pt(A[j][0],-ss[j],j);
                    //cout << x.x/G << ' ' << x.y/G << '\n';
                    while((int)v.size()>=2 && compare(v.back()-v.end()[-2],x-v.end()[-2])) v.pop_back();
                    v.push_back(x);
                }
            }
            
            for(int j=0;j<(int)v.size()-1;j++){
                int lid=v[j].id,rid=v[j+1].id;
                for(int k=lid;k<rid;k++){
                    if(!use[k]) continue;
                    int x=A[rid][0]-A[k][0],y=ss[k]-ss[rid];
                    if(x==0) lt[k]=1;
                    else lt[k]=(x-1)/y+1;
                    //cout << lt[k] << ' ';
                }
            }
            //cout << '\n';

            for(int j=N-1;j>=0;j--){
                if(!use[j]) continue;
                while(!pos.empty() && pos.back().fi>=lt[j]) pos.pop_back();
                pos.push_back({lt[j],j});
            }

            int l=1,a=cnt*ss[0],b=0;
            la[1]+=a,lb[1]+=b;
            
            for(auto [r,id]:pos){
                if(r>L) continue;

                //cout << r << ' ' << id << '\n';
                //l->r: i*(sum[0]-sum[id])+(T-A[id][0])
                //i*cnt*a+cnt*b
                int na=(ss[0]-ss[id])*cnt,nb=cnt*(T-A[id][0]);
                //cout << r << ' ' << id << ' ' << na << ' ' << nb << '\n';
                la[r]+=na-a,lb[r]+=nb-b;
                a=na,b=nb;

            }
            /*
            //cout << "pos " << i << ' ' << ss[0] << ' ' << a << ' ' << b << '\n';
            for(auto [r,id]:pos){
                if(r>L) break;
                //cout << r << ' ' << id << '\n';
                //l->r: i*(sum[0]-sum[id])+(T-A[id][0])
                //i*cnt*a+cnt*b
                int na=(ss[0]-ss[id])*cnt,nb=cnt*(T-A[id][0]);
                //cout << r << ' ' << id << ' ' << na << ' ' << nb << '\n';
                la[r]+=na-a,lb[r]+=nb-b;
                a=na,b=nb;
            }
            */
        }
        use[P[i].se]=false;
        X=P[i].fi+1;
    }
    for(int i=1;i<=L;i++) la[i]+=la[i-1],lb[i]+=lb[i-1];
    for(int i=1;i<=L;i++) la[i]=(total-la[i])*i-lb[i];

    int Q;cin >> Q;
    for(int i=0;i<Q;i++){
        int M;cin >> M;
        cout << upper_bound(la,la+L+1,M)-la-1 << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
