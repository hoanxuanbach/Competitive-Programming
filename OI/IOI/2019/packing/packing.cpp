#include<bits/stdc++.h>
using namespace std;
const vector<int> TEST = {9};
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test:TEST){
        string inp=to_string(test);
        if(test<=9) inp="0"+inp;
        string out=inp+".out";
        inp+=".in";
        ifstream cin(inp);
        //ofstream cout(out);
        int n,K;cin >> n >> K;
        vector<vector<int>> f(11);
        for(int i=0;i<n;i++){
            int x;cin >> x;
            f[x].push_back(i);
        }
        auto g = [&](int x){
            int i=f[x].back();
            f[x].pop_back();
            return i;
        };

        int T=0;
        vector<int> p(n,-1);
        while((int)f[10].size()>=2){
            int a=g(10),b=g(10);
            p[a]=p[b]=T++;
        }
        if(!f[10].empty()){
            int a=g(10),b=g(1),c=g(9);
            p[a]=p[b]=p[c]=T++;
        }
        
        for(int i=9;i>=1;i--){
            while(!f[i].empty()){
                int a=g(i);
                bool add=false;
                for(int x=i;x>=1;x--){
                    if(add) break;
                    int y=20-i-x;
                    if(y>x) continue;
                    if(!f[x].empty() && !f[y].empty()){
                        int b=g(x),c=g(y);add=true;
                        p[a]=p[b]=p[c]=T++;
                        break;
                    }
                }
                if(!add){
                    f[i].push_back(a);
                    break;
                }
            }
        }
        /*Test 1,2,3,5,6
        while((int)f[6].size()>=2 && (int)f[4].size()>=2){
            int a=g(6),b=g(6),c=g(4),d=g(4);
            p[a]=p[b]=p[c]=p[d]=T++;
        }

        if(!f[7].empty()){
            if((int)f[6].size()>=2 && (int)f[1].size()>=1){
                int a=g(7),b=g(6),c=g(6),d=g(1);
                p[a]=p[b]=p[c]=p[d]=T++;
            }
        }
        if(!f[4].empty()){
            if((int)f[5].size()>=3 && !f[1].empty()){
                int a=g(4),b=g(5),c=g(5),d=g(5),e=g(1);
                p[a]=p[b]=p[c]=p[d]=p[e]=T++;
            }
        }
        
        while((int)f[6].size()>=3 && (int)f[1].size()>=2){
            int a=g(6),b=g(6),c=g(6),d=g(1),e=g(1);
            p[a]=p[b]=p[c]=p[d]=p[e]=T++;
        }
        while((int)f[5].size()>=4){
            int a=g(5),b=g(5),c=g(5),d=g(5);
            p[a]=p[b]=p[c]=p[d]=T++;
        }
        while((int)f[6].size()>=3){
            int a=g(6),b=g(6),c=g(6);
            p[a]=p[b]=p[c]=T++;
        }
        */
        /*Test 4,7,8,10
        while((int)f[7].size()>=2 && (int)f[5].size()>=1){
            int a=g(7),b=g(7),c=g(5),d=-1;
            if((int)f[1].size()>=1) d=g(1);
            p[a]=p[b]=p[c]=T;
            if(d!=-1) p[d]=T;
            T++;
        }

        while((int)f[5].size()>=4){
            int a=g(5),b=g(5),c=g(5),d=g(5);
            p[a]=p[b]=p[c]=p[d]=T++;
        }
        */

        while((int)f[8].size()>=2){
            int a=g(8),b=g(8),sum=16;
            p[a]=p[b]=T;
            for(int i=3;i>=1;i--){
                while(!f[i].empty() && (sum+i)<=20){
                    sum+=i;
                    p[g(i)]=T;
                }
            }
            T++;
        }
        while((int)f[5].size()>=4){
            int a=g(5),b=g(5),c=g(5),d=g(5);
            p[a]=p[b]=p[c]=p[d]=T++;
        }

        int sum=0;
        vector<int> v;
        for(int i=9;i>=1;i--){
            while(!f[i].empty()){
                if(sum+i>20){
                    for(int a:v) p[a]=T;
                    while(!f[1].empty() && sum<20){
                        int a=g(1);sum++;p[a]=T;
                    }
                    T++;sum=0;v.clear();
                }
                v.push_back(g(i)),sum+=i;
            }
        }
        if(!v.empty()){
            for(int a:v) p[a]=T;
            T++;
        }

        cout << inp << ' ' << K << ' ' << T << endl;
        for(int i=1;i<=10;i++) cout << (int)f[i].size() << ' ';
        cout << endl;
        
        
        ofstream fout(out);
        fout << T << '\n';
        for(int i=0;i<n;i++){
            assert(p[i]!=-1);
            fout << p[i] << ' ';
        }
        fout << '\n';
        
    }
}