/********************************************
 * Luffbee's template
 *
 *  This is a template for suffix array,
 *  including DA and SA-IS implemention.
 *
 *******************************************/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6+10;

namespace SA {
  // _maxl:   the maxium length of a string
  // wa, wb:  two arrays for temporary use
  // sa:      variable for optimize 
	const int _maxl = MAXN+5;
  int wa[_maxl], wb[_maxl], *sa;

	inline bool equal(int * s, int a, int b, int l) {
		return s[a] == s[b] && s[a+l] == s[b+l];
	}

  // bucket sort
  int bu[_maxl];
  inline void busort(int n, int * key, int * ord, int m) {
    memset(bu, 0, sizeof(int)*m);
		for (int i = 0; i < n; ++i) ++bu[key[i]];
		for (int i = 1; i < m; ++i) bu[i] += bu[i-1];
		for (int i = n-1; i >= 0; --i) sa[--bu[key[ord[i]]]] = ord[i];
  }

  // double algorithm, O(nlogn)
  template<class T>
	inline void DA(T * const str, int n, int m) {
		int * x = wa, * y = wb, p, i, l;
    for (int i = 0; i < n; ++i) x[i] = str[i], y[i] = i;
    busort(n, x, y, m);
		for (l = 1, p = 1; p < n; l <<= 1, m = p) {
			for (p = 0, i = n-l; i < n; ++i) y[p++] = i;
			for (i = 0; i < n; ++i) if (sa[i] >= l) y[p++] = sa[i]-l;
      busort(n, x, y, m);
			swap(x, y);
			for (i = p = 1, x[sa[0]] = 0; i < n; ++i) {
				x[sa[i]] = equal(y, sa[i], sa[i-1], l) ? p-1 : p++;
			}
		}
	}


  // induced-sort
  template<class T>
  inline void isort(T * const str, int const n, char * const t, int * const ord, int const ordn, int const m) {
    int i;
    memset(wb, 0, sizeof(int)*m);
    memset(sa, 0, sizeof(int)*n);
    for (i = 0; i < n; ++i) ++wb[str[i]];
    wa[0] = wb[0];
    for (i = 1; i < m; ++i) wa[i] = wa[i-1] + wb[i];
    for (i = ordn-1; i >= 0; --i) sa[--wa[str[ord[i]]]] = ord[i];
    wa[0] = 0;
    for (i = 1; i < m; ++i) wa[i] = wa[i-1] + wb[i-1];
    sa[wa[str[n-1]]++] = n-1;
    for (i = 0; i < n; ++i) if (sa[i] && t[sa[i]-1] == 1)
      sa[wa[str[sa[i]-1]]++] = sa[i]-1;
    wa[0] = wb[0];
    for (i = 1; i < m; ++i) wa[i] = wa[i-1] + wb[i];
    for (i = n-1; i >= 0; --i) if (sa[i] && t[sa[i]-1] < 1)
      sa[--wa[str[sa[i]-1]]] = sa[i]-1;
  }

  template<class T>
  inline bool equal(T * const str, const int n, int x, int y, char * const t) {
    if (!x || !y) return false;
    do {
      if (str[x] != str[y]) return false;
      ++x; ++y;
    } while (x < n && y < n && t[x] && t[y]);
    if (x < n && y < n) return t[x] == t[y] && str[x] == str[y];
    else return false;
  }

  // type: L = 1, S = -1, S* = 0
  char type[_maxl*2];
  int lms[_maxl];
  // SA-IS algorithm, O(n+m)
  template<class T>
  void SAIS(T * const str, int const n, char * const t, int * const lms, int const m) {
    int sz = 0, i, k, pre, *lms2, *s2;
    for (t[n-1] = 1, i = n-2; i >= 0; --i) {
      if (str[i] > str[i+1]) {
        t[i] = 1;
        if (t[i+1] == -1) t[i+1] = 0, lms[sz++] = i+1;
      } else if (str[i] < str[i+1]) t[i] = -1;
      else t[i] = t[i+1];
    }
    isort(str, n, t, lms, sz, m);
    for (i = 0, pre = 0, k = 0; i < n; ++i) if (!t[sa[i]]) {
        if (equal(str, n, pre, sa[i], t)) wb[sa[i]] = k-1;
        else wb[sa[i]] = k++;
        pre = sa[i];
    }
    lms2 = lms+sz;
    if (k != sz) {
      s2 = sa+n-sz;
      for (i = 0; i < sz; ++i) s2[i] = wb[lms[sz-1-i]];
      SAIS(s2, sz, t+n, lms+sz, k);
      for (i = 0; i < sz; ++i) lms2[i] = lms[sz-1-sa[i]];
    } else for (i = 0; i < sz; ++i) lms2[wb[lms[i]]] = lms[i];
    isort(str, n, t, lms2, sz, m);
  }

  template<class T>
  inline void SAIS(T * const str, int n, int m) {
    SAIS(str, n, type, lms, m);
  }

  // get suffix array from str
  // O(n+m) for SAIS, O((n+m)logn) for DA
  // str: the string
  // n:   strlen(str)
  // osa: output
  // m:   m > max{str[i], 0 <= i < n}
  template<class T>
	inline void getSA(T * const str, int n, int * osa, int m) {
    sa = osa;
    SAIS(str, n, m);
		//DA(str, n, m);
	}

  // get rank array from sa, O(n)
  // sa: a permutation of [0, n)
  // n:  length of sa
  // rk: output
  inline void getRank(int * sa, int n, int * rk) {
    for (int i = 0; i < n; ++i) rk[sa[i]] = i;
  }

  // get height array of a string, O(n);
  // str: the string
  // n:   strlen(str)
  // sa:  suffix array of str
  // rk:  rank array of str
  // h:   output
  template<class T>
  inline void getHeight(T * const str, int n, int * sa, int * rk, int * h) {
    int i, j, k=0;
    for (i = 0; i < n; h[rk[i++]] = k) {
      if (rk[i] == 0) k = 0;
      else for (k?k--:0, j=sa[rk[i]-1]; str[i+k] == str[j+k]; ++k);
    }
  }
}

char txt[MAXN];
int txtsa[MAXN];
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
  cin >> txt;
  int l = strlen(txt);
  SA::getSA(txt, l, txtsa, 128);
  for (int i = 0; i < l; ++i) {
    cout << txtsa[i] + 1 << ' ';
  } cout << '\n';
}
