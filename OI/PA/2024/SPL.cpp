#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxn = 3e5+5;
const int inv2=(mod+1)/2;
int n,m;
vector<int> a,b,f[maxn];
vector<int> lt[maxn],rt[maxn];
int p[2*maxn];

int g(int x){
    if(x<=1) return 0;
    x=min(x-1,m);
    return (2*m-x+1)*x/2%mod;
}

void solve(int l,int r){
    vector<int> pos,s;
    for(int i=l;i<r;i++) s.push_back(a[i]<a[i+1]);
    for(int i=l+1;i<r;i++) if((a[i-1]<a[i])!=(a[i]<a[i+1])) pos.push_back(i);
    int sz=r-l;
    if(pos.empty()){
        for(int x=1;x<sz;x++){
            for(int i=1;x*(i+1)<sz && i<=m;i++){
                int k=x*(i+1)+1;
                int val=(sz-k+2)*(sz-k+1)/2%mod*(m-i+1)%mod;
                p[x]=(p[x]+val)%mod;
            }
        }
        return;
    }
    int mid=pos[(int)pos.size()/2];
    solve(l,mid);solve(mid,r);
    for(int i=1;i<=sz;i++) lt[i].clear(),rt[i].clear();
    int cur=0;
    for(int i=mid;i<r;i++){
        if(i>mid && s[i-l]==s[i-l-1]) cur++;
        else cur=1;
        for(int x:f[cur-1]) rt[x].push_back(i);
    }
    for(int i=mid-1;i>=l;i--){
        if(i<mid-1 && s[i-l]==s[i-l+1]) cur++;
        else cur=1;
        for(int x:f[cur-1]) lt[x].push_back(i);
    }
    for(int x=1;x<=sz;x++){
        int sl=(int)lt[x].size(),sr=(int)rt[x].size();
        vector<int> L(sl+1),R(sr+1);
        cur=mid-1;
        for(int i=0;i<sl;i++) L[i]=cur-lt[x][i],cur=lt[x][i];
        L[sl]=cur-l+1,cur=mid;
        for(int i=0;i<sr;i++) R[i]=rt[x][i]-cur,cur=rt[x][i];
        R[sr]=r-cur;

        for(int i=1;i<=sl;i++) p[x]=(p[x]+L[i]*R[0]%mod*g(i))%mod;
        for(int i=1;i<=sr;i++) p[x]=(p[x]+L[0]*R[i]%mod*g(i))%mod;
        R.erase(R.begin());L.erase(L.begin());
        array<int,3> T={0,0,0};
        for(int i=0;i<sr;i++){
            T[0]=(T[0]+R[i])%mod;
            T[1]=(T[1]+R[i]*i)%mod;
            T[2]=(T[2]+R[i]*i%mod*i)%mod;
        }
        int total=0;sr--;
        for(int i=0;i<sl;i++){
            if(i>=m){
                total=(total+L[i]*T[0]%mod*g(m+1)*2)%mod;
                continue;
            }
            while(sr>0 && i+sr+1>m){
                T[1]=(T[1]-R[sr]+mod)%mod;
                T[2]=(T[2]-R[sr]*(2*sr-1)%mod+mod)%mod;
                R[sr-1]=(R[sr-1]+R[sr])%mod;sr--;
            }
            int l0=L[i],l1=l0*i%mod,l2=l1*i%mod;
            total=(total+l0*T[0]%mod*2*m)%mod;
            total=(total+l0*T[1]%mod*(2*m-1))%mod;
            total=(total-l0*T[2]%mod)%mod;
            total=(total+l1*T[0]%mod*(2*m-1))%mod;
            total=(total-l1*2*T[1])%mod;
            total=(total-l2*T[0])%mod;
            total=(total+mod)%mod;
        }
        total=total*inv2%mod;
        p[x]=(p[x]+total)%mod;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=max(n,m);i++) for(int j=i;j<=max(n,m);j+=i) f[j].push_back(i);
    a.assign(n,0);
    for(int i=0;i<n;i++) cin >> a[i];
    b.assign(m,0);
    for(int i=0;i<m;i++) cin >> b[i];
    solve(0,n-1);
    swap(a,b);swap(n,m);
    solve(0,n-1);
    p[0]=(n*(n+1)/2%mod)*(m*(m+1)/2%mod)%mod;
    cout << 0 << ' ';
    for(int i=0;i<n+m-1;i++) cout << (p[i]-p[i+1]+mod)%mod << ' ';
    cout << '\n';
}
