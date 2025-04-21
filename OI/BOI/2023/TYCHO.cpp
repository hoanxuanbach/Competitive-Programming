#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+5;
const int inf = 9e18;

int B,P,D,N,dp[maxn],a[maxn];

int sz,bit[maxn],Min=inf;
vector<int> com;
void update(int x,int val){
    Min=min(Min,val);
    x=sz-(lower_bound(com.begin(),com.end(),x)-com.begin());
    for(int i=x;i<=sz;i+=(i&(-i))) bit[i]=min(bit[i],val);
}
int query(int x){
    x=sz-(lower_bound(com.begin(),com.end(),x)-com.begin());
    int res=inf;
    for(int i=x;i>=1;i-=(i&(-i))) res=min(res,bit[i]);
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> B >> P >> D >> N;
    for(int i=1;i<=N;i++) cin >> a[i];

    for(int i=0;i<=N;i++) com.push_back(a[i]%P);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=1;i<=sz;i++) bit[i]=inf;

    int res=inf;
    update(a[0]%P,dp[0]-(a[0]/P)*(D+P));
    for(int i=1;i<=N;i++){
        dp[i]=min(Min,query((a[i]-1)%P+1)-(D+P))+(a[i]-1)/P*(D+P)+P;
        update(a[i]%P,dp[i]-(a[i]/P)*(D+P));
    }
    for(int i=0;i<=N;i++) res=min(res,dp[i]+B-a[i]+(B-a[i]-1)/P*D);
    cout << res << '\n';
}
