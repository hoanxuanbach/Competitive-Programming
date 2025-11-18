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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n;cin >> n;
    vector<int> a(2*n);
    for(int i=1;i<2*n;i++) cin >> a[i];
    if(a[2*n-1]) a[1]=a[2*n-1];
    else if(a[1]) a[2*n-1]=a[1];

    int L=1,R=2*n-1;
    while(L<2*n && a[L]) L++;
    while(R>0 && a[R]) R--;
    if(L>R){
        for(int i=1;i<2*n;i++) cout << a[i] << ' ';
        cout << '\n';
        return;
    }
    if(!a[1]){
        for(int i=2;i<=n;i++) cout << 1 << ' ' << i << ' ';
        cout << 1 << '\n';
        return;
    }

    vector<int> lt,rt;

    vector<bool> f(n+1);
    for(int i=1;i<L;i++){
        if(!f[a[i]]){
            lt.push_back(a[i]);
            f[a[i]]=true;
        }
        else{
            f[lt.back()]=false;
            lt.pop_back();
        }
    }

    f.assign(n+1,false);
    vector<int> par(n+1);
    for(int i=2*n-1;i>R;i--){
        if(!f[a[i]]){
            rt.push_back(a[i]);
            f[a[i]]=true;
        }
        else{
            f[rt.back()]=false;
            rt.pop_back();
        }
    }

    int X=0;
    while(X<(int)lt.size() && X<(int)rt.size() && lt[X]==rt[X]) X++;

    vector<int> v;
    while((int)lt.size()>=X){
        v.push_back(lt.back());
        lt.pop_back();
    }
    for(int i=X;i<(int)rt.size();i++) v.push_back(rt[i]);
    reverse(v.begin(),v.end());

    f.assign(n+1,false);
    for(int i=1;i<2*n;i++) f[a[i]]=true;

    for(int i=1;i<=n;i++) if(!f[i]){
        while((int)v.size()>=2 && v.end()[-2]<i){
            v.pop_back();
            a[L++]=v.back();
        }
        a[L++]=i;
        v.push_back(i);
    }
    v.pop_back();
    while(!v.empty()){
        a[L++]=v.back();
        v.pop_back();
    }

    for(int i=1;i<2*n;i++) cout << a[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}