#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
const int maxn = 1e5+5;
#define pii pair<int,int>
#define mpp make_pair
#define fi first
#define se second

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}
double rnd(){
    return pp(rng);
}

int n,x[maxn],y[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=5;test<=10;test++){
        if(test==1 || test==4 || test==3 || test==6 || test==10) continue;
        string ss=to_string(test);
        if(test<=9) ss="0"+ss;
        string inp=ss+".in";
        string out=ss+".out.txt";
        ifstream cin(inp);
        ofstream cout(out);

        cin >> n;
        for(int i=1;i<=n;i++) cin >> x[i] >> y[i];

        vector<bool> used(n+1,false);
        deque<pii> sx,sy;
        for(int i=1;i<=n;i++) sx.push_back({x[i],i}),sy.push_back({y[i],i});
        sort(sx.begin(),sx.end());
        sort(sy.begin(),sy.end());

        vector<array<int,4>> spiral;
        vector<int> c0,c1;

        while(!sx.empty()){
            int L=-1,U=-1,D=-1,R=-1;
            while(!sx.empty() && used[sx.front().se]) sx.pop_front();
            while(!sx.empty() && used[sx.back().se]) sx.pop_back();
            while(!sy.empty() && used[sy.front().se]) sy.pop_front();
            while(!sy.empty() && used[sy.back().se]) sy.pop_back();
            if(sx.empty()) break;
            L=sx.front().se;R=sx.back().se;
            D=sy.front().se;U=sy.back().se;
            if(L==D){c0.push_back(L);used[L]=true;continue;}
            if(L==U){c1.push_back(L);used[L]=true;continue;}
            if(R==U){c0.push_back(R);used[R]=true;continue;}
            if(R==D){c1.push_back(R);used[R]=true;continue;}
            spiral.push_back({L,R,U,D});
            used[L]=used[R]=used[U]=used[D]=true;
        }
        reverse(spiral.begin(),spiral.end());

        vector<pii> ans,res;

        bool last=false;
        auto add = [&](pii p){
            if(res.empty()){
                res.push_back(p);
                return;
            }
            if((int)res.size()>=2){
                bool worked=true;
                pii &A=res.back(),&B=res.end()[-2];
                if(B.fi==A.fi){
                    if(1LL*(A.se-B.se)*(p.se-A.se)>0){
                        A.se=p.se;
                        worked=true;
                    }
                }
                else if(B.se==A.se){
                    if(1LL*(A.fi-B.fi)*(p.fi-A.fi)>0){
                        A.fi=p.fi;
                        worked=true;
                    }
                }
                if(!worked && last){
                    pii &C=res.end()[-3];
                    B.fi=C.fi;A.se=B.se;
                    if(B.fi==A.fi){
                        if(1LL*(A.se-B.se)*(p.se-A.se)>0) A.se=p.se;
                    }
                    else if(B.se==A.se){
                        if(1LL*(A.fi-B.fi)*(p.fi-A.fi)>0) A.fi=p.fi;
                    }
                }
            }
            last = (p.fi!=res.back().fi && p.se!=res.back().se);
            if(p.fi!=res.back().fi) res.push_back({p.fi,res.back().se});
            if(p.se!=res.back().se) res.push_back(p);
        };
        auto add_spiral = [&](vector<array<int,4>> S){
            bool start=false;
            for(auto [L,R,U,D]:S){
                pii ld={x[L],y[D]};
                pii lu={x[L],y[U]};
                pii rd={x[R],y[D]};
                pii ru={x[R],y[U]};
                if(!start){
                    add(ld);add(lu);add(ru);add(rd);add(ld);
                    start=true;
                }
                else{
                    res.back().first=x[L];
                    if(res.back().second<=y[L]){
                        add(lu);add(ru);add(rd);add(ld);
                    }
                    else{
                        add(ld);add(rd);add(ru);add(lu);
                    }
                }
            }
        };
        auto add_chain = [&](vector<int> C,int M){
            if(C.empty()) return;
            if(M&1){
                for(int i:C) x[i]*=-1;
            }
            if(M&2){
                for(int i:C) y[i]*=-1;
            }
            sort(C.begin(),C.end(),[&](int a,int b){
                return mpp(x[a],y[a])<mpp(x[b],y[b]);
            });
            if(M&1){
                for(int i:C) x[i]*=-1;
            }
            if(M&2){
                for(int i:C) y[i]*=-1;
            }
            add(mpp(x[C[0]],y[C[0]]));
            for(int i=1;i<(int)C.size();i++){
                if((i&1)^(M>>2)) add(mpp(x[C[i-1]],y[C[i]]));
                else add(mpp(x[C[i]],y[C[i-1]]));
            }
            if((int)C.size()>1) add(mpp(x[C.back()],y[C.back()]));
        };

        for(int m0=0;m0<8;m0++) for(int m1=0;m1<8;m1++){
            vector<int> p={0,1,2};
            do{
                last=false;
                res.clear();
                add(mpp(0,0));
                for(int i=0;i<3;i++){
                    if(p[i]==2) add_spiral(spiral);
                    else if(p[i]==1) add_chain(c1,m1);
                    else if(p[i]==0) add_chain(c0,m0);
                }
                if(ans.empty() || (int)ans.size()>(int)res.size()) ans=res;
            }while(next_permutation(p.begin(),p.end()));
        }
        cout << (int)ans.size()-1 << '\n';
        for(int i=1;i<(int)ans.size();i++) cout << ans[i].fi << ' ' << ans[i].se << '\n';
    }
}
