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
const int L = 30;

void solve(){
    int N;cin >> N;
    vector<int> a(L);

    vector<vector<vector<int>>> dp(L+1,vector<vector<int>>(105,vector<int>(32,0)));
    dp[0][0][31]=1;
    for(int i=1;i<=L;i++) for(int j=0;j<105;j++) for(int mask=0;mask<32;mask++){
        for(int k=0;k<=4;k++){
            int nj=(j*10+2*k+1)%105;
            int nmask=mask^(1<<k);
            dp[i][j][mask]+=dp[i-1][nj][nmask];
            dp[i][j][mask]=min(inf,dp[i][j][mask]);
        }
    }

    auto cal = [&](int s,int x){
        int mask=0,cur=0;
        for(int i=s-1;i>=x;i--){
            mask^=(1<<(a[i]/2));
            cur=(cur*10+a[i])%105;
        }
        return dp[x][cur][mask];
    };


    int s=1;
    while(s<=L){
        bool end=false;
        for(int k=1;k<=9;k+=2){
            a[s-1]=k;
            int cnt=cal(s,s-1);
            if(N>cnt) N-=cnt;
            else{
                end=true;
                break;
            }
        }
        if(end) break;
        s++;
    }
    for(int i=s-2;i>=0;i--){
        for(int k=1;k<=9;k+=2){
            a[i]=k;
            int cnt=cal(s,i);
            if(N>cnt) N-=cnt;
            else break;
        }
    }
    __int128 res=0;
    for(int i=s-1;i>=0;i--) res=res*10+a[i];
    string ret;
    while(res){
        ret+=char('0'+res%10);
        res/=10;
    }
    reverse(ret.begin(),ret.end());
    cout << ret << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
