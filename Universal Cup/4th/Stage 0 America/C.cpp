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

const int N=(1<<9)+5;
int f[10][2][N][N],g[10][2][N][N];

vector<int> adj[10];
int nxt(int X,int Y){
    int T=0;
    for(int i=0;i<9;i++) if(X>>i&1){
        for(int j:adj[i]) if(Y>>j&1) T|=(1<<i);
    }
    return T;
}


int F(int T,int P,int X,int Y){
    if(!Y) return 0;
    if(!T) return 1;
    if(f[T][P][X][Y]!=-1) return f[T][P][X][Y];

    int res=1,step=-1;
    if(!P){
        for(int m=Y;m;m=(m-1)&Y){
            res&=F(T,1,X,m)|F(T,1,X,Y^m);
            if(!res){
                step=m;
                break;
            }
        }
    }
    else{
        for(int i=0;i<9;i++) if(X>>i&1){
            res&=F(T-1,0,X^(1<<i),nxt(X^(1<<i),Y));
            if(!res){
                step=i;
                break;
            }
        }
    }
    f[T][P][X][Y]=res;
    g[T][P][X][Y]=step;
    return res;
}

void solve(){
    memset(f,-1,sizeof(f));
    int R,T;cin >> R >> T;
    int S=(1<<9)-1;
    for(int i=0;i<T;i++){
        int x;cin >> x;x--;
        S^=(1<<x);
    }

    for(int i=0;i<9;i++){
        if(i>=3) adj[i].push_back(i-3);
        if(i<=5) adj[i].push_back(i+3);
        if(i%3>=1) adj[i].push_back(i-1);
        if(i%3<=1) adj[i].push_back(i+1);
    }

    if(F(R,0,S,S)){
        cout << "Runner" << endl;
        int X=S,Y=S;

        vector<int> step;
        while(R){
            int M=0;cin >> T;
            for(int i=0;i<T;i++){
                int x;cin >> x;x--;
                M^=(1<<x);
            }
            M&=Y;
            if(F(R,1,X,M)){
                cout << "Yes" << endl;
                Y=M;
            }
            else{
                cout << "No" << endl;
                Y^=M;
            }
            step.push_back(Y);
            int k;cin >> k;k--;
            X^=(1<<k);Y=nxt(X,Y);
            assert(Y);
            cout << "Free" << endl;
            R--;
        }
        step.push_back(Y);
        reverse(step.begin(),step.end());
        
        int cur=__builtin_ctzll(step[0]);
        vector<int> pos={cur};
        for(int i=1;i<(int)step.size();i++){
            int jmp=-1;
            for(int x:adj[cur]){
                if(step[i]>>x&1) jmp=x;
            }
            cur=jmp;
            pos.push_back(cur);
        }
        reverse(pos.begin(),pos.end());
        for(int x:pos) cout << x+1 << ' ';
        cout << endl;
    }
    else{
        cout << "Trapper" << endl;
        int X=S,Y=S;
        while(R){
            F(R,0,X,Y);
            int M=g[R][0][X][Y];
            vector<int> ask;
            for(int i=0;i<9;i++) if(M>>i&1) ask.push_back(i+1);
            cout << (int)ask.size() << endl;
            for(int x:ask) cout << x << ' ';
            cout << endl;

            string ret;cin >> ret;
            if(ret=="Yes") Y=M;
            else Y^=M;

            F(R,1,X,Y);
            int k=g[R][1][X][Y];
            while(!(X>>k&1)) k++;
            cout << k+1 << endl;
            X^=(1<<k);Y=nxt(X,Y);

            cin >> ret;
            if(ret=="Trapped") return;
            R--;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
