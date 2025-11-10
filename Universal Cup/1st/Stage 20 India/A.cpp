#include<bits/stdc++.h>
using namespace std; 

const int L=30;

void solve(){
    int n,q;cin >> n >> q;
    vector<int> a(n+1);
    vector<vector<int>> d(n+1,vector<int>(L,0));
    for(int i=1;i<=n;i++){
        cin >> a[i];
        for(int j=0;j<L;j++){
            d[i][j]=(a[i]>>j&1);
            d[i][j]+=d[i-1][j];
        }
    }

    vector<vector<array<int,3>>> f(L);
    vector<int> res(q),cnt(q),one(q),sum(q);
    for(int i=0;i<q;i++){
        int l,r;cin >> l >> r;l--;
        for(int j=L-1;j>=0;j--){
            sum[i]=sum[i]<<1|(d[l][j]!=d[r][j]);
            one[i]=one[i]<<1|(d[r][j]==d[l][j]+1);
        }
        if(!sum[i]) continue;
        int k=__lg(sum[i]);
        res[i]=(1<<(k+1))-1;
        if(res[i]==sum[i]) continue;
        f[__builtin_ctz(~sum[i])].push_back({r,l,i});
    }
    
    vector<int> pre(n+1),cur(L);
    vector<vector<pair<int,int>>> qq(n+1);
    for(int k=0;k<L;k++){
        for(int i=1;i<=n;i++) qq[i].clear();
        for(auto [r,l,id]:f[k]) qq[r].push_back({l,id});

        for(int i=0;i<L;i++) cur[i]=0;
        for(int i=1;i<=n;i++){
            if(a[i]>=(1<<k)){
                int x=__builtin_ctz((a[i]>>k)<<k);
                pre[i]=cur[x];
                cur[x]=i;
            }
            for(auto [l,id]:qq[i]){
                cnt[id]=2;
                for(int x=__lg(sum[id]),t=L;(sum[id]>>x&1) && t>=0;x--){
                    for(int j=cur[x];j>l;j=pre[j],t--){
                        if(!(a[j]&(a[j]-(1<<k))&one[id])){
                            cnt[id]=1;
                            break;
                        }
                    }
                    if(cnt[id]==1) break;
                }
            }
        }
    }

    for(int i=0;i<q;i++) cout << res[i] << ' ' << cnt[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
