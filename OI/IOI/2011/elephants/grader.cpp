#include "elephants.h"
#include <stdio.h>
#include <stdlib.h>
#include "elephants.cpp"
#define MAX_N 1000000
#define MAX_M 1000000

static int n,l,m;
static int x[MAX_N];
static int ii[MAX_M];
static int yy[MAX_M];
static int sol[MAX_M];

inline
void my_assert(int e) {if (!e) abort();}

void read_input()
{
  int i;
  my_assert(3==scanf("%d %d %d",&n,&l,&m));
  for(i=0; i<n; i++)
    my_assert(1==scanf("%d",&x[i]));
  for(i=0; i<m; i++)
    my_assert(3==scanf("%d %d %d",&ii[i],&yy[i],&sol[i]));
}

int main()
{
  int i, ans;

  read_input();
  init(n,l,x);
  for(i=0; i<m; i++) {
    ans = update(ii[i],yy[i]);
    if(ans==sol[i])continue;
      printf("Incorrect.  In %d-th move, answered %d (%d expected).\n",
	     i+1, ans, sol[i]);
    return 0;
  }
  printf("Correct.\n");
  return 0;
}
