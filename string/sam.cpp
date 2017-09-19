#include<iostream>
#include<map>
#include<cstring>

using namespace std;
typedef long long LL;

const int MAXN = 1e5;

class SAM
{
public:
	// ELE:		the type of elements
	typedef char ELE;
	static const int LETTER = 26; // the size of alphabet
	static const char AA = 'a';	// the first letter of the alphabet
	// _maxl:	the max length of the string
	static const int _maxl = MAXN;
	int link[_maxl*2+5], in[_maxl*2+5], len[_maxl*2+5], num[_maxl*2+5];
	int trans[_maxl*2+5][LETTER];
	bool accept[_maxl*2+5];
	int head, last, tot;
	int NewState(int mxlen) {
		++tot;
		accept[tot] = false;
		link[tot] = in[tot] = num[tot] = 0;
		len[tot] = mxlen;
		memset(trans[tot], 0, sizeof(trans[tot]));
		return tot;
	}
	void init() { tot = 0; head = last = NewState(0); }
	void addone(int c) {
		int cur = NewState(len[last]+1), p = last; last = cur, num[cur] = 1;
		while(p && !trans[p][c]) { trans[p][c] = cur; p = link[p]; }
		if (!p) { link[cur] = head; ++in[head]; }
		else {
			int q = trans[p][c];
			if (len[q] == len[p]+1) {
				link[cur] = q; ++in[q];
			} else {
				int nq = NewState(len[p]+1);
				memcpy(trans[nq], trans[q], sizeof(trans[nq]));
				link[nq] = link[q]; link[q] = link[cur] = nq; in[nq] = 2;
				while (p && trans[p][c] == q) { trans[p][c] = nq; p = link[p]; }
			}
		}
	}
	void set_accept() {
		for (int p = last; link[p]; p = link[p]) accept[p] = true;
	}
	int que[_maxl*2+5];
	void set_num() {
		int t = 0, h = 0;
		for (int i = 1; i <= tot; ++i)
			if (in[i] == 0) que[t++] = i;
		while (h < t) {
			int p = que[h++]; int pp = link[p];
			num[pp] += num[p]; --in[pp];
			if (in[pp] == 0 && pp) que[t++] = pp;
		}
	}
	// build SAM
	// str:		the string
	// n:		the length of str
	void build(ELE * str, int n) {
		init();
		for (int i = 0; i < n; ++i) {addone(str[i] - AA);}
		set_accept();
		set_num();
	}
	// search s in SAM, return how many times it appears
	// s:	the substring
	// n:	the length of s
	int search(ELE * s, int n) {
		int p = head;
		for (int i = 0; i < n; ++i) {
			if (!trans[p][s[i]-AA]) return 0;
			p = trans[p][s[i]-AA];
		}
		return num[p];
	}
} sam;

char txt[MAXN+5];

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int k;
		cin >> k;
		cin >> txt;
		int l = strlen(txt);
		sam.build(txt, l);
		LL res = 0;
		for (int i = 1; i <= sam.tot; ++i)
			if (sam.num[i] == k) res += sam.len[i] - sam.len[sam.link[i]];
		cout << res << '\n';		
	}
	return 0;
}
