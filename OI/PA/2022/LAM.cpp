#include<bits/stdc++.h>
using namespace std;
const int maxn=505;
#define pii pair<int,int>
#define fi first
#define se second
int n,m,k,p1=-1,p2=-1;
int c[maxn][maxn],col[maxn*maxn],cnt,lst[maxn][maxn];
pii pos[maxn*maxn],nxt[maxn][maxn];
bool vis[maxn][maxn];
string s;
void lt(){
    for(int i=1;i<=n;i++){
        int cur=1;
        for(int j=1;j<=m;j++){
            if(c[i][j]!=0){
                c[i][cur]=c[i][j];
                if(cur!=j) c[i][j]=0;
                cur++;
            }
        }
    }
}
void rt(){
    for(int i=1;i<=n;i++){
        int cur=m;
        for(int j=m;j>=1;j--){
            if(c[i][j]!=0){
                c[i][cur]=c[i][j];
                if(cur!=j) c[i][j]=0;
                cur--;
            }

        }
    }
}
void up(){
    for(int j=1;j<=m;j++){
        int cur=1;
        for(int i=1;i<=n;i++){
            if(c[i][j]!=0){
                c[cur][j]=c[i][j];
                if(cur!=i) c[i][j]=0;
                cur++;
            }
        }
    }
}
void down(){
    for(int j=1;j<=m;j++){
        int cur=n;
        for(int i=n;i>=1;i--){
            if(c[i][j]!=0){
                c[cur][j]=c[i][j];
                if(cur!=i) c[i][j]=0;
                cur--;
            }
        }
    }
}
void ff(char x){
    if(x=='L') lt();
    else if(x=='P') rt();
    else if(x=='G') up();
    else down();
}
signed main(){
    //freopen("LAM.INP","r",stdin);
    //freopen("LAM.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char x;cin >> x;
            if(x!='.'){col[++cnt]=(x=='C');c[i][j]=cnt;}
        }
    }
    cin >> k >> s;
    int id=k,st=-1;
    for(int i=0;i<k;i++){
        if(s[i]=='P' || s[i]=='L'){
            if(p1==-1 && st==-1) st=1;
            p1=(s[i]=='L');
        }
        else{
            if(p2==-1 && st==-1) st=2;
            p2=(s[i]=='G');
        }
        if(p1!=-1 && p2!=-1){id=i+1;break;}
    }
    string nw;
    if(st==1){
        if(p1!=-1) nw+=(p1?'L':'P');
        if(p2!=-1) nw+=(p2?'G':'D');
    }
    else{
        if(p2!=-1) nw+=(p2?'G':'D');
        if(p1!=-1) nw+=(p1?'L':'P');
    }
    for(int i=id;i<k;i++){
        if(s[i]=='P' || s[i]=='L'){
            if(nw.back()=='P' || nw.back()=='L') nw.back()=s[i];
            else nw+=s[i];
            if((int)nw.size()>=3 && nw.back()==nw[(int)nw.size()-3]) nw.pop_back();
        }
        else{
            if(nw.back()=='G' || nw.back()=='D') nw.back()=s[i];
            else nw+=s[i];
            if((int)nw.size()>=3 && nw.back()==nw[(int)nw.size()-3]) nw.pop_back();
        }
    }
    int d=((int)nw.size()-2)/4,rem=((int)nw.size()-2)%4;
    ff(nw[0]);
    if((int)nw.size()>=2) ff(nw[1]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) pos[c[i][j]]={i,j};
    }
    if(d>=1){
        for(int i=2;i<6;i++) ff(nw[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!c[i][j]) continue;
                int x=c[i][j];
                nxt[pos[x].fi][pos[x].se]={i,j};
            }
        }
        d--;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!c[i][j] || vis[i][j]) continue;
                vector<pii> p;
                int cx=i,cy=j;
                do{
                    vis[cx][cy]=true;
                    p.push_back({cx,cy});
                    pii jmp=nxt[cx][cy];
                    cx=jmp.fi;cy=jmp.se;
                }while(cx!=i || cy!=j);
                for(int i=0;i<(int)p.size();i++){
                    pii jmp=p[(i+d)%(int)p.size()];
                    lst[jmp.fi][jmp.se]=c[p[i].fi][p[i].se];
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) c[i][j]=lst[i][j];
        }
    }
    if((int)nw.size()>=2){
        for(int i=(int)nw.size()-rem;i<(int)nw.size();i++) ff(nw[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]==0) cout << '.';
            else cout << (col[c[i][j]]?'C':'B');
        }
        cout << '\n';
    }
}
