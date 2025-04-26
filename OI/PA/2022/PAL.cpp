#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
int cnt[2];
signed main(){
    //freopen("PAL.INP","r",stdin);
    //freopen("PAL.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    deque<pii> dq;
    string s;cin >> s;
    for(char c:s){
        cnt[c-'a']++;
        if(dq.empty()) dq.push_back({c-'a',1});
        else if(dq.back().fi!=c-'a') dq.push_back({c-'a',1});
        else dq.back().se++;
    }
    if((cnt[0]&1) && (cnt[1]&1)){
        cout << -1 << '\n';
        return 0;
    }
    int ans=0;
    while((int)dq.size()>=2){
        if(dq.back().fi==dq.front().fi){dq.back().se--;dq.front().se--;}
        else{
            if(dq.front().se>dq.back().se){
                dq.front().se--;ans+=dq.back().se;
                dq[(int)dq.size()-2].se--;
            }
            else{
                dq.back().se--;ans+=dq.front().se;
                dq[1].se--;
            }
        }
        if(dq[(int)dq.size()-2].se==0){
            pii p=dq.back();dq.pop_back();dq.pop_back();
            if(!dq.empty()) dq.back().se+=p.se;
        }
        if((int)dq.size()>=2 && dq[1].se==0){
            pii p=dq.front();dq.pop_front();dq.pop_front();
            if(!dq.empty()) dq.front().se+=p.se;
        }
        if(!dq.empty() && dq.back().se==0) dq.pop_back();
        if(!dq.empty() && dq.front().se==0) dq.pop_front();
    }
    cout << ans << '\n';
}
