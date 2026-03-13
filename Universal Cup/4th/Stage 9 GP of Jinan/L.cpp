#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
    }
    return res;
}

void solve(){
    int n,m;cin >> n >> m;
    vector<int> p(n,-1);
    for(int i=0;i+1<(int)p.size();i+=2){
        int s=(int)p.size();
        p[i]=p[i+1]=s;
        p.push_back(-1);
    }

    int s=(int)p.size();
    vector<int> a(s,n+1),b(s);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<s;i++) if(p[i]!=-1) a[p[i]]=min(a[p[i]],a[i]),b[p[i]]=max(b[p[i]],a[i]);

    vector<int> bit(n);
    auto update = [&](int x,int val){
        for(int i=x;i<n;i+=(i&(-i))) bit[i]+=val;
    };
    auto query = [&](int x){
        int cnt=0;
        for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
        return cnt;
    };
    for(int i=1;i<n;i++) update(i,b[n+i-1]);

    auto fix = [&](int x,int val){
        while(p[x]!=-1){
            int nx=p[x];
            int add=-b[nx];
            a[x]=val;
            b[nx]=max(a[x],a[x^1]);
            val=min(a[x],a[x^1]);
            add+=b[nx];
            update(nx-n+1,add);
            x=nx;
        }
        a[x]=val;
    };

    for(int i=0;i<m;i++){
        char op;int x,y;cin >> op >> x >> y;
        if(op=='C'){
            x--;y--;
            int d=a[x];
            fix(x,a[y]);
            fix(y,d);
        }
        else{
            cout << query(y)-query(x-1) << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
