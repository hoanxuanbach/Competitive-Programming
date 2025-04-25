#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5+5;
const int B = 500;

set<int> ss;
int n,q,a[maxn];
int res[maxn],cnt[maxn],num[maxn];

void add(int x){
    num[cnt[x]]--;
    num[++cnt[x]]++;
    if(cnt[x]==B) ss.insert(x);
}
void del(int x){
    if(cnt[x]==B) ss.erase(x);
    num[cnt[x]--]--;
    num[cnt[x]]++;
}
int get(int N){
    vector<int> v;
    for(int x:ss) v.push_back(cnt[x]);
    sort(v.begin(),v.end());
    int l=0,r=0,total=0,k=0,col=0;  
    auto cal = [&](int x,int s,int d){
        int val=(x*(x+1)*s+d*(2*x+1)*s*(s-1)/2+d*d*(s-1)*s*(2*s-1)/6)/2;
        total+=val;
    };
    auto add = [&](int x,int s,int d){
        cal(x,s,d);
        cal(N-x-s*d,s,d);
    };
    for(int i=1;i<B;i++){
        col+=num[i];
        if(!num[i]) continue;
        int x=(num[i]+1)/2,y=num[i]/2;
        if(k) swap(x,y);
        add(l,x,i);add(r,y,i);
        l+=x*i;r+=y*i;k^=(num[i]&1);
    }
    col+=(int)v.size();
    for(int x:v){
        if(k) add(r,1,x),r+=x;
        else add(l,1,x),l+=x;
        k^=1;
    }
    total=col*N*(N+1)/2-total;
    return total;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    int l=1,r=0;

    vector<array<int,3>> qq(q);
    for(int i=0;i<q;i++){
        cin >> qq[i][0] >> qq[i][1];
        qq[i][2]=i;
    }
    sort(qq.begin(),qq.end(),[&](array<int,3> x,array<int,3> y){
        if(x[0]/B!=y[0]/B) return x[0]/B<y[0]/B;
        else if((x[0]/B)&1) return x[1]<y[1];
        else return x[1]>y[1];
    });
    int L=1,R=0;
    for(auto [l,r,id]:qq){
        while(R<r) add(a[++R]);
        while(L>l) add(a[--L]);
        while(R>r) del(a[R--]);
        while(L<l) del(a[L++]);
        res[id]=get(r-l+1);
    }
    for(int i=0;i<q;i++) cout << res[i] << '\n';
}