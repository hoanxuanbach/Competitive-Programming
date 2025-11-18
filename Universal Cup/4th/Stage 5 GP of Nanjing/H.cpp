#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
const int N = 5e3+5;

int f[N][N],kmp[2*N],d[N],cnt[2*N];

void solve(){
    string S;cin >> S;
    int n=(int)S.length();
    S="#"+S;

    for(int l=1;l<n;l++){
        kmp[1]=0;kmp[0]=-1;
        cnt[1]=1;cnt[0]=0;
        for(int i=2;i<=n-l;i++){
            int j=kmp[i-1];
            while(j>=0 && S[l+j+1]!=S[l+i]) j=kmp[j];
            kmp[i]=j+1;
            cnt[i]=cnt[kmp[i]]+1;
        }
        d[1]=0;d[0]=-1;
        for(int i=2;i<=n-l;i++){
            int j=d[i-1];
            while(j>=0 && S[l+j+1]!=S[l+i]) j=kmp[j];
            d[i]=j+1;
            while(d[i]>i/2) d[i]=kmp[d[i]];
            f[l][l+i]+=cnt[d[i]];
        }
    }
    for(int r=1;r<=n;r++) for(int l=r-1;l>=1;l--) f[l][r]=(f[l][r]+f[l+1][r])%mod;
    for(int l=n;l>=1;l--) for(int r=l+1;r<=n;r++) f[l][r]=(f[l][r]+f[l+1][r]+f[l][r-1]-f[l+1][r-1]+mod)%mod;
    int res=0;
    for(int r=4;r<n;r++){
        string s=S.substr(r+1,n-r)+S;
        int m=(int)s.length();
        s="$"+s;
        //cout << s << '\n';
        
        kmp[1]=0;kmp[0]=-1;
        cnt[1]=1;cnt[0]=0;
        for(int i=2;i<=m;i++){
            int j=kmp[i-1];
            while(j>=0 && s[j+1]!=s[i]) j=kmp[j];
            kmp[i]=j+1;
            cnt[i]=cnt[kmp[i]]+1;
            //cout << kmp[i] << ' ';
        }
        //cout << '\n';

        for(int l=1;l<=r;l++){
            int k=cnt[kmp[n-r+l]];
            //cout << l << ' ' << r << ' ' << k << '\n';
            res=(res+k*f[l][r])%mod;
        }
    }
    cout << res << '\n';
 }
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
