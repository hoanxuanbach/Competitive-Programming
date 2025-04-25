#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
int n,m,p[maxn],a[maxn],bit[maxn],r[maxn],kmp[maxn];
vector<int> q;
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void update(int x,int Max,int val){
    for(int i=x;i<=Max;i+=(i&(-i))) bit[i]+=val;
}
vector<int> ans;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){int x;cin >> x;a[x]=i;}
    for(int i=1;i<=m;i++){cin >> p[i];q.push_back(p[i]);}
    sort(q.begin(),q.end());
    for(int i=1;i<=m;i++) p[i]=lower_bound(q.begin(),q.end(),p[i])-q.begin()+1;
    for(int i=1;i<=n;i++){
        r[i]=query(a[i])+1;
        update(a[i],n,1);
    }
    for(int i=1;i<=n;i++) bit[i]=0;
    kmp[0]=-1;kmp[1]=0;
    for(int i=2;i<=n;i++){
        int x=query(a[i])+1,j=kmp[i-1];
        while(j!=-1 && r[j+1]!=x){
            int nxt=kmp[j];
            for(int k=i-j;k<=i-nxt-1;k++){
                update(a[k],n,-1);
                if(a[k]<a[i]) x--;
            }
            j=kmp[j];
        }
        kmp[i]=j+1;update(a[i],n,1);
    }
    for(int i=1;i<=m;i++) bit[i]=0;
    int len=0;
    for(int i=1;i<=m;i++){
        int x=query(p[i])+1;
        while(len==n || (r[len+1]!=x)){
            int j=kmp[len];
            for(int k=i-len;k<=i-j-1;k++){
                update(p[k],m,-1);
                if(p[k]<p[i]) x--;
            }
            len=j;
        }
        len++;
        if(len==n) ans.push_back(i-n+1);
        update(p[i],m,1);
    }
    cout << (int)ans.size() << '\n';
    for(int  v:ans) cout << v << ' ';
}
/*
5 10
2 1 5 3 4
5 6 3 8 12 7 1 10 11 9
*/
