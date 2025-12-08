#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int inf = 1e18;
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}


void solve(){
    int n;string s;cin >> n >> s;
    int fa=0,fb=0,f=0;
    for(char c:s){
        if(c=='a') fa++;
        else if(c=='b') fb++;
    }
    if(n==1){
        cout << (s[0]=='.'?"alice":"bob") << '\n';
        return;
    }
    int X=fa-fb;
    fa=fb=f=0;
    if(s[1]!='.' && s[0]=='.') s[0]=((s[1]-'a')^1)+'a';
    if(s[n-2]!='.' && s[n-1]=='.') s[n-1]=((s[n-2]-'a')^1)+'a';
    
    if(s[0]=='a') fa++;
    else if(s[0]=='b') fb++;
    else f++;
    if(s[n-1]=='a') fa++;
    else if(s[n-1]=='b') fb++;
    else f++;

    if(f==1) fa++;
    else if(f==2) fa++,fb++;

    int Y=0;
    if(fa==2) Y=1;
    if(fb==2) Y=-1;
    cout << (Y>X?"alice":"bob") << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}


