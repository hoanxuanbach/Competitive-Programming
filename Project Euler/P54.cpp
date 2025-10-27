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

const int S=5;
vector<array<int,2>> G;
struct poker{
    int g=0,type=-1,big=-1;
    poker(){}
    poker(vector<pii> X){
        int flush=0;
        int straight=0;

        int l=0;
        G.clear();
        sort(X.begin(),X.end());
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
};

void solve(){
    int N=1000,cnt=0;
    //cin >> N;
    for(int i=0;i<N;i++){
        vector<pii> A,B;
        for(int j=0;j<10;j++){
            char x,c;cin >> x >> c;
            pii P={-1,-1};

            if(x=='A') P.first=14;
            else if(x=='K') P.first=13;
            else if(x=='Q') P.first=12;
            else if(x=='J') P.first=11;
            else if(x=='T') P.first=10;
            else P.first=x-'0';
            P.first-=2;

            if(c=='D') P.second=2;
            else if(c=='S') P.second=0;
            else if(c=='H') P.second=3;
            else P.second=1;

            if(j<5) A.push_back(P);
            else B.push_back(P);
        }
        poker pA(A),pB(B);
        //cout << pA.type << ' ' << pB.type << '\n';
        //cout << (pB<pA?"Player 1":"Player 2") << '\n';
        cnt+=(pB<pA);
    }
    cout << cnt << '\n';
}
 
signed main(){
    freopen("54.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
