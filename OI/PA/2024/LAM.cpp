#include<bits/stdc++.h>
using namespace std;
const int maxn = 2005;

int n,m;
char c[maxn][maxn];
int cc[maxn],cr[maxn],pc[maxn],pr[maxn];
int sc[maxn][26],sr[maxn][26];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        cin >> c[i][j];
        cc[j]++;cr[i]++;
        sc[j][c[i][j]-'A']++;
        sr[i][c[i][j]-'A']++;
    }
    vector<pair<pair<char,int>,char>> res;
    for(int t=1;t<=n+m;t++){
        bool check=false;
        for(int i=0;i<n;i++){
            if(cr[i]==-1) continue;
            while(pr[i]<m && c[i][pr[i]]=='.') pr[i]++;
            if(!cr[i] || sr[i][c[i][pr[i]]-'A']==cr[i]){
                check=true;
                if(cr[i]) res.push_back({{'R',i+1},c[i][pr[i]]});
                for(int j=0;j<m;j++){
                    char C=c[i][j];
                    if(C=='.') continue;
                    cc[j]--;sc[j][C-'A']--;
                    c[i][j]='.';
                }
                cr[i]=-1;
                break;
            }
        }
        if(check) continue;
        for(int i=0;i<m;i++){
            if(cc[i]==-1) continue;
            while(pc[i]<n && c[pc[i]][i]=='.') pc[i]++;
            if(!cc[i] || sc[i][c[pc[i]][i]-'A']==cc[i]){
                check=true;
                if(cc[i]) res.push_back({{'K',i+1},c[pc[i]][i]});
                for(int j=0;j<n;j++){
                    char C=c[j][i];
                    if(C=='.') continue;
                    cr[j]--;sr[j][C-'A']--;
                    c[j][i]='.';
                }
                cc[i]=-1;
                break;
            }
        }
    }
    cout << (int)res.size() << '\n';
    while(!res.empty()){
        auto x=res.back();res.pop_back();
        cout << x.first.first << ' ' << x.first.second << ' ' << x.second << '\n';
    }
}
