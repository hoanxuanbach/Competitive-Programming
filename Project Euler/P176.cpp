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
const int inf = 4e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;
    vector<int> X={3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};

    auto get = [&](int x){
        int d=0;
        while(x%2==0) x/=2,d++;

        vector<int> A;
        for(int i=0;i<(int)X.size();i++){
            if(x%X[i]!=0) break;
            int k=0;
            while(x%X[i]==0) k++,x/=X[i];
            A.push_back(k);
        }

        int cnt=0;
        
        if(!d){
            int val=1;
            for(int k:A) val*=(2*k+1);
            val-=1;
            cnt+=val/2;
        }

        if(d){
            int val=(2*d-1);
            for(int k:A) val*=(2*k+1);
            val-=1;
            cnt+=val/2;
        }
        return cnt;
    };
    map<int,array<int,3>> mp;
    priority_queue<int,vector<int>,greater<int>> pq;
    int cur=1;
    while(cur<=inf){
        pq.push(cur);
        mp[cur]={inf,0,0};
        cur*=2;
    }
    while(!pq.empty()){
        int x=pq.top();pq.pop();
        //cout << x << ' ' << get(x) << endl;
        if(get(x)==N){
            cout << x << '\n';
            return;
        }
        auto [lst,k,i]=mp[x];
        if(x<=inf/X[i] && k<lst){
            mp[x*X[i]]={lst,k+1,i};
            pq.push(x*X[i]);
        }
        if(i+1<(int)X.size() && x<=inf/X[i+1] && k){
            mp[x*X[i+1]]={k,1,i+1};
            pq.push(x*X[i+1]);
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
