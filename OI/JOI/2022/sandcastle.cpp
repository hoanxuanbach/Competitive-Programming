#include<bits/stdc++.h>
using namespace std;
int dx[]={0,-1,0,1},
    dy[]={-1,0,1,0};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,m;cin >> n >> m;
    vector<vector<int>> a;
    if(n<m){
        a.assign(n,vector<int>(m));
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> a[i][j];
    }
    else{
        a.assign(m,vector<int>(n));
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> a[j][i];
        swap(n,m);
    }
    vector<int> com;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) com.push_back(a[i][j]);
    sort(com.begin(),com.end());
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) a[i][j]=lower_bound(com.begin(),com.end(),a[i][j])-com.begin()+1;
    vector<vector<vector<int>>> p(n+1,vector<vector<int>>(m+1,vector<int>(16,0)));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int k=0;k<16;k++){
        vector<int> v;
        for(int t=0;t<4;t++) if(k>>t&1){
            int xt=i+dx[t],yt=j+dy[t];
            if(xt<=0 || yt<=0 || xt>n || yt>m) continue;
            v.push_back(a[xt-1][yt-1]);
        }
        sort(v.begin(),v.end());
        int lt=0,rt=n*m+1;
        for(int x:v){
            if(x<a[i-1][j-1]) lt=x;
            else rt=a[i-1][j-1];
        }
        p[i][j][k]=rt-lt+p[i-1][j][k]+p[i][j-1][k]-p[i-1][j-1][k];
    }
    auto f = [&](int x,int y,int u,int v,int k){
        return p[u][v][k]-p[x-1][v][k]-p[u][y-1][k]+p[x-1][y-1][k];
    };
    long long total=n*m;
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++){
        vector<int> lt(m+1),mt(m+1),rt(m+1);
        for(int k=1;k<=m;k++){
            lt[k]=f(i,k,i,k,12)+f(j,k,j,k,6)+f(i+1,k,j-1,k,14);
            rt[k]=f(i,k,i,k,9)+f(j,k,j,k,3)+f(i+1,k,j-1,k,11);
            mt[k]=f(i,k,i,k,13)+f(j,k,j,k,7)+f(i+1,k,j-1,k,15);
            mt[k]+=mt[k-1];
        }
        map<int,int> mp;
        for(int k=1;k<=m;k++){
            total+=mp[n*m+1-(rt[k]+mt[k-1])];
            mp[lt[k]-mt[k]]++;
        }
    }
    for(int i=0;i<n;i++){
        int t=1;
        for(int j=1;j<m;j++){
            while((a[i][t]>a[i][t-1])!=(a[i][j]>a[i][j-1])) t++;
            total+=j-t+1;
        }
    }
    for(int i=0;i<m;i++){
        int t=1;
        for(int j=1;j<n;j++){
            while((a[t][i]>a[t-1][i])!=(a[j][i]>a[j-1][i])) t++;
            total+=j-t+1;
        }
    }
    cout << total << '\n';
}
