#include<bits/stdc++.h>
using namespace std;
#define int long long
int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}

bool has[5005][5005];
vector<array<int,3>> P[5005][5005];

void solve(){
    int L,R;cin >> L >> R;

    vector<int> p(R),f(R,1);
    for(int i=2;i<R;i++){
        if(!p[i]){
            for(int j=i;j<R;j+=i) p[j]=i;
        }
        int x=p[i];
        if((i/x)%x==0) f[i]=f[i/x]*x;
        else f[i]=f[i/x]*(x-1);
    }

    int N=R-L;
    vector<vector<array<int,2>>> fd(R);
    vector<vector<array<int,2>>> g(R);
    for(int i=1;i<R;i++){
        int id=i-L,x=i;
        while(x>1){
            int j=p[x],k=1;
            while(x%j==0) x/=j,k*=j;
            if(i>=L) g[j].push_back({k,id});
            fd[i].push_back({k,(k/j)*(j-1)});
        }
    }
    for(int x=2;x<R;x++){
        sort(g[x].begin(),g[x].end());
        for(int i=0;i<(int)g[x].size();i++) for(int j=i+1;j<(int)g[x].size();j++){
            int a=L+g[x][i][1],b=L+g[x][j][1],d=g[x][i][0],dd=g[x][j][0];
            int aa=a,bb=b;aa-=L;bb-=L;
            if(aa>bb) swap(aa,bb);
            if(f[b]%d==f[a]%d) P[aa][bb].push_back({dd,(dd/x)*(x-1),f[b]%dd});
            else has[aa][bb]=true;
        }
    }
    int res=0,cnt=0;
    for(int i=0;i<N;i++) for(int j=i+1;j<N;j++) if(!has[i][j]){

        vector<array<int,3>> pp=P[i][j];
        int ci=L+i,cj=L+j,cg=__gcd(ci,cj);
        while(cg>1){
            int x=p[cg];
            while(cg%x==0) cg/=x;
            while(ci%x==0) ci/=x;
            while(cj%x==0) cj/=x;
        }
        for(auto [x,d]:fd[ci]) pp.push_back({x,d,f[L+i]%x});
        for(auto [x,d]:fd[cj]) pp.push_back({x,d,f[L+j]%x});
        

        cnt++;
        long long X=1;
        for(auto [x,d,k]:pp) X*=x;

        long long val=0;
        for(auto [x,d,k]:pp) val+=1LL*(1LL*(k*power((X/x)%x,d-1,x))%x)*(X/x);
        val%=X;
        res+=val;
        
        if(cnt%1000==0) cout << cnt << endl;
        
    }
    cout << cnt << ' ' << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
