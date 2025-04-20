#include<bits/stdc++.h>
using namespace std;
const int maxn = 55;
const int inf = 1e9;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
int N,P;
ll cc[15][15];
char c[maxn][15];
vector<char> C={'X','Y','Z'};
map<ll,pii> mp;

int build(ll mask){
    if(mp.find(mask)!=mp.end()) return mp[mask].fi;
    if(__builtin_popcountll(mask)==1) return 0;
    int step=inf,pos=-1;
    for(int i=0;i<P;i++) for(int j=0;j<3;j++){
        ll a=mask&cc[i][j],b=mask^a;
        if(!a || !b) continue;
        int val=max(build(a),build(b));
        if(val<step) step=val,pos=i*3+j;
    }
    mp[mask]={step+1,pos};
    return step+1;
}
void query(ll mask){
    if(__builtin_popcountll(mask)==1){
        for(int i=0;i<N;i++) if(mask>>i&1){
            cout << "C " << i+1 << endl;
        }
        return;
    }
    int s=mp[mask].se;
    int i=s/3,j=s%3;
    ll a=mask&cc[i][j],b=mask^a;
    cout << "Q " << i+1 << ' ' << C[j] << endl;
    int ok;cin >> ok;
    if(ok) query(a);
    else query(b);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> P;
    for(int i=0;i<N;i++) for(int j=0;j<P;j++){
        cin >> c[i][j];
        cc[j][(c[i][j]-'X')]|=(1LL<<i);
    }
    build((1LL<<N)-1);
    query((1LL<<N)-1);
}
