#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int p2[2*maxn],p3[2*maxn],inv2[2*maxn];


int n,res,a[maxn];
int mobius[maxn],p[maxn],total[maxn],f[maxn];
vector<int> d[maxn];

void solve(){
    cin >> n;

    p2[0]=p3[0]=1;
    for(int i=1;i<=2*n;i++){
        p2[i]=p2[i-1]*2%mod;
        p3[i]=p3[i-1]*3%mod;
    }
    inv2[2*n]=power(p2[2*n],mod-2);
    for(int i=2*n;i>=1;i--) inv2[i-1]=inv2[i]*2%mod;

    for(int i=1;i<=n;i++){
        cin >> a[i];
        total[a[i]]++;
    }
    for(int i=1;i<=n;i++) for(int j=i*2;j<=n;j+=i) total[i]+=total[j];

    for(int i=2;i<=n;i++) if(!p[i]) for(int j=i;j<=n;j+=i) p[j]=i;
    vector<int> A;
    for(int i=1;i<=n;i++){
        int x=i;
        mobius[i]=1;
        while(x>1){
            int j=p[x],cnt=0;
            while(x%j==0) x/=j,cnt++;
            if(cnt>1) mobius[i]=0;
            else mobius[i]*=-1;
        }
        if(mobius[i]){
            A.push_back(i);
            for(int j=i*2;j<=n;j+=i) d[j].push_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        while(!A.empty() && i*A.back()>n) A.pop_back();
        int sum_mobius = 0, sum_f = 0, val = 0;
        //cout << '*' << i << '\n';
        for(int j:A){
            sum_mobius+=mobius[j];
            f[j]=mobius[j]*p2[total[i*j]];
            sum_f=(sum_f+f[j])%mod;
            //cout << j << ' ' << f[j] << '\n';
        }
        for(int j:A){
            val=(val-2*mobius[j]%mod*sum_mobius%mod*p2[total[i*j]]%mod+mod)%mod;
        }
        val+=sum_mobius%mod*sum_mobius%mod;
        
        val+=sum_f*sum_f%mod;
        val=(val%mod+mod)%mod;
        for(int j=(int)A.size()-1;j>=0;j--){
            int x = A[j];
            //cout << "f0 " << x << ' ' << f[x] << '\n';
            for(int y:d[x]) f[x]=(f[x]+f[y]+mod)%mod;
            f[x]=(f[x]*f[x])%mod;
            //cout << "f2 " << f[x] << '\n';
        }
        for(int j=(int)A.size()-1;j>=0;j--){
            int x = A[j];
            for(int y:d[x]) f[x]=(f[x]+f[y]*mobius[y]*mobius[x]+mod)%mod;
        }

        for(int x:A){
            int c = total[i*x];
            //cout << "num " << c << ' ' << f[x] << '\n';
            val=(val+(p3[c]*inv2[2*c]%mod-1)*f[x]%mod)%mod;
        }
        //cout << val << '\n';

        res=(res+i*val)%mod;
    }
    cout << (res%mod+mod)%mod << '\n';
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
