#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
#define pii pair<int,int>
vector<int> x[15],a[15],d[15];
char c;
void ins(int p,int q){x[p].push_back(q);x[q].push_back(p);}
void add(int p,int q){a[p].push_back(q);}
void del(int p,int q){d[p].push_back(q);}
int len,pos[maxn],pe,p10[maxn],pre[maxn];
void print(){
    for(int i=0;i<len;i++){
        if(p10[i]==-1) cout << char(pos[i]);
        else cout << char(pos[i]+'0');
    }
    cout << "#\n";
    return;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    ins(0,6);ins(0,9);ins(6,9);ins(2,3);ins(3,5);
    del(8,0);del(7,1);del(8,6);del(8,9);del(9,3);del(9,5);del(6,5);
    add(0,8);add(1,7);add(3,9);add(5,9);add(6,8);add(9,8);add(5,6);
    int l=0,eq=1;
    while(cin >> c){
        if(c=='#') break;
        if(c>='0' && c<='9'){
            pos[len]=c-'0';
            pre[len]=eq;
        }
        else{
            pos[len]=c;p10[len]=-1;
            if(len>l) p10[len-1]=1;
            for(int i=len-2;i>=l;i--) p10[i]=p10[i+1]*10;
            if(c=='='){pe=1;eq=-1;}
            else if(c=='+'){
                if(pe) eq=-1;
                else eq=1;
            }
            else if(c=='-'){
                if(pe) eq=1;
                else eq=-1;
            }
            l=len+1;
        }
        len++;
    }
    p10[len-1]=1;
    for(int i=len-2;i>=l;i--) p10[i]=p10[i+1]*10;
    int res=0;
    for(int i=0;i<len;i++){
        if(p10[i]==-1) continue;
        res+=pre[i]*p10[i]*pos[i];
    }
    if(res==0){
        print();
        return 0;
    }
    for(int i=0;i<len;i++){
        for(int k:x[pos[i]]){
            int s=res+pre[i]*p10[i]*(k-pos[i]);
            if(s==0){
                pos[i]=k;
                print();
                return 0;
            }
        }
        for(int j=0;j<len;j++){
            if(p10[i]==-1 || p10[j]==-1 || i==j) continue;
            for(int k1:a[pos[i]]){
                for(int k2:d[pos[j]]){
                    int s=res+pre[i]*p10[i]*(k1-pos[i])+pre[j]*p10[j]*(k2-pos[j]);
                    if(s==0){
                        pos[i]=k1;pos[j]=k2;
                        print();return 0;
                    }
                }
            }
        }
    }
    cout << "No\n";
}