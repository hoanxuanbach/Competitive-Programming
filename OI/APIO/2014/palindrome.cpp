#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e5+5;
struct node{
    int num=0,len,slink,nxt[26];
}tree[maxn];
int ans,lst,cnt=2;
string s;
void add(int p,int c){
    while(tree[lst].len==p || (s[p]!=s[p-tree[lst].len-1])) lst=tree[lst].slink;
    if(tree[lst].nxt[c]){
        lst=tree[lst].nxt[c];
        tree[lst].num++;
        return;
    }
    tree[lst].nxt[c]=++cnt;
    tree[cnt].len=tree[lst].len+2;
    tree[cnt].num++;
    if(tree[cnt].len==1){
        tree[cnt].slink=2;lst=cnt;
        return;
    }
    lst=tree[lst].slink;
    while(tree[lst].len==p || (s[p]!=s[p-tree[lst].len-1])) lst=tree[lst].slink;
    tree[cnt].slink=tree[lst].nxt[c];lst=cnt;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> s;lst=2;
    tree[1].slink=tree[2].slink=1;
    tree[1].len=-1;tree[2].len=0;
    for(int i=0;i<(int)s.length();i++) add(i,s[i]-'a');
    for(int i=cnt;i>=2;i--){
        tree[tree[i].slink].num+=tree[i].num;
        ans=max(ans,tree[i].num*tree[i].len);
    }
    cout << ans << '\n';
}
