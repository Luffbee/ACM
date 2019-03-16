#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
const int M = 4e5+10;
struct Edge{ int u,v; }e[M];
int n,m,stamp,dfn[N],low[N];
int bccno[N],bcc_cnt;
vector<int> vec[N],bcc[N];
bool g[N][N],isbridge[M];

void tarjan(int index,int fa) {
  int tmp;
  dfn[index]=low[index]=++stamp;
  for(int i=0;i<(int)vec[index].size();i++) {
    tmp=e[vec[index][i]].v;
    if(!dfn[tmp]) {
      tarjan(tmp,index);
      low[index]=min(low[index],low[tmp]);
      if(low[tmp]>dfn[index])
        isbridge[vec[index][i]]
          =isbridge[vec[index][i]^1]=1;
    }
    else if(dfn[tmp]<dfn[index] && tmp!=fa) {
      low[index]=min(low[index], dfn[tmp]);
} } }

void dfs(int index) {
  dfn[index]=1;
  bccno[index]=bcc_cnt;
  for(int i=0;i<(int)vec[index].size();i++) {
    int tmp=vec[index][i];
    if(isbridge[tmp]) continue;
    if(!dfn[e[tmp].v]) dfs(e[tmp].v);
} }

void find_ebcc() {
  bcc_cnt=stamp=0;
  memset(dfn,0,sizeof(dfn));
  memset(low,0,sizeof(low));
  memset(isbridge,0,sizeof(isbridge));
  memset(bccno,0,sizeof(bccno));
  memset(bcc,0,sizeof(bcc));
  for(int i=1;i<=n;i++)
    if(!dfn[i]) tarjan(i, -1);
  memset(dfn,0,sizeof(dfn));
  for(int i=1;i<=n;i++) if(!dfn[i]) {
      bcc_cnt++; dfs(i);
} }
