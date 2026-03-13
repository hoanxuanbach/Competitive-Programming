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

const int T = 30;
void solve(){
    int n,k;cin >> n >> k;
    vector<int> c(n);
    for(int i=0;i<n;i++) cin >> c[i];
    
    vector<int> bit(n+1);
    auto update = [&](int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    };
    auto query = [&](int x){
        int cnt=0;
        for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
        return cnt;
    };

    int res=0,sum=0;
    for(int i=0;i<n;i++){
        sum+=query(n-c[i]);
        update(n-c[i]+1,1);
    }
    res=sum;
    auto add = [&](int i,int x){
        
        c[i]=x;
        sum+=query(n-c[i]);
        update(n-c[i]+1,1);
    };
    auto del = [&](int i){
        
        update(n-c[i]+1,-1);
        sum-=query(n-c[i]);
    };

    int mx=0,pos=-1;
    vector<int> cur;
    
    vector<int> cnt(n+1);
    auto cal = [&](){
        int total=sum;
        for(int x:cur){
            total+=query(n-x);
            cnt[x]++;
        }
        int num=1,m=0,mul=0;
        bool check=true;
        for(int x:cur){
            for(int i=1;i<=cnt[x];i++){
                m++;
                mul+=m-i;
                if(num<=k) num=num*m/i;
                if(num>k) check=false;
            }
            cnt[x]=0;
        }
        if(num>k) check=false;
        if(!check) return false;
        res+=total*num+num*mul/2;k-=num;
        return true;
    };

    for(int i=n-1;i>=0;i--){
        del(i);
        mx=max(mx,c[i]);
        cur.push_back(c[i]);
        if(c[i]<mx){
            sort(cur.begin(),cur.end());
            if(i<=n-T){
                int x=upper_bound(cur.begin(),cur.end(),c[i])-cur.begin();
                add(i,cur[x]);cur.erase(cur.begin()+x);pos=i;
            }
            else{
                vector<int> val;
                for(int x:cur) if(x>c[i] && (val.empty() || x>val.back())) val.push_back(x);
                for(int x:val){
                    add(i,x);
                    cur.erase(find(cur.begin(),cur.end(),x));
                    if(!cal()){
                        pos=i;
                        break;
                    }
                    cur.push_back(x);
                    del(i);
                }
            }
            if(pos!=-1) break;
        }
    }

    pos++;
    sort(cur.begin(),cur.end(),greater<int>());
    while(pos<=n-T){
        add(pos,cur.back());
        cur.pop_back();
        pos++;
    }   

    for(int i=pos;i<n;i++){
        vector<int> val;
        sort(cur.begin(),cur.end());
        for(int x:cur) if(val.empty() || x>val.back()) val.push_back(x);
        for(int x:val){
            add(i,x);
            cur.erase(find(cur.begin(),cur.end(),x));
            if(!cal()) break;
            cur.push_back(x);
            del(i);
        }
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
