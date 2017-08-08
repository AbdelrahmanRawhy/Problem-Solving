/*
  Different Solutions for LIS Problem
  Muhammad Magdi
*/
#include <bits/stdc++.h>

using namespace std;
const int N = 1000, M = 2e6, OO = 1000000007, EPS = 0.00000001;

int n , A[N+9], mem[N+9][N+9];

int LIS(int i = 0, int prev = n){     //Memory -> O(n^2), Time -> O(n^2)
  if(i == n)  return mem[i][prev] = 0;
  int &ret = mem[i][prev];
  if(~ret)  return ret;
  return ret = max(LIS(i+1, prev), (A[i]>A[prev]? LIS(i+1, i)+1 : 0));
}

void buildLIS(int i = 0, int prev = n){
  if(i==n)  return;
  if(~mem[i+1][prev] && mem[i][prev] == mem[i+1][prev])          //we left it
    buildLIS(i+1, prev);
  else if(~mem[i+1][i] && mem[i][prev] == mem[i+1][i]+1){     //we took it
    printf("%d ", A[i]);
    buildLIS(i+1, i);
  }
}

int dp[N+9][N+9];
int iterativeLIS(){    //Memory -> O(n^2), Time -> O(n^2)
  for(int i = 0 ; i <= n ; ++i)
    dp[n][i] = 0;
  for(int i = n-1 ; ~i ; --i)
    for(int prev = n ; ~prev ; --prev)
      dp[i][prev] = max(dp[i+1][prev], ((prev == n || A[i]>A[prev])? dp[i+1][i]+1 : 0));
  return dp[0][n];
}

int rdp[2][N+9];
int rollingLIS(){    //Memory -> O(n), Time -> O(n^2)
  int r = 0;
  for(int i = 0 ; i <= n ; ++i)     //Base Case
    rdp[r][i] = rdp[!r][i] = 0;
  for(int i = n-1 ; ~i ; --i){      //Bottom-Up Approach
    r = !r;                         //switch to the other row
    for(int prev = n ; ~prev ; --prev)
      rdp[r][prev] = max(rdp[!r][prev], ((prev == n || A[i]>A[prev])? rdp[r][i]+1 : 0));
  }
  return rdp[r][n];
}

int greadyLIS(){    //Memory -> O(n), Time -> O(nLogn)
  vector<int> ret;
  for(int i=0; i<n; i++){
    auto it = lower_bound(ret.begin(), ret.end(), A[i]);
    if(it == ret.end()) ret.push_back(A[i]);
    else *it = A[i];
  }
  return (int)ret.size();
}

void greadyLISWithBuilding(){    //Memory -> O(n), Time -> O(nLogn)
  int LIS = 0, ret[N+9] , last = OO;
  set<int> retset[N+9];
  stack<int> st;
  for(int i=0; i<n; i++){
    auto it = lower_bound(ret, ret+LIS, A[i]);
    if(it == ret+LIS)   ret[LIS++] = A[i];
    else                ret[LIS-1] = A[i];
    retset[LIS].insert(A[i]);
  }
  for(int i = LIS ; i>0 ; --i){
    auto it = retset[i].lower_bound(last);
    if(it!=retset[i].begin())   --it;
    st.push((last = *it));
  }
  /*Printing*/
  printf("Gready says LIS = %d\n", LIS);
  printf("And a valid sub-sequence is : ");
  while(!st.empty())
    printf("%d ", st.top()), st.pop();
  puts("");
}

int main(){
	// freopen("i.in", "r", stdin);
	// freopen("o.out", "w", stdout);
  memset(mem, -1, sizeof mem);
  scanf("%d", &n);
  for(int i = 0 ; i < n ; ++i)
    scanf("%d", A+i);
  printf("Memoization says LIS = %d\n", LIS());
  printf("And a valid sub-sequence is : ");
  buildLIS();
  puts("");
  printf("DP says LIS = %d\n", iterativeLIS());
  printf("With Rolling the answer is %d\n", LIS());
  greadyLISWithBuilding();
  return 0;
}

/* input samples
5
1 4 2 4 3

6
2 4 3 4 1 6
*/
