#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int inverse(int k,int mod){
    int M=mod,P=1;
    for(int i=2;i*i<=M;i++){
        if(M%i==0){
            int X=1;
            while(M%i==0) M/=i,X*=i;
            P*=X/i*(i-1);
        }
    }
    if(M>1) P*=(M-1);
    int res=1;P--;
    while(P){
        if(P&1) res=res*k%mod;
        k=k*k%mod;P>>=1;
    }
    return res;
}

const int mod = 998244353;
#define matrix vector<vector<int>>

matrix I;
matrix operator*(matrix a,matrix b){
    int n=(int)a.size();
    matrix c(n,vector<int>(n,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) c[i][k]=(c[i][k]+a[i][j]*b[j][k])%mod;
    return c;
}
matrix power(matrix a,int n){
    matrix res=I;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
    }
    return res;
}

void solve(){
    int n,m,k,L;cin >> n >> m >> k >> L;
    k=inverse(k,L);
    
    vector<int> t(m);
    for(int i=0;i<m;i++) cin >> t[i];

    I.assign(m+1,vector<int>(m+1,0));
    for(int i=0;i<=m;i++) I[i][i]=1;

    vector<pair<int,matrix>> S(n);
    for(int i=0;i<n;i++){
        int s,v;cin >> s >> v;
        vector<vector<int>> M=I;
        for(int x=0;x<m;x++) if(t[x]==v) M[x][x+1]=1;
        S[i]={s,M};
    }

    while(L>1){
        if(2*k>L){
            S.push_back({1,S[0].second});
            if(S[0].first>1) S[0].first--;
            else S.erase(S.begin());
            reverse(S.begin(),S.end());
            k=L-k;
        }
        n=(int)S.size();
        vector<int> d(n);
        vector<matrix> T(4*n,I);

        function<void(int,int,int,int)> update = [&](int l,int r,int id,int x){
            if(l==r){
                T[id]=power(S[x].second,d[x]);
                return;
            }
            int mid=(l+r)>>1;
            if(x<=mid) update(l,mid,id<<1,x);
            else update(mid+1,r,id<<1|1,x);
            T[id]=T[id<<1]*T[id<<1|1];
        };

        int P=0;
        vector<array<int,3>> E;
        for(int i=0;i<n;i++){
            if(P%k) E.push_back({P%k,i,1});
            int w=S[i].first;
            E.push_back({0,i,(P+w+k-1)/k-(P+k-1)/k});
            P+=w;
            if(P%k) E.push_back({P%k,i,-1});
        }
        sort(E.begin(),E.end());E.push_back({k,-1,0});

        int sz=(int)E.size();
        vector<pair<int,matrix>> nS;
        for(int l=0,r=0;l+1<sz;l=r){
            while(E[r][0]==E[l][0]){
                d[E[r][1]]+=E[r][2];
                update(0,n-1,1,E[r][1]);
                r++;
            }
            nS.push_back({E[r][0]-E[l][0],T[1]});
        }
        swap(S,nS);
        L=k-L%k;
        swap(L,k);
    }
    cout << S[0].second[0][m] << '\n';

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
