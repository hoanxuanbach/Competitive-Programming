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

int f[2][155][400005];

void solve(){
    int S;cin >> S;

    int M=1;
    for(int i=1;i<=9;i++) M*=i;

    for(int i=0;i<=S;i++) for(int x=0;x<M;x++) f[0][i][x]=inf;
    f[0][0][0]=0;

    int T=20,t=0;
    int cnt=0,cur=1;
    for(int i=0;i<T;i++){
        cout << '*' << i << endl;
        for(int s=0;s<=S;s++) for(int x=0;x<M;x++) f[t^1][s][x]=inf;
        for(int s=0;s<=S;s++) for(int x=0;x<M;x++) if(f[t][s][x]!=inf){
            for(int d=0;d<=9;d++){
                int ns=s+d;
                int nx=(x+d*cur)%M;
                int nw=f[t][s][x]+d*cnt+(x+d*cur)/M;
                if(ns<=S) f[t^1][ns][nx]=min(f[t^1][ns][nx],nw);
            }
        }

        cur*=10;
        cnt*=10;
        cnt+=cur/M;
        cur%=M;
        t^=1;
    }

    vector<int> len(S+1,inf);
    vector<string> g(S+1);

    cout << "first " << endl;
    for(int s=0;s<=S;s++) for(int x=0;x<M;x++) if(f[t][s][x]!=inf){
        int cc=M,dd=f[t][s][x],cx=x;
        for(int i=9;i>1;i--){
            cc/=i;
            while(cx>=cc) cx-=cc,dd++;
        }
        len[s]=min(len[s],dd);
    }
    cout << "second " << endl;
    for(int s=0;s<=S;s++){
        cout << s << ' ' << len[s] << endl;
        for(int x=0;x<M;x++) if(f[t][s][x]!=inf){
            int cc=M,dd=f[t][s][x],cx=x;

            string ss;
            for(int i=9;i>1;i--){
                cc/=i;
                while(cx>=cc) cx-=cc,dd++,ss+=char('0'+i-1);
            }
            reverse(ss.begin(),ss.end());

            if(dd==len[s]){
                while((int)g[s].size()<(int)ss.size()) g[s]+='9';
                while((int)ss.size()<(int)g[s].size()) ss+='9';
                g[s]=min(g[s],ss);
            }
        }
    }
    int res=0;
    for(int i=1;i<=S;i++){
        cout << i << ' ' << g[i] << ' ' << len[i] << '\n';
        for(char c:g[i]) res+=c-'0';
        res+=9*(len[i]-(int)g[i].size());
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
