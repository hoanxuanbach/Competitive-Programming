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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int LG = 20;
void solve(){
    vector<int> S;

    int N,Q,K;cin >> N >> Q >> K;
    vector<int> A(N+1),P(N+1);
    vector<int> L(N+1),R(N+1);
    
    S.push_back(0);
    S.push_back(K);
    for(int i=1;i<=N;i++){
        cin >> A[i];
        if(!(i&1)){
            P[i]=P[i-1]-A[i];
            if(A[i]>=K) L[i]=0,R[i]=K-1;
            else{
                L[i]=((P[i]+1)%K+K)%K;
                R[i]=(P[i-1]%K+K)%K;
                //cout << '*' << i << ' ' << L[i] << ' ' << R[i] << '\n';
            } 
            S.push_back(L[i]);
            S.push_back(R[i]+1);
        }
        else P[i]=P[i-1]+A[i];
    }

    sort(S.begin(),S.end());
    S.erase(unique(S.begin(),S.end()),S.end());
    int M=(int)S.size();
    auto get = [&](int x){
        return upper_bound(S.begin(),S.end(),x)-S.begin();
    };

    vector<int> nxt(N+1);
    {
        vector<int> tree(4*M,N);
        function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int val){
            if(r<tl || tr<l) return;
            if(tl<=l && r<=tr){
                tree[id]=min(tree[id],val);
                return;
            }
            int mid=(l+r)>>1;
            update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        };
        function<int(int,int,int,int)> query = [&](int l,int r,int id,int x){
            if(l==r) return tree[id];
            int mid=(l+r)>>1;
            if(x<=mid) return min(tree[id],query(l,mid,id<<1,x));
            else return min(tree[id],query(mid+1,r,id<<1|1,x));
        };
        for(int i=N;i>=1;i--){
            if(i&1){
                nxt[i]=query(1,M,1,get((P[i-1]%K+K)%K));
            }
            else{
                int l=get(L[i]),r=get(R[i]+1)-1;
                if(l<=r) update(1,M,1,l,r,i);
                else update(1,M,1,l,M,i),update(1,M,1,1,r,i);
            }
        }
    }
    vector<int> tree(4*N);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            tree[id]=P[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    };
    build(1,N,1);
    function<int(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return -inf;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    };
    
    vector<vector<int>> jmp(N+2,vector<int>(LG,N+1)),cnt(N+2,vector<int>(LG));
    for(int i=1;i<=N;i+=2){
        jmp[i][0]=nxt[i]+1;
        cnt[i][0]=max(0LL,query(1,N,1,i,nxt[i])-P[i-1])/K;
    }
    for(int j=1;j<LG;j++) for(int i=1;i<=N;i+=2){
        jmp[i][j]=jmp[jmp[i][j-1]][j-1];
        cnt[i][j]=cnt[i][j-1]+cnt[jmp[i][j-1]][j-1];
    }

    while(Q--){
        int l,r;cin >> l >> r;
        if(!(l&1)) l++;
        if(l>r){
            cout << 0LL << '\n';
            continue;
        }
        int res=0;
        for(int j=LG-1;j>=0;j--){
            if(jmp[l][j]>r) continue;
            res+=cnt[l][j];
            l=jmp[l][j];
        }
        res+=max(0LL,query(1,N,1,l,r)-P[l-1])/K;
        cout << res << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
