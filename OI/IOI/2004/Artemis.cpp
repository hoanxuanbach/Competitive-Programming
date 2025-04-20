#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define val fi.se
const int maxn = 20005;

int N,T;
piii p[maxn];
vector<int> com;
int c0[maxn],c1[maxn],num[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> T;
    for(int i=1;i<=N;i++){
        cin >> p[i].fi.fi >> p[i].val;p[i].se=i;
        com.push_back(p[i].val);
    }
    sort(com.begin(),com.end());
    for(int i=1;i<=N;i++) p[i].val=lower_bound(com.begin(),com.end(),p[i].val)-com.begin()+1;
    sort(p+1,p+N+1);
    int mn=N+1,a=-1,b=-1;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++) num[i]+=p[j].val<=p[i].val;
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++) c0[j]=c0[j-1]+(p[j].val<=p[i].val);
        for(int j=1;j<=N;j++) c1[j]=0;
        for(int j=1;j<=i;j++) c1[p[j].val]++;
        for(int j=1;j<=N;j++) c1[j]+=c1[j-1];
        for(int j=1;j<=i;j++){
            int total=num[i]+num[j]-c0[j]-c1[p[j].val]+1;
            if(total>=T && total<mn) mn=total,a=i,b=j;
        }
    }
    cout << p[a].se << ' ' << p[b].se << '\n';
}
