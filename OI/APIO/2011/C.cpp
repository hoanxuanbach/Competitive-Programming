// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
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
const int maxn=1005;
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

int n,cnt,len;
string s[maxn];
bool used[maxn],cc[26];

int f(int i,int x){
    for(int j=0;j<(int)s[i].length();j++) if(s[i][j]-'A'==x) return j;
    return -1;
}

bool backtrack(int num){
    if(num<0) return true;
    if(cnt<=1) return false;

    for(int x=0;x<26;x++){
        //cout << "backtrack " << num << ' ' << x << '\n';
        if(cc[x]) continue;

        cc[x]=true;
        bool check=false;
        vector<int> del;
        for(int i=1;i<=n;i++){
            if(used[i] && f(i,x)!=-1){
                del.push_back(i);
                used[i]=false;
            }
        }
        cnt-=(int)del.size();
        if(backtrack(num-1)) check=true;
        cnt+=(int)del.size();
        for(int i:del) used[i]=true;

        if(check){
            cc[x]=false;
            continue;
        }
        for(int k=0;k<len;k++){
            del.clear();
            for(int i=1;i<=n;i++){
                if(used[i] && f(i,x)!=k){
                    del.push_back(i);
                    used[i]=false;
                }
            }
            cnt-=(int)del.size();
            if(backtrack(num)) check=true;
            cnt+=(int)del.size();
            for(int i:del) used[i]=true;
            if(check) break;
        }
        cc[x]=false;
        if(!check){
            //cout << "backtrack " << num << ' ' << cnt << ' ' << 0 << '\n';
            return false;
        }
    }
    //cout << "backtrack " << num << ' ' << cnt << ' ' << 1 << '\n';
    return true;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> s[i];
    for(len=1;len<=7;len++){
        cnt=0;
        for(int i=0;i<26;i++) cc[i]=false;
        for(int i=1;i<=n;i++) cnt+=(used[i]=((int)s[i].length()==len));
        //cout << len << ' ' << cnt << '\n';
        if(cnt && backtrack(len)){
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
