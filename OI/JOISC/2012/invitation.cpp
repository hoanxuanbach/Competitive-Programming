#include<bits/stdc++.h>
using namespace std; 
//#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 2e9;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 3e5+15;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

bool vis[maxn];
vector<int> dd;

struct DS{
    vector<int> tree[4*maxn];
    int mx[4*maxn],lazy[4*maxn];
    void add(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id].push_back(val);
            return;
        }
        int mid=(l+r)>>1;
        add(l,mid,id<<1,tl,tr,val);add(mid+1,r,id<<1|1,tl,tr,val);
    }
    void getnew(int id,int val){
        if(mx[id]!=-inf){
            mx[id]=max(mx[id],val);
            lazy[id]=max(lazy[id],val);
        }
    }
    void pushdown(int id){
        if(lazy[id]){
            getnew(id<<1,lazy[id]);
            getnew(id<<1|1,lazy[id]);
            lazy[id]=0;
        }
    }
    void del(int l,int r,int id,int x){
        for(int i:tree[id]) if(!vis[i]){
            vis[i]=true;
            dd.push_back(i);
        }
        tree[id].clear();
        if(l==r){
            mx[id]=-inf;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) del(l,mid,id<<1,x);
        else del(mid+1,r,id<<1|1,x);
        mx[id]=max(mx[id<<1],mx[id<<1|1]);
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        mx[id]=max(mx[id<<1],mx[id<<1|1]);
    }
    int get(int l,int r,int id){
        if(l==r) return l;
        pushdown(id);
        int mid=(l+r)>>1;
        if(mx[id<<1]==mx[id]) return get(l,mid,id<<1);
        else return get(mid+1,r,id<<1|1);
    }
}dA,dB;

void solve(){   
    int A,B,C,N;cin >> A >> B >> C >> N;
    vector<int> P(N),Q(N),R(N),S(N),T(N);


    vector<int> cA,cB;
    cA={1,C,C+1,A+1};cB={1,B+1};
    for(int i=0;i<N;i++){
        cin >> P[i] >> Q[i] >> R[i] >> S[i] >> T[i];
        cA.push_back(P[i]),cA.push_back(P[i]+1),cA.push_back(Q[i]+1);
        cB.push_back(R[i]),cB.push_back(R[i]+1),cB.push_back(S[i]+1);
    }
    sort(cA.begin(),cA.end());cA.erase(unique(cA.begin(),cA.end()),cA.end());
    sort(cB.begin(),cB.end());cB.erase(unique(cB.begin(),cB.end()),cB.end());
    int sA=(int)cA.size()-1,sB=(int)cB.size()-1;

    C=lower_bound(cA.begin(),cA.end(),C)-cA.begin()+1;
    for(int i=0;i<N;i++){
        P[i]=lower_bound(cA.begin(),cA.end(),P[i])-cA.begin()+1;
        Q[i]=lower_bound(cA.begin(),cA.end(),Q[i]+1)-cA.begin();
        R[i]=lower_bound(cB.begin(),cB.end(),R[i])-cB.begin()+1;
        S[i]=lower_bound(cB.begin(),cB.end(),S[i]+1)-cB.begin();
        dA.add(1,sA,1,P[i],Q[i],i);
        dB.add(1,sB,1,R[i],S[i],i);
    }
    for(int i=sA;i>=1;i--) cA[i]-=cA[i-1];
    for(int i=sB;i>=1;i--) cB[i]-=cB[i-1];

    long long res=0;
    dA.del(1,sA,1,C);

    //cout << sA << ' ' << sB << '\n';
    while(true){
        for(int i:dd){
            dA.update(1,sA,1,P[i],Q[i],T[i]);
            dB.update(1,sB,1,R[i],S[i],T[i]);
        }
        dd.clear();
        int val=max(dA.mx[1],dB.mx[1]);
        if(val==-inf) break;
        else if(val==0){
            cout << -1 << '\n';
            return;
        }
        if(dA.mx[1]==val){
            int i=dA.get(1,sA,1);
            res+=1LL*cA[i]*val;
            dA.del(1,sA,1,i);
            //cout << "A " << i << ' ' << val << '\n';
        }
        else{
            int i=dB.get(1,sB,1);
            res+=1LL*cB[i]*val;
            dB.del(1,sB,1,i);
            //cout << "B " << i << ' ' << val << '\n';
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
/*
5 6 3 
4
2 4 1 3 20
1 2 2 4 40
4 5 2 3 30
4 4 4 6 10
*/