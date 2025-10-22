#include<bits/stdc++.h>
using namespace std; 

void solve(){
    int n,m,k;cin >> n >> m >> k;
    
    
    vector<int> p(n);
    for(int i=0;i<n;i++) cin >> p[i];
    
    vector<int> s;
    for(int i=0;i<n;i++){
        int x=upper_bound(s.begin(),s.end(),p[i])-s.begin();
        if(x==(int)s.size()) s.push_back(-1);
        s[x]=p[i];
    }
    if((int)s.size()<k){
        cout << "No\n";
        return;
    }

    for(int i=0;i<n;i++) p[i]=n-p[i];

    vector<bool> used(n);
    {
        vector<int> f(n);
        for(int i=0;i<n;i++){
            int j=i;
            while(j && p[j-1]>p[j]){
                while(j>=2 && p[j]<p[j-2] && p[j-2]<p[j-1]) swap(p[j-1],p[j]),j--;
                j--;
                while(j>=1 && p[j-1]<p[j+1] && p[j+1]<p[j]) swap(p[j-1],p[j]),j--;
            }
            f[i]=j;
        }

        int sz;
        vector<int> q;
        for(int i=n-1;i>=0;i--){
            q.push_back(p[i]);
            if(!i || p[i-1]>p[i]) k--;
            if(!k) break;
        }
        reverse(q.begin(),q.end());
        sz=(int)q.size();

        vector<int> nxt(n,-2),pre(n,-2);
        for(int i=0;i<sz;i++){
            if(!i || q[i-1]>q[i]) pre[q[i]]=-1;
            else pre[q[i]]=q[i-1];

            if(i+1==sz || q[i]>q[i+1]) nxt[q[i]]=-1;
            else nxt[q[i]]=q[i+1];
        }

        for(int i=n-1;i>=0;i--){
            int j=f[i];
            while(j<i){
                while(j+2<=i && p[j+1]<p[j+2] && p[j+2]<p[j]) swap(p[j],p[j+1]),j++;
                j++;
                while(j+1<=i && p[j]<p[j-1] && p[j-1]<p[j+1]){
                    int a=p[j],b=p[j-1],c=p[j+1];
                    //bac->bca
                    if(nxt[a]==c){
                        if(pre[b]!=-2){
                            if(nxt[b]!=-1) pre[nxt[b]]=a;
                            pre[c]=b;
                            swap(nxt[a],nxt[b]);
                        }
                        else{
                            if(pre[a]!=-1) nxt[pre[a]]=b;
                            pre[c]=b;
                            swap(nxt[a],nxt[b]);
                            swap(pre[a],pre[b]);
                        }
                    }
                    swap(p[j],p[j+1]);
                    j++;
                }
            }
        }

        for(int i=0;i<n;i++) if(pre[i]!=-2) used[i]=true;
    }

    vector<int> q;
    for(int i=0;i<n;i++) if(used[p[i]]) q.push_back(p[i]);
    int sz=(int)q.size();

    if(sz<m){
        cout << "No\n";
        return;
    }
    s.clear();
    int pos=-1;
    vector<int> g(n+1,-1),f(sz,-1);
    for(int i=0;i<sz;i++){
        q[i]=n-q[i];g[q[i]]=i;
        int x=upper_bound(s.begin(),s.end(),q[i])-s.begin();
        if(x==(int)s.size()) s.push_back(-1),pos=i;
        s[x]=q[i];
        f[i]=(x?g[s[x-1]]:-1);
    }

    while(pos!=-1) m--,g[q[pos]]=-1,pos=f[pos];
    
    vector<int> res;
    for(int i=0;i<sz;i++){
        if(g[q[i]]!=-1 && m) g[q[i]]=-1,m--;
        if(g[q[i]]==-1) res.push_back(q[i]);
    }
    cout << "Yes\n";
    for(int x:res) cout << x << ' ';
    cout << '\n';
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}