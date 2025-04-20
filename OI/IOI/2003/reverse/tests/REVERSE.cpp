#include<bits/stdc++.h>
using namespace std;
const int S=29;
const int M=10;
int n,R[10],C[300];
bool used[10];
int L[]={8,44,101,173,257};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=1;test<=16;test++){
        string inp="";
        if(test<=9) inp+="0";
        inp+=to_string(test);
        ifstream fin(inp);
        fin >> n;
        inp="reverse-out-"+inp+".txt";
        ofstream cout(inp);
        cout << "FILE reverse " << test << '\n';

        for(int i=1;i<M;i++) R[i]=used[i]=0;
        memset(C,0,sizeof(C));

        int d=0;
        R[0]=-100;
        if(n<=L[0]){
            for(int i=1;i<M;i++) R[i]=i-1;
        }
        else if(n<=L[1]){
            d=1;
            R[9]=n;
            for(int i=8;i>0;i--) R[i]=max(0,R[i+1]-(d*(9-i)+1));
        }
        else if(n<=L[2]){
            d=2;
            R[9]=n;
            R[8]=R[9]-d-1;
            for(int i=7;i>0;i--) R[i]=max(0,R[i+1]-d*(9-i)-(8-i));
        }
        else if(n<=L[3]){
            d=3;
            R[9]=n;
            R[8]=R[9]-d-1;
            R[7]=R[8]-2*d-1;
            for(int i=6;i>0;i--) R[i]=max(0,R[i+1]-6*(8-i));
        }
        else{
            d=4;
            R[9]=n;
            R[8]=R[9]-d-1;
            R[7]=R[8]-2*d-1;
            for(int i=6;i>0;i--) R[i]=max(0,R[i+1]-9*(8-i));
        }

        for(int i=1;i<M;i++){
            C[R[i]]++;
            cout << R[i] << " \n"[i==M-1];
        }
        auto P = [&](int pos){
            assert(R[pos]==n);
            cout << "P " << pos << '\n';
            used[pos]=1;n--;
        };
        auto S = [&](int a,int b){
            cout << "S " << a << ' ' << b << '\n';
            C[R[b]]--;
            R[b]=R[a]+1;
            C[R[b]]++;
        };
        while(true){
            int cur=0;
            while(cur<10 && R[cur]!=n) cur++;
            P(cur);

            if(n<0) break;
            int x=0;
            while(x<=n && !C[n-x]) x++;
            int pos=0;
            for(int i=1;i<M;i++) if(R[i]==n-x) pos=i;
            if(pos && x>0){
                S(pos,cur);
                for(int i=1;i<x;i++) S(cur,cur);
            }
            int k=d-x;pos=0;
            if(k==d){
                for(int i=1;i<M;i++){
                    bool cc=1;
                    for(int j=1;j<=d;j++) if(C[R[i]+j]) cc=0;
                    if(!cc) continue;
                    if(R[i]>=R[pos] && R[i]+d<n && !C[R[i]+d] && !C[R[i]+d+1]) pos=i;
                }
            }
            else{
                for(int i=1;i<M;i++){
                    bool cc=1;
                    for(int j=1;j<=d;j++) if(C[R[i]+j]) cc=0;
                    if(!cc) continue;
                    if(R[i]+d<n && R[i]>R[pos] && !C[R[i]+d] && used[i]) pos=i;
                }
                cur=pos;
            }
            //cout << '*' << n << ' ' << pos << ' ' << k << '\n';
            if(pos && k>0){
                S(pos,cur);
                for(int i=1;i<k;i++) S(cur,cur);
            }
        }
    }
}
