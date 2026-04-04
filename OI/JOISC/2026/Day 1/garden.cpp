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


    void solve(){
        int H,W,N,X;cin >> H >> W >> N >> X;
        vector<int> U(N+1),D(N+1),L(N+1),R(N+1),C(N+1);
        for(int i=1;i<=N;i++) cin >> U[i] >> D[i] >> L[i] >> R[i] >> C[i];

        auto cal = [&](){
            
            vector<int> hS={1,H+1},wS={1,W+1};
            for(int i=1;i<=N;i++){
                hS.push_back(U[i]);
                hS.push_back(D[i]+1);
                wS.push_back(L[i]);
                wS.push_back(R[i]+1);
            }

            auto get = [&](vector<int> &S,int x){
                return upper_bound(S.begin(),S.end(),x)-S.begin();
            };

            sort(hS.begin(),hS.end());
            hS.erase(unique(hS.begin(),hS.end()),hS.end());
            sort(wS.begin(),wS.end());
            wS.erase(unique(wS.begin(),wS.end()),wS.end());

            int T=N;
            vector<int> res(N+1,-1);
            int sz=(int)hS.size();
            vector<vector<int>> g(sz);
            for(int i=1;i<=N;i++){
                int u=get(hS,U[i])-1;
                int d=get(hS,D[i]+1)-1;
                g[u].push_back(i);
                g[d].push_back(-i);
            }

            int M=(int)wS.size();
            vector<int> lazy(4*M),tree(4*M);
            function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int val){
                if(tr<l || r<tl) return;
                if(tl<=l && r<=tr){
                    lazy[id]+=val;
                    tree[id]+=val;
                    return;
                }
                int mid=(l+r)>>1;
                update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
                tree[id]=max(tree[id<<1],tree[id<<1|1])+lazy[id];
            };

            vector<int> ins(N+1);
            for(int i=0;i<sz;i++){
                for(int x:g[i]){
                    if(abs(x)>T) continue;
                    int sgn=(x<0?-1:1);x=abs(x);ins[x]+=sgn;
                    update(1,M,1,get(wS,L[x]),get(wS,R[x]),sgn*C[x]);
                }
                while(tree[1]>=X){
                    res[T]=hS[i];
                    if(ins[T]){
                    update(1,M,1,get(wS,L[T]),get(wS,R[T]),-C[T]);
                    ins[T]=0; 
                    }
                    T--;
                }
            }
            return res;
        };

        vector<int> fU=cal();
        for(int i=1;i<=N;i++) swap(U[i],D[i]),U[i]=H+1-U[i],D[i]=H+1-D[i];
        vector<int> fD=cal();

        swap(H,W);
        for(int i=1;i<=N;i++) swap(U[i],L[i]),swap(D[i],R[i]);
        vector<int> fL=cal();
        for(int i=1;i<=N;i++) swap(U[i],D[i]),U[i]=H+1-U[i],D[i]=H+1-D[i];
        vector<int> fR=cal();

        swap(H,W);
        for(int i=1;i<=N;i++){
            if(fU[i]==-1) cout << 0 << '\n';
            else cout << (H+2-fU[i]-fD[i])*(W+2-fL[i]-fR[i]) << '\n';
        }
    }
    
    signed main(){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);cout.tie(NULL);
        int test=1;//cin >> test;
        while(test--) solve();
    }
