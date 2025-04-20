#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e9;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=1;test<=11;test++){
        string inp=to_string(test);
        if(test<=9) inp="0"+inp;
        string out = inp+".out";
        ifstream cin(inp);
        ofstream cout(out);

        int N;cin >> N;
        pii mV={inf,inf};
        vector<pii> V(N);
        for(int i=0;i<N;i++){
            cin >> V[i].fi >> V[i].se;
            mV=min(mV,V[i]);
        }
        int M=0;
        vector<int> S(N),T(N),F;
        vector<pii> P;
        for(int i=0;i<N;i++){
            int x=V[(i+1)%N].fi-V[i].fi;
            int y=V[(i+1)%N].se-V[i].se;
            int g=abs(__gcd(x,y));x/=g;y/=g;
            S[i]=M;
            for(int j=1;j<=g;j++){
                P.push_back({x*j,y*j}),M++;
                F.push_back(i);
            }
            T[i]=M;
        }

        vector<int> pos;
        auto get = [&](int K){
            int A=K/2,B=K-A;
            map<pii,pii> mp;
            for(int i=0;i<N;i++){
                if(B==2){
                    for(int j=i+1;j<N;j++){
                        for(int p=S[i];p<T[i];p++) for(int q=S[j];q<T[j];q++){
                            pii cc={-P[p].fi-P[q].fi,-P[p].se-P[q].se};
                            if(mp.find(cc)!=mp.end()){
                                pos={mp[cc].fi,mp[cc].se,p,q};
                                return;
                            }
                        }
                    }
                }
                else{
                    for(int p=S[i];p<T[i];p++){
                        pii cc={-P[p].fi,-P[p].se};
                        if(mp.find(cc)!=mp.end()){
                            pos={mp[cc].fi,mp[cc].se,p};
                            return;
                        }
                    }
                }
                if(A==2){
                    for(int j=0;j<i;j++){
                        for(int p=S[i];p<T[i];p++) for(int q=S[j];q<T[j];q++){
                            pii cc={P[p].fi+P[q].fi,P[p].se+P[q].se};
                            mp[cc]={q,p};
                        }
                    }
                }
                else{
                    for(int p=S[i];p<T[i];p++) mp[P[p]]={p,-1};
                }
            }
        };
        for(int k=min(4,N-1);k>=2;k--){
            get(k);
            if(!pos.empty()) break;
        }
        assert(!pos.empty());
        sort(pos.begin(),pos.end(),greater<int>());
        while(!pos.empty() && pos.back()==-1) pos.pop_back();
        reverse(pos.begin(),pos.end());
        vector<int> D(N);

        pii mA={inf,inf};
        int sA=(int)pos.size();
        vector<pii> A(sA);
        for(int i=0;i<sA;i++){
            int j=pos[i];
            D[F[j]]=(j==T[F[j]]-1?-1:j);
            A[i]=P[j];
            if(i) A[i].fi+=A[i-1].fi,A[i].se+=A[i-1].se;
            mA=min(mA,A[i]);
        }

        pii mB={inf,inf};
        int sB=0;
        vector<pii> B;
        for(int i=0;i<N;i++){
            if(D[i]<0) continue;
            else if(!D[i]) B.push_back(P[T[i]-1]);
            else B.push_back({P[T[i]-1].fi-P[D[i]].fi,P[T[i]-1].se-P[D[i]].se});
            if(sB) B[sB].fi+=B[sB-1].fi,B[sB].se+=B[sB-1].se;
            mB=min(mB,B[sB++]);
        }

        pii add={mV.fi-mA.fi-mB.fi,mV.se-mA.se-mB.se};
        for(int i=0;i<sB;i++) B[i].fi+=add.fi,B[i].se+=add.se;

        cout << sA << '\n';
        for(auto [x,y]:A) cout << x << ' ' << y << '\n';
        cout << sB << '\n';
        for(auto [x,y]:B) cout << x << ' ' << y << '\n';
    }
}
