#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)(x).size())
#define sumof(x) accumulate(all(x), 0ll)

void solve(){
   int p, q;
   cin >> p >> q;
   string answer;
   int d=(p-q);
   if (d%2){
      d+=9;
      p-=12;
      q-=21;
      answer+="12";
   }
   function<vector<string>(int)> gen_number=[&](int x) -> vector<string> {
      if (x==0) return {"0"s};
      if (x==1) return {"1"s};
      stringstream ss; ss << x;
      string s; ss >> s;
      int sz=s.size();
      string t=s;
      for (int i=0; i<sz; ++i) t[i]=min(t[i], t[sz-i-1]);
      if (t[0]=='0'){
         t.erase(t.begin());
         for (auto &c:t) c='9';
      }
      int y; stringstream st; st << t; st >> y;
      if (x==y) return {t};
      auto ans=gen_number(x-y);
      ans.push_back(t);
      return ans;
   };
   d/=2;
   p-=d;
   if (d<0){
      d=-d;
      auto t=gen_number(d);
      for (auto &sus:t){
         answer+="+0-"s;
         answer+=sus;
      }
   }else if (d>0){
      auto t=gen_number(d);
      for (auto &sus:t){
         answer+="+"s;
         answer+=sus;
         answer+="-0"s;
      }
   }
   if (p>0){
      auto t=gen_number(p);
      for (auto &sus:t){
         answer+="+"s;
         answer+=sus;
      }
   }else if (p<0){
      p=-p;
      answer+="+0";
      auto t=gen_number(p);
      for (auto &sus:t){
         answer+="-"s;
         answer+=sus;
      }
      answer+="-0";
   }
   if (answer.empty()) answer="0";
   if (answer[0]=='+' || answer[0]=='-') answer.erase(answer.begin());
   cout << answer;
   // reverse(all(answer));
   // cout << '\n' << answer;
   assert((int)answer.size()<=1000);
   // cout << ' '  << answer.size();
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   // cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
