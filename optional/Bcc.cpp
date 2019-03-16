#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
const int M = 4e5;
struct Edge{ int u,v; }e[M];
int n,m,stamp,dfn[N],low[N];
int iscut[N],bccno[N];
int scnt,stk[M],bcc_cnt;
vector<int> vec[N],bcc[N];

void tarjan(int index,int fa) {
  int child=0,tmp;
  dfn[index]=low[index]=++stamp;
  for(int i=0;i<(int)vec[index].size();i++) {
    tmp=e[vec[index][i]].v;
    if(!dfn[tmp]) {
      stk[++scnt]=vec[index][i],child++;
      tarjan(tmp,index);
      low[index]=min(low[index],low[tmp]);
      if(low[tmp]>=dfn[index]) {
        iscut[index]=1;
        bcc[++bcc_cnt].clear();
        while(1) {
          int num=stk[scnt--];
          if(bccno[e[num].u]!=bcc_cnt) {
            bcc[bcc_cnt].push_back(e[num].u);
            bccno[e[num].u]=bcc_cnt;
          }
          if(bccno[e[num].v]!=bcc_cnt) {
            bcc[bcc_cnt].push_back(e[num].v);
            bccno[e[num].v]=bcc_cnt;
          }
          if(e[num].u==index && e[num].v==tmp)
            break;
        }
      }
    }
    else if(dfn[tmp]<dfn[index] && tmp!=fa) {
        stk[++scnt]=vec[index][i];
        low[index]=min(low[index], dfn[tmp]);
    }
  }
  if(fa<0 && child==1) iscut[index]=0;
}

void find_bcc() {
    // 割顶的bccno值无意义 
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    stamp=scnt=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i,-1);
}
