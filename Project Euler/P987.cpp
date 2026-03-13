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
#define i128 __int128

void solve(){
    int K;cin >> K;

    int T=0;
    vector<vector<pii>> adj;
    map<vector<pii>,int> mp;
    vector<pair<vector<pii>,int>> st;

    auto add = [&](vector<pii> P){
        sort(P.begin(),P.end());
        if(mp.find(P)==mp.end()){
            st.push_back({P,T});
            adj.emplace_back();
            mp[P]=T++;
        }
        return mp[P];
    };

    vector<pii> cur;
    add(cur);
    for(int i=1;i<=4;i++){
        cur.push_back({1,i});
        add(cur);
    }

    while(!st.empty()){
        auto [P,x]=st.back();st.pop_back();
        
        //cout << "dfs ";
        //for(auto [x,y]:P) cout << "{" << x << ' ' << y << "}";
        //cout << endl;

        int sz=(int)P.size();
        for(int d=0;sz+d<=4;d++){
            
            vector<pii> nP;
            vector<bool> used(5);
            function<void(int)> backtrack = [&](int i){
                if(i==sz+d){
                    int nx=add(nP);
                    adj[x].push_back({nx,d});
                    return;
                }
                for(int j=(i<=sz?1:nP.back().second+1);j<=4;j++) if(!used[j]){

                    pii X;
                    if(i<sz){
                        X=P[i];X.first++;
                        if(X.second!=j) X.second=0;    
                    }
                    else X={1,j};
                    if(X.first==5 && X.second!=0) continue;
                    
                    if(X.first!=5) nP.push_back(X);
                    used[j]=true;
                    backtrack(i+1);
                    used[j]=false;
                    if(X.first!=5) nP.pop_back();
                }
            };

            backtrack(0);
        }
    }

    //cout << T << endl;

    int M=13;
    auto cal = [&](int s){
        if(s>K) return (i128)0;
        vector<vector<vector<i128>>> dp(M,vector<vector<i128>>(T,vector<i128>(K+1,0)));

        i128 cnt=0;
        dp[0][s][s]=1;
        for(int i=0;i<M-1;i++) for(int x=0;x<T;x++) for(int k=0;k<=K;k++) 
            for(auto [y,d]:adj[x]) if(k+d<=K) dp[i+1][y][k+d]+=dp[i][x][k];

        for(auto [P,x]:mp){
            bool ok=true;
            vector<int> S;
            for(auto [a,b]:P){
                if(a!=4) ok=false;
                S.push_back(b);
            }
            if(!ok) continue;

            int sz=(int)S.size();
            if(sz>4-s) continue;
            int mul=0;
            
            vector<bool> used(5);
            function<void(int)> backtrack = [&](int i){
                if(i==sz){
                    mul++;
                    return;
                }
                for(int j=s+1;j<=4;j++) if(!used[j] && S[i]!=j){
                    used[j]=true;
                    backtrack(i+1);
                    used[j]=false;
                }
            };
            backtrack(0);


            cnt+=mul*dp[M-1][x][K];
        }

        return cnt;
    };

    i128 res=0,mul=1;
    for(int x=0;x<=4;x++){
        res+=mul*cal(x);
        mul=mul*(4-x)/(x+1);
    }
    string ans;
    while(res) ans+=char('0'+res%10),res/=10;
    reverse(ans.begin(),ans.end());
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
