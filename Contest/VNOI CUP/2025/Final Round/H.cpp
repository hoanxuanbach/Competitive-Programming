#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2=(mod+1)/2;
const int maxn = 2e5+5;
const int maxa = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

const int B = 340;

void solve(){   
    int n,k;cin >> n >> k;
    vector<int> p(n);
    for(int i=0;i<n;i++) cin >> p[i];

    vector<int> f(n+1),c(n),t(n+1),d(n+1),jmp(n+1);
    vector<vector<int>> s(n);

    for(int i=0;i<n;i++) f[p[i]]=i;
    set<int> ss;
    for(int i=0;i<n;i++) ss.insert(i);
    for(int i=1;i<=n;i++){
        int id=f[i];
        auto it=ss.lower_bound(id);
        int pos=*it;
        t[i]=c[pos];
        jmp[i]=pos;
        s[c[pos]++].push_back(i);
        while(it!=ss.begin()){
            it=prev(it);
            if(c[*it]<c[pos]) it=ss.erase(it);
            else break;
        }
    }

    vector<int> q;
    for(int i=0;i<n;i++){
        vector<int> val;
        for(int j=0;j<n;j++){
            if(i>=(int)s[j].size()) break;
            val.push_back(s[j][i]);
        }
        reverse(val.begin(),val.end());
        for(int x:val) q.push_back(x);
    }

    vector<int> num(n+1);
    for(int i=n;i>=1;i--){
        d[i]=num[t[i]]=max(num[t[i]]+1,1LL);
        num[t[i]+1]--;
    }

    if(p==q) cout << -1 << '\n';
    else if(!k){
        for(int x:q) cout << x << ' ';
        cout << '\n';
    }
    else{
        vector<queue<int>> qq(n+1);
        

        vector<int> g(n+1,0);
        vector<vector<int>> cc(n);
        for(int i=1;i<=n;i++) cc[jmp[i]].push_back(i);

        vector<int> mx(n+1),num(n+1);

        auto build = [&](int id){
            int l=max(1LL,id*B),r=min(n,id*B+B-1);
            int lst=0;num[id]=0;
            for(int i=l;i<=r;i++){
                if(g[i]==0) continue;
                if(t[i]>lst){
                    lst=t[i];
                    if(g[i]==2) num[id]=t[i];
                }
            }
            mx[id]=lst;
        };
        auto query = [&](int x){
            int cur=0,id=x/B;
            for(int i=0;i<id;i++) cur=max(cur,mx[i]);
            int l=max(1LL,id*B),r=min(n,id*B+B-1);
            for(int i=l;i<=x;i++) if(g[i]!=0) cur=max(cur,t[i]);
            for(int i=x+1;i<=r;i++){
                if(g[i]!=0){
                    if(cur<t[i]){
                        cur=t[i];   
                        if(g[i]==2) return true;
                    }
                }
            }
            for(int i=id+1;i<=(n/B);i++){
                if(cur<num[i]) return true;
                cur=max(cur,mx[i]);
            }
            return false;
        };
        for(int i=0;i<=n/B;i++) build(i);

        int x=-1;
        for(int i=n-1;i>=0;i--){
            for(int j:cc[i]) g[j]=1,build(j/B);
            g[p[i]]=2,build(p[i]/B);
            if(query(p[i])){
                x=i;
                break;
            }
        }

        {
            //cout << '*' << x << '\n';
            for(int i=0;i<=n;i++) while(!qq[i].empty()) qq[i].pop();
            vector<int> nxt(n+1,-1),pre(n+1,-1);

            int mx=0,lst=0;
            bool check=false;

            for(int i=1;i<=n;i++){
                if(f[i]<x){
                    if(jmp[i]<x) continue;
                    assert(t[i]==mx);
                    qq[mx+1].push(qq[mx].front());
                    qq[mx].pop();mx++;
                }
                else{
                    if(t[i]==0){
                        qq[1].push(i);
                        mx=max(mx,1LL);
                        nxt[lst]=i;
                        pre[i]=lst;
                        lst=i;
                    }
                    else if(t[i]==mx && i>p[x] && !check){
                        check=true;
                        int k=nxt[0];
                        nxt[0]=i;pre[i]=0;
                        pre[k]=i;nxt[i]=k;
                        
                        qq[mx+1].push(qq[mx].front());
                        qq[mx].pop();mx++;
                    }
                    else{
                        //cout << i << ' ' << t[i] << ' ' << d[i] << '\n';
                        while((int)qq[t[i]].size()>d[i]) qq[t[i]].pop();
                        int k=qq[t[i]].front();qq[t[i]].pop();
                        qq[t[i]+1].push(k);
                        int l=pre[k];
                        nxt[l]=i;nxt[i]=k;
                        pre[i]=l;pre[k]=i;
                        mx=max(mx,t[i]+1);
                    }
                }
            }
            assert(check);

            for(int i=0;i<x;i++) cout << p[i] << ' ';
            int i=nxt[0];
            while(i!=-1){
                cout << i << ' ';
                i=nxt[i];
            }
            cout << '\n';
            return;
        }
        assert(false);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}