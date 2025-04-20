#include "mars.h"
#include "mars.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>
#include <bitset>

using namespace std;

static void WA(string msg)
{
	cout << "WA: " << msg << endl;
	exit(0);
}

static long long to_longlong(string s)
{
  long long ans=0;
  for(int i=(int)s.size()-1;i>=0;i--)
    ans=(ans*2)+s[i]-'0';
  return ans;
}

int n;
char s[55][55];
bool vis[55][55];
int DX[]={0,0,1,-1},
    DY[]={1,-1,0,0};

void DFS(int x,int y){
    vis[x][y]=1;
    for(int t=0;t<4;t++){
        int xt=x+DX[t],yt=y+DY[t];
        if(xt<0 || yt<0 || xt>2*n || yt>2*n || vis[xt][yt] || s[xt][yt]!='1') continue;
        DFS(xt,yt);
    }
}


int main()
{
	int t;
	assert(scanf("%d",&t) == 1);
	while(t--)
	{
		assert(scanf("%d",&n) == 1);

		for(int i = 0; i < 2*n+1; i++)
			for(int j = 0; j < 2*n+1; j++)
				vis[i][j]=0,assert(scanf(" %c",&s[i][j]) == 1);

        int res=0;
        for(int i=0;i<=2*n;i++) for(int j=0;j<=2*n;j++) if(!vis[i][j] && s[i][j]=='1'){
            res++;DFS(i,j);
        }

		vector <vector<string>> h(2*n+1, vector<string>(2*n+1, string(100 ,'0')));
		for(int i = 0; i < 2*n+1; i++)
			for(int j = 0; j < 2*n+1; j++)
				h[i][j][0] = s[i][j];

		vector <vector<string>> subarr(3, vector<string>(3));
		for(int k = 0; k < n; k++)
		{
			int m = 2*(n-k-1);
			for(int i = 0; i <= m; i++)
			{
				for(int j = 0; j <= m; j++)
				{
                    //cout << k << ' ' << i << ' ' << j << endl;
					for(int y = 0; y < 3; y++)
					{
						for(int x = 0; x < 3; x++)
						{
							subarr[y][x] = h[i+y][j+x];
						}
					}
					h[i][j] = process(subarr, i, j, k, n);
                    //cout << h[i][j] << endl;
					if(h[i][j].size() != 100) WA("Invalid return length");
					for(int l = 0; l < 100; l++)
						if(h[i][j][l] != '0' && h[i][j][l] != '1') WA("Invalid return");
				}
			}
		}
        cout << res << '\n';
		printf("%lld\n",to_longlong(h[0][0]));
	}
}
/*
1
10
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
*/
