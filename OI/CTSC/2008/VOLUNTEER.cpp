#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define pdi pair<double,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 2000000005;

int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

void solve(){ 
    int n,mod,delta;
    
    int T=5;

    priority_queue<pdi,vector<pdi>,greater<pdi>> pq;
    vector<double> cost(T);
    for(int i=0;i<T;i++) cost[i]=log(i+2);

    vector<int> s(T);
    for(int i=0;i<T;i++) cin >> s[i];
    
    if(s[0]) s[2]=0;
    if(s[0] && s[1]) s[4]=0;

    cin >> mod >> delta;
    vector<pii> P;
    {
        int N=mod;
        for(int i=2;i*i<=N;i++){
            if(N%i==0){
                int d=0;
                while(N%i==0) N/=i,d++;
                P.push_back({i,d});
            }
        }
        if(N>1) P.push_back({N,1});
    }
    int sz=(int)P.size();
    auto get_crt = [&](vector<int> rem){
        int res=0;
        for(int i=0;i<sz;i++){
            auto [p,k]=P[i];
            int base=power(p,k,inf),phi=base/p*(p-1);
            res=(res+rem[i]*power(mod/base,phi,mod))%mod;
        }
        return res;
    };

    if(s[0] || s[1] || s[2]){
        vector<array<int,3>> f(T,{0,0,0});
        f[0][0]=1,f[1][1]=1,f[2][0]=2,f[3][2]=1,f[4][0]=f[4][1]=1;

        vector<array<int,3>> X;
        set<array<int,3>> ss;

        vector<array<int,3>> ord;
        for(int i=0;i<T;i++) if(s[i]){
            ss.insert(f[i]);
            pq.push({cost[i],(int)X.size()});
            X.push_back(f[i]);
        }

        int lim = 100000;
        while((int)ord.size()<lim){
            auto [d,id]=pq.top();pq.pop();
            ord.push_back(X[id]);
            for(int i=0;i<T;i++) if(s[i]){
                array<int,3> nxt=X[id];
                for(int j=0;j<3;j++) nxt[j]+=f[i][j];
                if(ss.find(nxt)!=ss.end()) continue;
                pq.push({d+cost[i],(int)X.size()});
                ss.insert(nxt);X.push_back(nxt);
            }
        }

        array<int,3> mx={0,0,0},mul={2,3,5};
        for(int i=0;i<(int)ord.size();i++) for(int j=0;j<3;j++) mx[j]=max(mx[j],ord[i][j]);
        auto check = [&](int a,int b){
            for(int i=0;i<3;i++) if(ord[b][i]<ord[a][i]) return false;
            return true;
        };

        int n;cin >> n;
        vector<int> qa(n),qb(n);
        vector<vector<int>> rem(n,vector<int>(sz,0));

        for(int i=0;i<n;i++) cin >> qa[i] >> qb[i],qa[i]--,qb[i]--;
        
        vector<array<int,3>> pw(2*lim+1,{1,1,1});
        vector<vector<vector<int>>> val(mx[0]+1,vector<vector<int>>(mx[1]+1,vector<int>(mx[2]+1)));
        vector<vector<vector<int>>> cnt(mx[0]+1,vector<vector<int>>(mx[1]+1,vector<int>(mx[2]+1)));

        for(int t=0;t<sz;t++){
            auto [p,k]=P[t];
            int base=power(p,k,inf);

            if(delta%p!=0){
                vector<int> dd(lim);

                for(int i=0;i<=mx[0];i++) for(int j=0;j<=mx[1];j++) for(int k=0;k<=mx[2];k++) cnt[i][j][k]=0,val[i][j][k]=1;

                int cmod=1;
                for(int x=1;x<=k;x++){
                    cmod*=p;
                    for(int i=1;i<=2*lim;i++) for(int j=0;j<3;j++) pw[i][j]=pw[i-1][j]*mul[j]%cmod;
                    for(int i=0;i<lim;i++){
                        int cur=delta;
                        for(int j=0;j<3;j++) cur=cur*pw[ord[i][j]][j]%cmod;
                        cur=(cur+1)%cmod;
                        if(!cur) dd[i]=x;
                    }
                }

                cmod=1;
                for(int x=0;x<k;x++){
                    int ccmod=cmod*base;
                    for(int i=1;i<=2*lim;i++) for(int j=0;j<3;j++) pw[i][j]=(__int128)pw[i-1][j]*mul[j]%ccmod;
                    for(int i=0;i<lim;i++) if(dd[i]==x){
                        int cur=delta;
                        for(int j=0;j<3;j++) cur=(__int128)cur*pw[ord[i][j]][j]%ccmod;
                        cur=(cur+1)%ccmod;
                        cur/=cmod;

                        int a=ord[i][0],b=ord[i][1],c=ord[i][2];
                        cnt[a][b][c]=x;
                        val[a][b][c]=cur;
                    }
                    cmod*=p;
                }
                for(int i=0;i<lim;i++){
                    if(dd[i]==k){
                        int a=ord[i][0],b=ord[i][1],c=ord[i][2];
                        cnt[a][b][c]=k;
                    }
                }

                for(int i=0;i<=mx[0];i++) for(int j=0;j<=mx[1];j++) for(int k=1;k<=mx[2];k++){
                    cnt[i][j][k]+=cnt[i][j][k-1];
                    val[i][j][k]=val[i][j][k]*val[i][j][k-1]%base;
                }
                for(int i=0;i<=mx[0];i++) for(int j=1;j<=mx[1];j++) for(int k=0;k<=mx[2];k++){
                    cnt[i][j][k]+=cnt[i][j-1][k];
                    val[i][j][k]=val[i][j][k]*val[i][j-1][k]%base;
                }
                for(int i=1;i<=mx[0];i++) for(int j=0;j<=mx[1];j++) for(int k=0;k<=mx[2];k++){
                    cnt[i][j][k]+=cnt[i-1][j][k];
                    val[i][j][k]=val[i][j][k]*val[i-1][j][k]%base;
                }

                for(int i=0;i<n;i++){
                    if(!check(qa[i],qb[i])) continue;
                    array<int,3> ca=ord[qa[i]],cb=ord[qb[i]];

                    int qcnt=0,qval=1,phi=base/p*(p-1);
                    for(int mask=0;mask<8;mask++){
                        int mult=1;
                        array<int,3> pos={0,0,0};

                        bool ok=true;
                        for(int j=0;j<3;j++){
                            if(mask>>j&1) mult*=-1,pos[j]=ca[j]-1;
                            else pos[j]=cb[j];
                            if(pos[j]<0) ok=false;
                        }
                        if(ok){
                            int a=pos[0],b=pos[1],c=pos[2];
                            qcnt+=mult*cnt[a][b][c];
                            if(mult==1) qval=qval*val[a][b][c]%base;
                            else qval=qval*power(val[a][b][c],phi-1,base)%base;
                        }
                    }
                    rem[i][t]=qval*power(p,qcnt,base)%base;
                    rem[i][t]=(rem[i][t]+base-1)%base;
                    rem[i][t]=rem[i][t]*power(delta,phi-1,base)%base;
                }
            }
            else{
                //Weak testcases
                assert(false);
            }
        }
        for(int i=0;i<n;i++){
            if(!check(qa[i],qb[i])){
                cout << 0 << '\n';
                continue;
            }
            else cout << get_crt(rem[i]) << '\n';
        }
    }
    else{
        vector<array<int,2>> f(T,{0,0});
        f[3][0]=1,f[4][1]=1;

        vector<array<int,2>> X;
        set<array<int,2>> ss;

        vector<array<int,2>> ord;
        for(int i=0;i<T;i++) if(s[i]){
            ss.insert(f[i]);
            pq.push({cost[i],(int)X.size()});
            X.push_back(f[i]);
        }

        int lim = 100000;
        while((int)ord.size()<lim){
            auto [d,id]=pq.top();pq.pop();
            ord.push_back(X[id]);
            for(int i=0;i<T;i++) if(s[i]){
                array<int,2> nxt=X[id];
                for(int j=0;j<2;j++) nxt[j]+=f[i][j];
                if(ss.find(nxt)!=ss.end()) continue;
                pq.push({d+cost[i],(int)X.size()});
                ss.insert(nxt);X.push_back(nxt);
            }
        }

        array<int,2> mx={0,0},mul={5,6};
        for(int i=0;i<(int)ord.size();i++) for(int j=0;j<2;j++) mx[j]=max(mx[j],ord[i][j]);
        auto check = [&](int a,int b){
            for(int i=0;i<2;i++) if(ord[b][i]<ord[a][i]) return false;
            return true;
        };

        int n;cin >> n;
        vector<int> qa(n),qb(n);
        vector<vector<int>> rem(n,vector<int>(sz,0));

        for(int i=0;i<n;i++) cin >> qa[i] >> qb[i],qa[i]--,qb[i]--;
        
        vector<array<int,2>> pw(2*lim+1,{1,1});
        vector<vector<int>> val(mx[0]+1,vector<int>(mx[1]+1));
        vector<vector<int>> cnt(mx[0]+1,vector<int>(mx[1]+1));

        for(int t=0;t<sz;t++){
            auto [p,k]=P[t];
            int base=power(p,k,inf);

            if(delta%p!=0){
                vector<int> dd(lim);

                for(int i=0;i<=mx[0];i++) for(int j=0;j<=mx[1];j++) cnt[i][j]=0,val[i][j]=1;

                int cmod=1;
                for(int x=1;x<=k;x++){
                    cmod*=p;
                    for(int i=1;i<=2*lim;i++) for(int j=0;j<2;j++) pw[i][j]=pw[i-1][j]*mul[j]%cmod;
                    for(int i=0;i<lim;i++){
                        int cur=delta;
                        for(int j=0;j<2;j++) cur=cur*pw[ord[i][j]][j]%cmod;
                        cur=(cur+1)%cmod;
                        if(!cur) dd[i]=x;
                    }
                }

                cmod=1;
                for(int x=0;x<k;x++){
                    int ccmod=cmod*base;
                    for(int i=1;i<=2*lim;i++) for(int j=0;j<2;j++) pw[i][j]=(__int128)pw[i-1][j]*mul[j]%ccmod;
                    for(int i=0;i<lim;i++) if(dd[i]==x){
                        int cur=delta;
                        for(int j=0;j<2;j++) cur=(__int128)cur*pw[ord[i][j]][j]%ccmod;
                        cur=(cur+1)%ccmod;
                        cur/=cmod;

                        int a=ord[i][0],b=ord[i][1];
                        cnt[a][b]=x;
                        val[a][b]=cur;
                    }
                    cmod*=p;
                }
                for(int i=0;i<lim;i++){
                    if(dd[i]==k){
                        int a=ord[i][0],b=ord[i][1];
                        cnt[a][b]=k;
                    }
                }

                for(int i=0;i<=mx[0];i++) for(int j=1;j<=mx[1];j++){
                    cnt[i][j]+=cnt[i][j-1];
                    val[i][j]=val[i][j]*val[i][j-1]%base;
                }
                for(int i=1;i<=mx[0];i++) for(int j=0;j<=mx[1];j++){
                    cnt[i][j]+=cnt[i-1][j];
                    val[i][j]=val[i][j]*val[i-1][j]%base;
                }

                for(int i=0;i<n;i++){
                    if(!check(qa[i],qb[i])) continue;
                    array<int,2> ca=ord[qa[i]],cb=ord[qb[i]];

                    int qcnt=0,qval=1,phi=base/p*(p-1);
                    for(int mask=0;mask<4;mask++){
                        int mult=1;
                        array<int,2> pos={0,0};

                        bool ok=true;
                        for(int j=0;j<2;j++){
                            if(mask>>j&1) mult*=-1,pos[j]=ca[j]-1;
                            else pos[j]=cb[j];
                            if(pos[j]<0) ok=false;
                        }
                        if(ok){
                            int a=pos[0],b=pos[1];
                            qcnt+=mult*cnt[a][b];
                            if(mult==1) qval=qval*val[a][b]%base;
                            else qval=qval*power(val[a][b],phi-1,base)%base;
                        }
                    }
                    rem[i][t]=qval*power(p,qcnt,base)%base;
                    rem[i][t]=(rem[i][t]+base-1)%base;
                    rem[i][t]=rem[i][t]*power(delta,phi-1,base)%base;
                }
            }
            else{
                //Weak testcases
                assert(false);
            }
        }
        for(int i=0;i<n;i++){
            if(!check(qa[i],qb[i])){
                cout << 0 << '\n';
                continue;
            }
            else cout << get_crt(rem[i]) << '\n';
        }
    }
}
/*
1 0 0 1 0
10001 2
3
1 10
2 12
4 15
*/
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}