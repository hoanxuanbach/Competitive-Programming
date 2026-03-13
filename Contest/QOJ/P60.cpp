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

const int B = 340;
void solve(){
    int n,q;cin >> n >> q;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]=(a[i]-1)^a[i-1];
    }

    vector<int> C;
    for(int i=0;i<=n;i++) C.push_back(a[i]);
    sort(C.begin(),C.end());
    C.erase(unique(C.begin(),C.end()),C.end());

    int m=(int)C.size();
    for(int i=0;i<=n;i++) a[i]=lower_bound(C.begin(),C.end(),a[i])-C.begin();

    vector<int> L(q),R(q),res(q);
    for(int i=0;i<q;i++){
        cin >> L[i] >> R[i];
        int sz=R[i]-L[i]+1;
        res[i]=sz*(sz+1)/2;
    }
    
    vector<int> ord(q);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        if(L[x]/B!=L[y]/B) return L[x]/B<L[y]/B;
        else{
            if((L[x]/B)&1) return R[x]>R[y];
            else return R[x]<R[y];
        }
    });
    
    int l=1,r=0,cur=0;
    vector<vector<int>> cnt(2,vector<int>(m));
    cnt[0][a[0]]++;
    for(int id:ord){
        while(r<R[id]){
            r++;
            cur+=cnt[r&1][a[r]];
            cnt[r&1][a[r]]++;
        }
        while(l>L[id]){
            l--;
            cur+=cnt[(l-1)&1][a[l-1]];
            cnt[(l-1)&1][a[l-1]]++;
        }
        while(r>R[id]){
            cnt[r&1][a[r]]--;
            cur-=cnt[r&1][a[r]];
            r--;
        }
        while(l<L[id]){
            cnt[(l-1)&1][a[l-1]]--;
            cur-=cnt[(l-1)&1][a[l-1]];
            l++;
        }
        res[id]-=cur;
    }
    for(int i=0;i<q;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
