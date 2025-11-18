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

void solve(){
    int N;cin >> N;cin.ignore();
    vector<pair<string,int>> S;

    int n=-1;
    for(int i=0;i<N;i++){
        string s;getline(cin,s);
        
        int K=-1;
        string A;
        for(char c:s){
            if(c>='0' && c<='9'){
                if(K==-1) A+=c;
                else K=c-'0';
            }
            else if(K==-1) K=0;
        }
        n=(int)A.size();
        S.push_back({A,K});
        cout << A << ' ' << K << '\n';
    }

    vector<pair<string,vector<int>>> A,B;
    int m=n/2;n-=m;

    string cur;
    vector<int> cnt(N);
    function<void(int)> dfs = [&](int i){
        if(i==m){
            A.push_back({cur,cnt});
            /*
            if(cur[0]=='3'){
                cout << cur << '\n';
                for(int j=0;j<N;j++) cout << cnt[j] << ' ';
                cout << '\n';
            }
            */
            return;
        }
        for(int x=0;x<=9;x++){
            bool ok=true;
            for(int j=0;j<N;j++){
                if(S[j].first[i]==char('0'+x)) cnt[j]++;
                if(cnt[j]>S[j].second) ok=false;
            }
            cur+=char('0'+x);
            if(ok) dfs(i+1);
            cur.pop_back();
            for(int j=0;j<N;j++){
                if(S[j].first[i]==char('0'+x)) cnt[j]--;
            }
        }
    };

    dfs(0);
    swap(A,B);
    swap(n,m);
    for(int i=0;i<N;i++) reverse(S[i].first.begin(),S[i].first.end());
    dfs(0);

    map<vector<int>,string> mp;
    for(auto [s,v]:A){
        reverse(s.begin(),s.end());
        for(int i=0;i<N;i++) v[i]=S[i].second-v[i];
        mp[v]=s;
    }

    for(auto [s,v]:B){
        if(mp.find(v)!=mp.end()){
            cout << s << mp[v] << '\n';
            return;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
