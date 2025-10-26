#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int maxn=1005;
const int Max=100;

struct Piece{
    vector<vector<int>> c;
    int n,m,cnt;
    void rot(){
        vector<vector<int>> nc(m,vector<int>(n,0));
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) nc[j][n-1-i]=c[i][j];
        swap(n,m);swap(nc,c);
    }
};
void print(int mask){
    if(mask==-1){
        cout << -1 << '\n';
        return;
    }
    cout << mask << '\n';
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            int id=i*5+j;
            if(mask>>id&1) cout << '#';
            else cout << '.';
        }
        cout << '\n';
    }
}
map<char,Piece> mp;
void init(){
    mp['I']={
        {
            {1,1,1,1}
        },
        1,4,2
    };
    mp['L']={
        {
            {1,0},
            {1,0},
            {1,1}
        },
        3,2,4
    };
    mp['O']={
        {
            {1,1},
            {1,1}
        },
        2,2,1
    };
    mp['T']={
        {
            {1,1,1},
            {0,1,0}
        },
        2,3,4
    };
    mp['Z']={
        {
            {1,1,0},
            {0,1,1}
        },
        2,3,2
    };
}
int eval(int mask){
    if(mask==-1) return inf;
    else return __builtin_popcount(mask);
}

int try_move(int mask,int x,int y,Piece P){
    for(int i=0;i<P.n;i++)for(int j=0;j<P.m;j++){
        if(!P.c[i][j]) continue;
        int pos=(x+i)*5+(y+j);
        if(mask>>pos&1) return -1;
        mask|=(1<<pos);
    }
    vector<int> c(5,0),r(5,0);
    int mc=0,mr=0;
    for(int i=0;i<5;i++){
        mc|=(1<<(5*i));
        mr|=(1<<i);
    }
    for(int i=0;i<5;i++){
        c[i]=(mc&mask)==mc;
        r[i]=(mr&mask)==mr;
        mc<<=1;mr<<=5;
    }
    mc>>=5;mr>>=25;
    int D=(1<<25)-1;
    for(int i=0;i<5;i++){
        if(c[i]) mask&=(D^mc);
        if(r[i]) mask&=(D^mr);
        mc<<=1;mr<<=5;
    }
    return mask;
}

int get_move(int mask,char c,bool fout){
    if(mask==-1){
        if(fout) assert(false);
        return -1;
    }
    int nmask=-1;
    int px=-1,py=-1,pt=-1;
    Piece cur=mp[c];
    for(int t=0;t<cur.cnt;t++){
        for(int x=0;x<=5-cur.n;x++) for(int y=0;y<=5-cur.m;y++){
            int M=try_move(mask,x,y,cur);
            if(eval(M)<eval(nmask)){
                nmask=M;
                px=x,py=y,pt=t;
            }
        }
        cur.rot();
    }
    if(fout){
        assert(nmask!=-1);
        for(int i=0;i<pt;i++) cur.rot();
        vector<vector<char>> cc(5,vector<char>(5));
        for(int i=0;i<5;i++) for(int j=0;j<5;j++) cc[i][j]=((mask>>(i*5+j)&1)?'#':'.');
        for(int i=0;i<cur.n;i++) for(int j=0;j<cur.m;j++){
            if(cur.c[i][j]) cc[px+i][py+j]='*';
        }
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++) cout << cc[i][j];
            cout << endl;
        }
    }
    return nmask;
}

vector<int> dp[maxn],trace[maxn];
char C[maxn][2];

void prepare(){
    int n;cin >> n;
    dp[0].push_back(0);
    trace[0].push_back(-1);
    for(int i=0;i<n;i++){
        char x,y;cin >> x >> y;
        C[i+1][0]=x;C[i+1][1]=y;
        vector<pii> p;
        for(int j=0;j<(int)dp[i].size();j++){
            p.push_back({get_move(dp[i][j],x,0),j<<1});
            p.push_back({get_move(dp[i][j],y,0),j<<1|1});
        }
        sort(p.begin(),p.end(),[](pii a,pii b){
            return eval(a.fi)<eval(b.fi);
        });
        for(int j=0;j<min((int)p.size(),Max);j++){
            dp[i+1].push_back(p[j].fi);
            trace[i+1].push_back(p[j].se);
        }
    }
    int pos=0;
    string res;
    for(int i=n;i>=1;i--){
        int x=trace[i][pos];
        res+=C[i][x&1];
        pos=(x>>1);
    }
    reverse(res.begin(),res.end());
    cout << res << '\n';
}
void play(){
    int n;cin >> n;
    int cur=0;
    for(int i=1;i<=n;i++){
        char x;cin >> x;
        cur=get_move(cur,x,1);
    }
}

void solve(){
    init();
    string s;cin >> s;
    if(s=="prepare") prepare();
    else play();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}