#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1e6+10;

template<class T, int LETTER, T AA=0>
struct SFXT {
  static const int _maxl=MAXN+5;
  static const int INF = _maxl+5;
  int nxt[_maxl*2][LETTER];
  int begin[_maxl*2], end[_maxl*2], link[_maxl*2];
  bool accept[_maxl*2];
  int tot, root, last;
  int str[_maxl];
  struct State {
    int no, ch, len, num;
  } act;
  int NewNode(int x) {
    begin[tot] = x;
    end[tot] = INF;
    accept[tot] = false;
    link[tot] = 0;
    memset(nxt[tot], 0, sizeof(nxt[tot]));
    return tot++;
  }
  inline void move(State & state) {
    if (state.len == 0) return;
    if (state.no == root) {
      --state.len;
      if (state.len == 0) {
        state.ch = -1;
        return;
      } else state.ch = str[last-state.num];
    } else state.no = link[state.no];
    int edge = nxt[state.no][state.ch];
    while (state.len > end[edge]-begin[edge]+1) {
      state.no = edge;
      state.len -= end[edge]-begin[edge]+1;
      state.ch = str[last-state.len-1];
      edge = nxt[state.no][state.ch];
    }
  }
  int split(int edge, int l) {
    int t = NewNode(begin[edge]);
    end[t] = begin[t] + l - 1;
    nxt[t][str[begin[edge]+l]] = edge;
    begin[edge] += l;
    return t;
  }
  void addone(int ch) {
    ++act.num; str[last++] = ch;
    int pre = -1;
    while (act.num) {
      if (ch < 0 && act.num == 1) break;
      int & edge = (act.ch == -1 ? root : nxt[act.no][act.ch]);
      if (act.len < end[edge]-begin[edge]+1) {
        int nxtch = str[begin[edge]+act.len];
        if (ch == nxtch) {
          ++act.len; break;
        } else {
          edge = split(edge, act.len);
          if (pre > 0) link[pre] = edge;
          pre = edge;
        }
      } else {
        if (pre > 0) {
          link[pre] = edge;
          pre = -1;
        }
        if (ch >= 0 && nxt[edge][ch]) {
          act = {edge, ch, 1, act.num};
          break;
        }
      }
      if (ch < 0) accept[edge] = true;
      else nxt[edge][ch] = NewNode(last-1);
      --act.num;
      move(act);
    }
    if (ch < 0) --last;
  }
  void mkaccept() {
    addone(-1);
  }
  void build(T * s, int n) {
    for (int i = 0; i < n; ++i)
      addone(s[i]-AA);
    mkaccept();
  }
  void init() {
    tot = last = 0;
    root = NewNode(0);
    end[root] = -1;
    act = {root, -1, 0, 0};
  }
  T output[_maxl];
  int outp;
  void dfs(int cur, int l) {
    if (cur == root) outp = 0;
    outp += min(end[cur]+1, last) - begin[cur];
    if (end[cur] == INF || accept[cur]) {
      cout << l-outp+1 << ' ';
    } 
    for (int i = 0; i < LETTER; ++i)
      if (nxt[cur][i]) dfs(nxt[cur][i], l);
    outp -= min(end[cur]+1, last) - begin[cur];
  }
};
SFXT<char, 26, 'a'> sfxt;
char txt[MAXN];
int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  sfxt.init();
  cin >> txt;
  int l = strlen(txt);
  sfxt.build(txt, l);
  sfxt.dfs(0, l);
  cout << '\n';
}
