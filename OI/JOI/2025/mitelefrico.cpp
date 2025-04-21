#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    int n,m,p;
    cin >> n >> m >> p;

    vector<array<int,3>> e;
    for(int i=0;i<m;i++){
        int a,b,c;cin >> a >> b >> c;
        e.push_back({c,a,b});
    }
    sort(e.begin(),e.end());

    int pos=0,cc=0;
    
    vector<int> cnt(n+1);
    vector<pair<int,int>> P;
    for(auto [c,a,b]:e){
        cc+=!cnt[b];
        cnt[b]++;
        while(cc>=n-1){
            cnt[e[pos][2]]--;
            cc-=!cnt[e[pos][2]];
            pos++;
        }
        if(pos){
            P.push_back({e[pos-1][0],c});
            //cout << e[pos-1][0] << ' ' << c << '\n';
        }
    }

    int q;cin >> q;
    vector<int> L(q),R(q),X(q),res(q);

    m=(int)P.size();
    for(int i=0;i<q;i++){
        cin >> L[i] >> R[i] >> X[i];
        res[i]=inf+1;
        pos=lower_bound(P.begin(),P.end(),make_pair(L[i],-inf))-P.begin();
        if(pos<m) res[i]=max(0LL,P[pos].second-R[i]);
        //cout << '*' << i << ' ' << pos << ' ' << res[i] << '\n';
    }
    for(int i=0;i<m;i++) swap(P[i].first,P[i].second);
    for(int i=0;i<q;i++){
        pos=upper_bound(P.begin(),P.end(),make_pair(R[i],inf))-P.begin();
        if(pos) res[i]=min(res[i],max(0LL,L[i]-P[pos-1].second));
        //cout << '*' << i << ' ' << pos << ' ' << res[i] << '\n';
    }
    for(int i=0;i<m;i++) swap(P[i].first,P[i].second);

    vector<pair<int,int>> qq;
    for(int i=0;i<q;i++) qq.push_back({L[i],i});
    sort(qq.begin(),qq.end());

    vector<int> com,bit(m+1,inf);
    for(int i=0;i<m;i++) com.push_back(p-P[i].second);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());


    auto update = [&](int x,int val){
        x=lower_bound(com.begin(),com.end(),x)-com.begin()+1;
        for(int i=x;i<=m;i+=(i&(-i))) bit[i]=min(bit[i],val);
    };
    auto query = [&](int x){
        x=upper_bound(com.begin(),com.end(),x)-com.begin();
        int ans=inf;
        for(int i=x;i>=1;i-=(i&(-i))) ans=min(ans,bit[i]);
        return ans;
    };

    pos=0;
    for(auto [_,id]:qq){
        while(pos<m && P[pos].first<=L[id]) update(p-P[pos].second,P[pos].second-P[pos].first),pos++;
        int mn = query(p-R[id]);
        if(mn!=inf) res[id]=min(res[id],mn-R[id]+L[id]);
    }

    for(int i=0;i<q;i++) cout << (res[i]<=X[i]?"Yes":"No") << '\n';
}