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
 
const int maxn = (1<<22)+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

struct line{
    int a,b,p;
    bool operator<(line o){return a<o.a;}
    bool operator<(int o){return p<o;}
};
struct cvht{
    int pos=0;
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    void isect(line &y,line &l){
        if(y.a==l.a) y.p=(y.b>l.b)?inf:-inf;
        else y.p=div(y.b-l.b,l.a-y.a);
        return;
    }
    void add(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    int query(int v){
        while(x[pos].p<v) pos++;
        return x[pos].a*v+x[pos].b;
    }
};

void solve(){
    int N,M,X,Q;cin >> N >> M >> X >> Q;
    
    vector<int> A(M+1);
    for(int i=1;i<=M;i++) cin >> A[i];

    vector<int> res(Q),S(Q),K(Q),L(Q),R(Q),G;
    for(int i=0;i<Q;i++){
        cin >> K[i] >> S[i];
    
        R[i]=upper_bound(A.begin()+1,A.end(),S[i])-A.begin()-1;
        L[i]=lower_bound(A.begin()+1,A.end(),S[i]+K[i]-X)-A.begin();
        if(L[i]<=R[i]) G.push_back(i),res[i]=inf;
    }
    sort(G.begin(),G.end(),[&](int x,int y){
        return K[x]<K[y];
    });
    auto cal = [&](int i,int k){
        return A[i]-i*k;
    };
    auto f = [&](int i,int j,int k){
        return (A[j]-A[i])*(k-j)>=(A[k]-A[j])*(j-i);
    };
    function<vector<int>(int,int,vector<int>)> dnc = [&](int l,int r,vector<int> g){
        int mid=(l+r)>>1;
        vector<int> lg,rg,gg;
        for(int i:g){
            if(L[i]<=l && r<=R[i]) gg.push_back(i);
            else{
                if(L[i]<=mid) lg.push_back(i);
                if(mid<R[i]) rg.push_back(i);
            }
        }

        vector<int> T;

        if(l==r) T={l};
        else{
            T=dnc(l,mid,lg);
            vector<int> nT=dnc(mid+1,r,rg);
            for(int x:nT){
                while((int)T.size()>1 && f(T.end()[-2],T.back(),x)) T.pop_back();
                T.push_back(x);
            }
        }

        int pos=0;
        for(int i:gg){
            while(pos+1<(int)T.size() && cal(T[pos],K[i])>=cal(T[pos+1],K[i])) pos++;
            res[i]=min(res[i],cal(T[pos],K[i]));
        }
        return T;
    };
    dnc(1,M,G);

    for(int i=0;i<Q;i++){
        if(L[i]<=R[i]) res[i]=min((res[i]+R[i]*K[i]-S[i]+X)/K[i],R[i]-L[i]+1);
        cout << res[i] << '\n';
    }

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
