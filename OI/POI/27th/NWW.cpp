#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define maxa 2500
const int inf=1e18;
int prime[maxa+5],pp[maxa+5],n,cur,up[maxa+5][maxa+5];
pii res;
vector<pii> p[maxa+5];
vector<int> pw[maxa+5];
void check2(int n){
    int d=sqrt(n);
    while(d*(d+1)<n) d++;
    while(d*(d+1)>n) d--;
    if(d*(d+1)==n) res=min(res,{d,d+1});
}
void check3(int n){
    int d=pow(n,1.0/3);
    while(d*(d+1)*(d+2)<n) d++;
    while(d*(d+1)*(d+2)>n) d--;
    if(d*(d+1)*(d+2)==n && d%2==1) res=min(res,{d,d+2});
    d=pow(2*n,1.0/3);
    while(d*(d+1)*(d+2)<2*n) d++;
    while(d*(d+1)*(d+2)>2*n) d--;
    if(d*(d+1)*(d+2)==2*n && d%2==0) res=min(res,{d,d+2});
}
void check4(int n){
    int d=pow(2*n,1.0/4);
    while(d*(d+1)*(d+2)*(d+3)<2*n) d++;
    while(d*(d+1)*(d+2)*(d+3)>2*n) d--;
    if(d*(d+1)*(d+2)*(d+3)==2*n && d%3!=0) res=min(res,{d,d+3});
    d=pow(6*n,1.0/4);
    while(d*(d+1)*(d+2)*(d+3)<6*n) d++;
    while(d*(d+1)*(d+2)*(d+3)>6*n) d--;
    if(d*(d+1)*(d+2)*(d+3)==6*n && d%3==0) res=min(res,{d,d+3});
}
void check5(int n){
    int d=pow(2*n,1.0/5);
    while(d*(d+1)*(d+2)*(d+3)*(d+4)<2*n) d++;
    while(d*(d+1)*(d+2)*(d+3)*(d+4)>2*n) d--;
    if(d*(d+1)*(d+2)*(d+3)*(d+4)==2*n && d%3==1 && d%2!=0) res=min(res,{d,d+4});
    d=pow(4*n,1.0/5);
    while(d*(d+1)*(d+2)*(d+3)*(d+4)<4*n) d++;
    while(d*(d+1)*(d+2)*(d+3)*(d+4)>4*n) d--;
    if(d*(d+1)*(d+2)*(d+3)*(d+4)==4*n && d%3==1 && d%4==2) res=min(res,{d,d+4});
    d=pow(8*n,1.0/5);
    while(d*(d+1)*(d+2)*(d+3)*(d+4)<8*n) d++;
    while(d*(d+1)*(d+2)*(d+3)*(d+4)>8*n) d--;
    if(d*(d+1)*(d+2)*(d+3)*(d+4)==8*n && d%3==1 && d%4==0) res=min(res,{d,d+4});
    d=pow(6*n,1.0/5);
    while(d*(d+1)*(d+2)*(d+3)*(d+4)<6*n) d++;
    while(d*(d+1)*(d+2)*(d+3)*(d+4)>6*n) d--;
    if(d*(d+1)*(d+2)*(d+3)*(d+4)==6*n && d%3!=1 && d%2!=0) res=min(res,{d,d+4});
    d=pow(12,1.0/5)*pow(n,1.0/5);
    while(d*(d+1)*(d+2)*(d+3)/12*(d+4)<n) d++;
    while(d*(d+1)*(d+2)*(d+3)/12*(d+4)>n) d--;
    if(d*(d+1)*(d+2)*(d+3)/12*(d+4)==n && d%3!=1 && d%4==2)res=min(res,{d,d+4});
    d=pow(24,1.0/5)*pow(n,1.0/5);
    while(d*(d+1)*(d+2)*(d+3)/12*(d+4)/2<n) d++;
    while(d*(d+1)*(d+2)*(d+3)/12*(d+4)/2>n) d--;
    if(d*(d+1)*(d+2)*(d+3)/12*(d+4)/2==n && d%3!=1 && d%4==0)res=min(res,{d,d+4});
}
bool add(int x,bool c){
    int mul=1;
    for(pii v:p[x]){
        mul*=pw[v.first][max(0LL,v.second-pp[v.first])];
    }
    if(cur<=n/mul || c){
        cur*=mul;
        for(pii v:p[x]) pp[v.first]=max(pp[v.first],v.second);
        return true;
    }
    return false;
}
void del(int l,int r){
    for(pii v:p[l]){
        if(v.second<pp[v.first]) continue;
        int d=up[v.first][r-l];
        cur/=pw[v.first][v.second-d];pp[v.first]=d;
    }
}
void solve(){
    cin >> n;res={LLONG_MAX,LLONG_MAX};
    check2(n);check3(n);check4(n);check5(n);
    int r=2;cur=1;
    for(int i=1;i<=maxa;i++) pp[i]=0;
    for(int i=1;i<=maxa;i++){
        while(r<=maxa+1){
            if(r==i+1 || r==i){add(r,true);r++;}
            else if(cur==n) break;
            else if(add(r,false)) r++;
            else break;
        }
        if(cur==n){
            res=min(res,{i,r-1});
            break;
        }
        del(i,r-1);
    }
    if(res.first==LLONG_MAX) cout << "NIE\n";
    else cout << res.first << ' ' << res.second << '\n';
    return;
}
void getup(int pm){
    int cur=1;
    for(int i=1;i<=maxa+2;i++){
        up[pm][i]=up[pm][i-1];
        if(i%(cur*pm)==0){up[pm][i]++;cur*=pm;}
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int i=2;i<=maxa+1;i++){
        if(prime[i]==0){
            for(int j=i;j<=maxa+1;j+=i) prime[j]=i;
            pw[i].push_back(1);
            while(pw[i].back()<=inf/i) pw[i].push_back(pw[i].back()*i);
            getup(i);
        }
        int d=i;
        while(d>1){
            int j=prime[d],num=0;
            while(d%j==0){d/=j;num++;}
            p[i].push_back({j,num});
        }

    }
    int t;cin >> t;
    while(t--) solve();
}
