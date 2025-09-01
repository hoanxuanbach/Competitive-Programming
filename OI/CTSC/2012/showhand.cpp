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

const int S=5,T=13,M=52;
vector<array<int,2>> G;
struct poker{
    int g=0,type=-1,big=-1,mask=0;
    poker(){}
    poker(int Mask,vector<pii> &X){
        mask=Mask;
        int flush=0;
        int straight=0;

        int l=0;
        G.clear();
        for(int i=1;i<S;i++){
            if(X[i].second==X[i-1].second) flush++;
            if(X[i].first==X[i-1].first+1) straight++;
            if(X[i].first!=X[l].first){
                G.push_back({i-l,X[l].first});
                l=i;
            }
        }
        G.push_back({S-l,X[l].first});
        sort(G.begin(),G.end(),greater<array<int,2>>());
        if(straight==S-2 && X[S-1].first==12 && X[0].first==0 && X[S-2].first==3){
            straight++;
            G.erase(G.begin());
            G.push_back({1,-1});
        } 
        for(int i=0;i<S;i++){
            if(G[0][1]==X[i].first){
                big=X[i].second;
                break;
            }
        }

        int K=24;
        for(int i=0;i<(int)G.size();i++){
            g+=(1LL<<K)*((G[i][0]-1)*16+(G[i][1]+1));
            K-=6;
        }

        if(flush==S-1 && straight==S-1) type=1;
        else if(flush==S-1) type=4;
        else if(straight==S-1) type=5;
        else if(G[0][0]==4) type=2;
        else if(G[0][0]==3 && G[1][0]==2) type=3;
        else if(G[0][0]==3) type=6;
        else if(G[0][0]==2 && G[1][0]==2) type=7;
        else if(G[0][0]==2) type=8;
        else type=9;
    };
    void print(){
        int K=24,sum=0;
        while(sum<S){
            int a=(g>>K)&63;
            cout << a/16+1 << ' ' << a%16-1 << endl;
            sum+=a/16+1;
            K-=6;
        }
    }
    friend bool operator<(poker &A,poker &B){
        if(A.type!=B.type) return A.type>B.type;
        else if(A.g!=B.g) return A.g<B.g;
        else return A.big>B.big;
    }
}P[2600000];
int num,cnt[300005];
int nxt[300005][52];

int N;
vector<pii> cur;
void build(int mask,int x,int k){
    if(k==S){
        P[N++]=poker(mask,cur);
        return;
    }
    if(x==M) return;
    cur.push_back({x/4,x%4});
    build(mask|(1LL<<x),x+1,k+1);
    cur.pop_back();
    build(mask,x+1,k);
}

void solve(){
    build(0,0,0);
    sort(P,P+N);
    int A=0,B=0;
    int n;cin >> n;
    for(int i=0;i<n;i++){
        int x,y;cin >> x >> y;
        if(x==1) x=14;
        x-=2;y--;
        A|=1LL<<(x*4+y);
        //cout << "A " << x << ' ' << y << endl;
    }
    for(int i=1;i<n;i++){
        int x,y;cin >> x >> y;
        if(x==1) x=14;
        x-=2;y--;
        B|=1LL<<(x*4+y);
        //cout << "B " << x << ' ' << y << endl;
    }
    int total=1;
    for(int i=2*n;i<=2*S;i++) total*=(M-i+1);
    for(int i=1;i<=S-n;i++) total/=i;
    for(int i=1;i<=S-n+1;i++) total/=i;

    int res=0;
    for(int i=0;i<N;i++){
        int mask=P[i].mask;
        vector<int> pos;
        while(mask){
            int t=__builtin_ctzll(mask);
            mask&=(mask-1);
            pos.push_back(t);
        }

        function<void(int,int,int)> cal = [&](int u,int j,int k){
            if(j==S){
                if(k&1) res-=cnt[u];
                else res+=cnt[u];
                return;
            }
            if(k<S-1){
                if(!nxt[u][pos[j]]) nxt[u][pos[j]]=++num;
                cal(nxt[u][pos[j]],j+1,k+1);
            }
            cal(u,j+1,k);
        };
        if((A&P[i].mask)==A){
            //cout << "A" << endl;
            //P[i].print();
            cal(0,0,0);
        }
        function<void(int,int,int)> add = [&](int u,int j,int k){
            if(j==S){
                cnt[u]++;
                return;
            }
            if(k<S-1){
                if(!nxt[u][pos[j]]) nxt[u][pos[j]]=++num;
                add(nxt[u][pos[j]],j+1,k+1);
            }
            add(u,j+1,k);
        };

        if((B&P[i].mask)==B){
            //cout << "B" << endl;
            //P[i].print();
            add(0,0,0);
        }
    }
    int g=__gcd(res,total);
    cout << res/g << "/" << total/g << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

/*
5
1 1
2 1
3 1
4 1
5 1
1 4
13 4
12 4
11 4
10 4
*/