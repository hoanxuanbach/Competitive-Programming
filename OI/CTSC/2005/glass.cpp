#include<bits/stdc++.h>
using namespace std; 
#define ll long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const ll inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int M = 100000;

const int B = 200;
const int N = 50000;
int n,m;

ll total=0;
int dd[40005];


struct Block{
    int L,R,d=0;
    int cnt[M+5],num;
    void build(){
        for(int i=L;i<R;i++) cnt[dd[i]+N]=0,dd[i]+=d;
        d=0;num=0;
        for(int i=L;i<R;i++){
            cnt[dd[i]+N]++;
            if(dd[i]<0) num++;
        }
    }
    int get(int x){
        if(x<0 || x>M) return 0;
        else return cnt[x];
    }
    void add(int x,int val){
        if(x<L) return;
        if(R<=x){
            if(val==1){
                total+=B-2*num;
                d++;num-=get(N-d);
            }
            else{
                num+=get(N-d);d--;
                total-=(B-2*num);
            }
        }
        else{
            for(int i=L;i<=x;i++){
                total-=abs(dd[i]+d);
                cnt[dd[i]+N]--;
                dd[i]+=val;
                cnt[dd[i]+N]++;
                assert(dd[i]+N>=0 && dd[i]+N<=M);
                total+=abs(dd[i]+d);
            }
            build();
        }
    }
}S[205];

void add(int x,int val){
    x--;
    for(int i=0;i<B;i++) S[i].add(x,val);
}

void solve(){   
    ll K;cin >> n >> m >> K;
    for(int i=0;i<B;i++){
        S[i].L=i*B,S[i].R=(i+1)*B;
        S[i].build();
    }
    
    int res=0;
    ll area=0;
    auto update = [&](int x,ll d){
        if(x==res) area=min(area,d);
        else if(x>res) res=x,area=d;
    };

    vector<int> a(n+1),b(m+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=m;i++) cin >> b[i];
    sort(a.begin()+1,a.end());
    sort(b.begin()+1,b.end());

    for(int i=1;i<=n;i++){
        total+=a[i];
        if(total*a[i]<=K) update(i,total*a[i]);
    }
    total=0;
    for(int i=1;i<=m;i++){
        total+=b[i];
        if(total*b[i]<=K) update(i,total*b[i]);
    }
    for(int i=1;i<=m;i++) add(b[i],1);
    int p=m;
    for(int i=1;i<=n;i++){
        add(a[i],-1),total+=a[i];

        while(p && (total/2)*max(a[i],b[p])>K) add(b[p],-1),total-=b[p--];

        if(p) update(i+p,(total/2)*max(a[i],b[p]));
    }

    cout << res << ' ' << area << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}