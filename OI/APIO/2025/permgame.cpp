#include "permgame.h"
#include <bits/stdc++.h>
using namespace std;

int Alice(int N, int M, std::vector<int> U, std::vector<int> V, int S, std::vector<int> P) {
    
    auto cal = [&](){
        int cnt=0;
        for(int i=0;i<S;i++) cnt+=(P[i]==i);
        return cnt;
    };

    vector<vector<int>> cycle;
    auto build = [&]{
        cycle.clear();
        vector<bool> vis(S);
        for(int i=0;i<S;i++) if(P[i]!=i && !vis[i]){
            int u=i;
            vector<int> cc;
            do{
                cc.push_back(u);
                vis[u]=true,u=P[u];
            }while(u!=i);
            cycle.push_back(cc);
        }
        sort(cycle.begin(),cycle.end(),[&](vector<int> a,vector<int> b){
            return (int)a.size()>(int)b.size();
        });
        return S-cal();
    };

    vector<vector<int>> edge(N);
    for(int i=0;i<M;i++) edge[U[i]].push_back(V[i]),edge[V[i]].push_back(U[i]);

    bool ret=(cal()>=(S-N+1));
    for(int i=0;i<N;i++) if((int)edge[i].size()>=3) ret=true;
    if(ret) return cal();

    int root=0;
    for(int i=0;i<N;i++) if((int)edge[i].size()==1) root=i;

    vector<int> chain={root,edge[root][0]};
    while((int)chain.size()<N){
        int u=chain.back(),x=-1;
        for(int v:edge[u]) if(v!=chain[0] && v!=chain.end()[-2]) x=v;
        chain.push_back(x);
    }

    auto query = [&](vector<int> x){
        vector<int> T(N);
        for(int i=0;i<N;i++) T[chain[i]]=x[i];
        int id=Bob(T);
        swap(P[T[U[id]]],P[T[V[id]]]);
    };

    if(N==M+1 || (!(N&1) && cal()==(S-N))){
        while(build()>=N){
            vector<int> x;
            for(auto cc:cycle) x.insert(x.end(),cc.begin(),cc.end());
            x.resize(N);
            query(x);
        }
    }
    else if(N&1){
        build();

        int res=cal(),cnt=0,sz=0;
        for(auto cc:cycle){
            if((int)cc.size()&1) res++;
            else sz+=(int)cc.size();
        }
        for(auto cc:cycle) if(((int)cc.size()&1) && sz<N) cnt++,sz+=(int)cc.size();
        res-=2*(cnt/2);

        auto split = [&](vector<int> x){
            vector<int> v;
            for(int i=0;i<N;i+=2) v.push_back(x[i]);
            for(int i=N-2;i>=1;i-=2) v.push_back(x[i]);
            query(v);
        };

        while(build()>S-res){
            bool flag=false;
            for(auto cc:cycle) if((int)cc.size()&1){
                if((int)cc.size()>N){
                    split(cc);
                    flag=true;
                    break;
                }
                else if((int)cc.size()==N){
                    query(cc);
                    flag=true;
                    break;
                }
            }

            if(flag) continue;
           
            vector<int> x;
            for(auto cc:cycle) if(!((int)cc.size()&1)) x.insert(x.end(),cc.begin(),cc.end());
            while((int)x.size()>=N) x.pop_back();
            for(auto cc:cycle) if((int)cc.size()&1) x.insert(x.end(),cc.begin(),cc.end());
            x.resize(N);
            query(x);
        }
    }
    else{

        auto split = [&](vector<int> v){
            int sz=(int)v.size();
            vector<int> x;

            int pos=0;
            x.push_back(v[pos]);
            for(int i=1;i<N/2;i++){
                if(pos%(2*(sz-N)-2)==0) pos+=(sz-N);
                else pos++;
                x.push_back(v[pos]);
            }
            x.push_back(v[++pos]);
            x.push_back(v[pos-=(sz-N)]);
            for(int i=1;i<N/2-1;i++){
                if(pos%(2*(sz-N)-2)==1) pos-=(sz-N);
                else pos--;
                x.push_back(v[pos]);
            }
            query(x);
        };

        while(build()>N+1){
            bool flag=false;
            for(auto cc:cycle){
                if((int)cc.size()>=N+2){
                    split(cc);
                    flag=true;
                    break;
                }
                else if((int)cc.size()==N){
                    query(cc);
                    flag=true;
                    break;
                }
            }
            if(flag) continue;

            vector<int> x;
            for(int i=0;i<(int)cycle.size();i++){
                int k=min((int)cycle[i].size(),max(1,N-((int)cycle.size()-1-i)-(int)x.size()));
                for(int j=0;j<k;j++) x.push_back(cycle[i][j]);
            }
            x.resize(N);
            query(x);
        }
    }

    return cal();
}
