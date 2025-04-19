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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e8;
const int mod=998244353;
//int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    //dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int tt[maxn],pre[maxn];

void solve(){
    int N,Q;cin >> N;
    string S;cin >> S;
    cin >> Q;
    vector<array<int,3>> qq(Q);
    for(int i=0;i<Q;i++) cin >> qq[i][0] >> qq[i][1] >> qq[i][2];
    vector<int> res(Q,inf);

    //AB,C - A,C - B,C
    //A,B
    //A,B+C
    //none

    vector<int> perm = {0,1,2};
    vector<vector<int>> TT(3);
    do{
        vector<int> A,B,AB;
        int sA=0,sB=0,sC=0,sAB=0,sAC=0,sBC=0;

        int PP=0;
        for(int i=0;i<3;i++) if(perm[i]==0) PP=i;

        int base = 0,cnt=0;
        char cc = S[0];
        string nS;
        for(char c:S){
            if(c=='?') nS+=c;
            else nS+=char('A'+perm[c-'A']);
        }
        for(int i=1;i<N;i++){
            if(S[i]=='?') cnt++;
            else{
                if(cnt){
                    int x=perm[cc-'A'],y=perm[S[i]-'A'];
                    if(x>y) swap(x,y);
                    if(x==0 && y==0) A.push_back(cnt),sA+=cnt;
                    else if(x==1 && y==1) B.push_back(cnt),sB+=cnt;
                    else if(x==2 && y==2) sC+=cnt;
                    else if(x==0 && y==1) AB.push_back(cnt),sAB+=cnt;
                    else if(x==0 && y==2) sAC+=cnt;
                    else sBC+=cnt;
                }
                if(S[i]!=cc) base++;
                cc=S[i],cnt=0;
            }
        }

        sort(A.begin(),A.end(),greater<int>());
        sort(B.begin(),B.end(),greater<int>());
        sort(AB.begin(),AB.end(),greater<int>());

        vector<pii> PA;
        for(int x:A){
            if(PA.empty() || x!=PA.back().fi) PA.push_back({x,1});
            else PA.back().se++;
        }
        cnt=0;

        if(TT[PP].empty()){
            for(int i=1;i<=sA;i++) tt[i]=inf;
            tt[0]=0;
            
            
            for(auto [x,d]:PA){
                for(int i=0;i<x;i++) pre[i]=-1;
                for(int i=0;i<=sA;i++){
                    bool check=(tt[i]!=inf);
                    if(pre[i%x]!=-1 && (i-pre[i%x])/x<=d && tt[i]==inf) tt[i]=min(tt[i],cnt+(i-pre[i%x])/x);
                    if(check) pre[i%x]=i;
                }
                cnt+=d;
            }
            vector<int> ctt(sA+1);
            for(int i=0;i<=sA;i++) ctt[i]=tt[i];
            TT[PP]=ctt;
        }
        else{
            for(int i=0;i<=sA;i++) tt[i]=TT[PP][i];
        }

        vector<int> tree(4*(sA+1));
        function<void(int,int,int)> build = [&](int l,int r,int id){
            if(l==r){
                tree[id]=tt[l];
                //cout << "Time " << l << ' ' << tm[l] << '\n';
                return;
            }
            int mid=(l+r)>>1;
            build(l,mid,id<<1);build(mid+1,r,id<<1|1);
            tree[id]=min(tree[id<<1],tree[id<<1|1]);
        };
        build(0,sA,1);
        function<int(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
            if(tr<l || r<tl) return inf;
            if(tl<=l && r<=tr) return tree[id];
            int mid=(l+r)>>1;
            return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
        };

        
        int szA=(int)A.size(),szB=(int)B.size(),szAB=(int)AB.size();
        
        int fst=-1;
        vector<int> T0,T1;
        if(szAB) fst=AB[0];
        for(int i=0;i+1<szAB;i+=2) T0.push_back(AB[i]+AB[i+1]);
        for(int i=1;i+1<szAB;i+=2) T1.push_back(AB[i]+AB[i+1]);

        vector<int> pA(szA+1),pB(szB+1);
        for(int i=0;i<szA;i++) pA[i+1]=pA[i]+A[i];
        for(int i=0;i<szB;i++) pB[i+1]=pB[i]+B[i];

        int szT0=(int)T0.size(),szT1=(int)T1.size();
        vector<int> pT0(szT0+1),pT1(szT1+1);
        for(int i=0;i<szT0;i++) pT0[i+1]=pT0[i]+T0[i];
        for(int i=0;i<szT1;i++) pT1[i+1]=pT1[i]+T1[i];


        auto getA = [&](int x){
            return lower_bound(pA.begin(),pA.end(),x)-pA.begin();
        };
        auto getB = [&](int x){
            return lower_bound(pB.begin(),pB.end(),x)-pB.begin();
        };
        auto getT = [&](int posA,int posB,int dC,vector<int> &T,vector<int> &pT){
            /*
            cout << dC << '\n';
            cout << "A " << sA << '\n';
            for(int x:A) cout << x << ' ';
            cout << '\n';
            cout << "B " << sB << '\n';
            for(int x:B) cout << x << ' ';
            cout << '\n';
            cout << "T\n";
            for(int x:T) cout << x << ' ';
            cout << '\n';
            */
            int l=1,r=N;
            int val=0,cnt=0,sum=0;
            while(l<=r){
                int x=(l+r)>>1;
                int numA=upper_bound(A.begin(),A.end(),x,greater<int>())-A.begin();
                int numB=upper_bound(B.begin(),B.end(),x,greater<int>())-B.begin();
                int numT=upper_bound(T.begin(),T.end(),x,greater<int>())-T.begin();
                numA=max(numA,posA);numB=max(numB,posB);
                //cout << '*' << x << ' ' << numA << ' ' << numB << ' ' << numT << '\n';
                int cx=numA+numB+numT-posA-posB,sx=pA[numA]+pB[numB]-pA[posA]-pB[posB]+pT[numT];
                if(sx>=dC) val=x,cnt=cx,sum=sx,l=x+1;
                else r=x-1;
            }
            if(val==0 || sum<dC) return inf;
            int k=(sum-dC)/val;cnt-=k;
            //cout << "getT " << posA << ' ' << posB << ' ' << val << ' ' << sum << ' ' << cnt << '\n';
            return cnt;
        };
        
        for(int i=0;i<Q;i++){
            array<int,3> X;
            for(int j=0;j<3;j++) X[perm[j]]=qq[i][j];
            int dA=X[0],dB=X[1],dC=X[2];

            {//none
                dA-=sA,dB-=sB,dC-=sC;
                if(dA>=0 && dB>=0 && dC>=0 && dA<=sAB+sAC && dB<=sAB+sBC && dC<=sAC+sBC) res[i]=min(res[i],base);
            }
            
            {//AB+C
                dA=X[0],dB=X[1],dC=X[2];
                dC-=(sC+sAC+sBC);
                if(dC>=0){
                    int posA=getA(max(sA-dA,0)),posB=getB(max(sB-dB,0));
                    int cur=base+2*(posA+posB);
                    int mxC=pA[posA]+pB[posB];
                    int mnC = max(sA-dA,0)+max(sB-dB,0);
                    //cout << res[i] << '\n';
                    //cout << nS << '\n';
                    //cout << perm[0] << ' ' << perm[1] << ' ' << perm[2] << ' ' << dA << ' ' << dB << ' ' << dC << '\n';
                    //cout << dC << ' ' << mxC << ' ' << posA << ' ' << posB << ' ' << cur << '\n';
                    if(dC>=mnC){
                        if(dC<=mxC) res[i]=min(res[i],cur);
                        else{
                            dC-=mxC;
                            int predC=dC;
                            if(fst!=-1){
                                if(dC<=fst) res[i]=min(res[i],cur+1);
                                else{
                                    dC-=fst;
                                    res[i]=min(res[i],cur+1+2*getT(posA,posB,dC,T1,pT1));
                                }
                            }
                            dC=predC;
                            res[i]=min(res[i],cur+2*getT(posA,posB,dC,T0,pT0));
                        }
                    }
                    //cout << "end " << res[i] << '\n'; 
                }
            }
            
            
            {
                dA=X[0],dB=X[1],dC=X[2];
                dB-=(sB+sAB);dC-=(sC+sAC);
                if(dB>=0 && dC>=0 && dA<=sA){
                    int sz=sA-dA,pos=getA(sz);
                    res[i]=min(res[i],base+2*pos+1);
                    int sum=pA[pos],mx=max(sum-dC,0),val=sum-sz;
                    
                    //cout << nS << '\n';
                    //cout << pos << ' ' << sum << ' ' << sz << '\n';
                    //cout << perm[0] << ' ' << perm[1] << ' ' << perm[2] << ' ' << dA << ' ' << dB << ' ' << dC << '\n';
                    //cout << '*' << base+2*pos << '\n';
                    
                    //min(a,dB)+sum-max(a,sum-dC)>=sz
                    //find a such that val>=max(mx,a)-min(dB,a)  
                    //a<=min(mx,dB) -> mx-a<=val -> a>=mx-val
                    {
                        int l=max(0,mx-val),r=min(mx,dB);
                        if(l<=r && query(0,sA,1,l,r)<=pos){
                            //cout << "query " << l << ' ' << r << '\n'; 
                            res[i]=min(res[i],base+2*pos);
                        }
                    }
                    //a>=max(mx,db) -> val>=a-dB
                    {
                        int l=max(mx,dB),r=min(val+dB,sA);
                        if(l<=r && query(0,sA,1,l,r)<=pos){
                            //cout << "query " << l << ' ' << r << '\n';
                            res[i]=min(res[i],base+2*pos);
                        }
                    }
                    if(mx<=dB){
                        //a>=mx && a<=dB -> val>=a-a = 0
                        int l=mx,r=min(sA,dB);
                        if(l<=r && query(0,sA,1,l,r)<=pos){
                            //cout << "query " << l << ' ' << r << '\n';
                            res[i]=min(res[i],base+2*pos);
                        }
                    }
                    if(dB<=mx && val>=mx-dB){
                        int l=dB,r=min(mx,sA);
                        if(l<=r && query(0,sA,1,l,r)<=pos){
                            //cout << "query " << l << ' ' << r << '\n';
                            res[i]=min(res[i],base+2*pos);
                        }
                        //a>=dB && a<=mx -> val>=mx-dB;
                    }
                }
            }
            
            
            {
                //BC full B
                dA=X[0],dB=X[1],dC=X[2];
                dB-=(sB+sAB+sBC);dC-=sC;
                if(dB>=0 && dC>=0 && dB<=sA && dC<=sAC){
                    int pos=getA(dB);
                    res[i]=min(res[i],base+pos*2);
                }
            }
            
        }
    }while(next_permutation(perm.begin(),perm.end()));
    for(int i=0;i<Q;i++) cout << res[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
