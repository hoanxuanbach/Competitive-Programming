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
#define int unsigned long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=1035;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;
const int S=62*24;

int n,a[maxn];

int get(int x,int d){
    return (x>>(d*8))&((1<<8)-1);
}

void encode(){
    cin >> n;
    string s;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        bool check=false;
        for(int j=0;j<4;j++){
            int x=get(a[i],j),y=get(a[i],7-j);
            if(x!=y){
                if(x>y){
                    a[i]-=(x<<(j*8))+(y<<((7-j)*8));
                    a[i]+=(x<<((7-j)*8))+(y<<(j*8));
                    s+='1';
                }
                else s+='0';
                check=true;
                break;
            }
        }
        if(!check) s+='0';
    }
    while((int)s.size()<=S) s+='0';
    for(int i=0;i<24;i++){
        string cur=s.substr(i*62,62);
        cur.insert(cur.begin()+7,'1');cur+='0';
        for(int j=0;j<64;j++) a[n+i+1]+=(cur[j]-'0')*1ULL<<j;
    }
    cout << n+24 << '\n';
    for(int i=1;i<=n+24;i++) cout << a[i] << ' ';
    cout << '\n';
}

int rev(int x){
    int res=0;
    for(int i=0;i<8;i++){
        int a=get(x,7-i);
        res+=(a<<(8*i));
    }
    return res;
}

void decode(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    n-=24;
    string s;
    for(int i=0;i<24;i++){
        string cur;
        int d=a[n+i+1];
        if(d>>63&1) d=rev(d);
        for(int j=0;j<64;j++) cur+=(d&1)+'0',d>>=1;
        cur.pop_back();cur.erase(cur.begin()+7);
        s+=cur;
    }
    for(int i=1;i<=n;i++){
        int d=s[i-1]-'0';
        for(int j=0;j<4;j++){
            int x=get(a[i],j),y=get(a[i],7-j);
            if(x!=y){
                if(x>y){
                    a[i]=rev(a[i]);
                    swap(x,y);
                }
                if(d){
                    a[i]-=(x<<(8*j))+(y<<(8*(7-j)));
                    a[i]+=(y<<(8*j))+(x<<(8*(7-j)));
                }
                break;
            }
        }
    }
    for(int i=1;i<=n;i++) cout << a[i] << ' ';
    cout << '\n';
}

void Rm(){
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        int t=rng()%2;
        if(t) a[i]=rev(a[i]);
    }
    cout << n << '\n';
    for(int i=1;i<=n;i++) cout << a[i] << ' ';
    cout << '\n';
}

void solve(){
    string s;cin >> s;
    if(s=="encode") encode();
    else if(s=="decode") decode();
    else Rm();
}

signed main(){
    //freopen("L.INP","r",stdin);
    //freopen("L.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

