#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
const int inv2= (mod+1)/2;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int maxn = 5e5+5;

int n,a[maxn];

vector<vector<int>> g[10][10];
vector<int> sum[10][10];

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    
    vector<int> p(n);
    iota(p.begin(),p.end(),1);
    vector<vector<int>> table;
    map<vector<int>,int> mp;
    do{
        mp[p]=(int)table.size();
        table.push_back(p);
    }while(next_permutation(p.begin(),p.end()));
    
    for(int l=1;l<=n;l++) for(int r=l;r<=n;r++){
        vector<int> nxt((int)table.size(),-1);
        for(int i=0;i<(int)table.size();i++){
            
            int s=0;
            for(int j=l-1;j<r;j++) s+=a[table[i][j]];
            sum[l][r].push_back(s);

            vector<int> cur=table[i];
            if(next_permutation(cur.begin()+l-1,cur.begin()+r)) nxt[i]=mp[cur];
        }
        for(int i=0;i<(int)table.size();i++){
            if(nxt[i]==-2) continue;
            vector<int> ss;
            int j=i;
            ss.push_back(j);
            while(nxt[j]!=-1){
                int x=j;
                j=nxt[j];
                nxt[x]=-2;
                ss.push_back(j);
            }
            nxt[j]=-2;
            g[l][r].push_back(ss);
        }
    }

    vector<int> total((int)table.size(),0);
    total[0]++;

    int q;cin >> q;
    int mul=1;
    while(q--){
        int id,l,r;cin >> id >> l >> r;
        if(id==1){
            int x=1;
            for(int i=1;i<=r-l+1;i++) x=x*i%mod;
            for(auto v:g[l][r]){
                int S=0;
                for(int i=0;i<x;i++) S=(S+total[v[i]])%mod;
                for(int i=0;i<x;i++) total[v[i]]=S;
            }

            x=power(x,mod-2);
            mul=mul*x%mod;
        }
        else{
            int res=0;
            for(int i=0;i<(int)table.size();i++) res=(res+total[i]*sum[l][r][i])%mod;
            res=res*mul%mod;
            cout << res << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
