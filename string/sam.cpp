#include<iostream>
#include<map>
#include<cstring>

using namespace std;

const int MAXN = 1e5;

class SAM
{
public:
	// MAXL:	the max length of the string
	// ELE:		the type of elements
	typedef char ELE;
	static const int LETTER = 26; // the size of alphabet
	static const char AA = 'a';	// the first letter of the alphabet
	static const int _maxl = MAXN;
	struct State {
		//map<ELE, int> transs;	// the transition
		int transs[LETTER];
		inline int & trans(ELE e) {
			//return transs[e];
			return transs[e-AA];
		} // get of set the transation
		// check wether there is  a transation
		inline bool hastrans(ELE e) {
			//return transs.count(e);
			return transs[e-AA] != -1;
		}
		inline void cleartrans() {
			//transs.clear();
			memset(transs, -1, sizeof(transs));
		}
		// set transation according to another state
		inline void cptrans(State const & rh) {
			//transs = rh.transs;
			memcpy(transs, rh.transs, sizeof(transs));
		}
		// maxlen:	the length of the longest string this state present
		// num:		the number of path that can reach a accpet state from this state
		// accept:	wether this state is a accept state
		// link:	the index of the link state, -1 means no link state
		int maxlen, num; bool accept;
		int link;
		void init(int mxlen = 0) {
			link = -1;
			maxlen = mxlen;
			num = 0;
			accept = false;
			cleartrans();
		}
	} state[2*_maxl+1];
	int tot;		// number of total states
	int head, last; // head is the initial state, last is the latest state.

	int NewState(int mxlen = 0) {
		state[tot].init(mxlen);
		return tot++;
	}
	void init() { tot = 0; head = last = NewState(); }
	SAM() { init(); }
	// add a char to the SAM
	// c:	the new char
	void addone(ELE c) {
		int cur = NewState(state[last].maxlen+1);
		int p;;
		for (p = last; p != -1 && !state[p].hastrans(c); p = state[p].link)
			state[p].trans(c) = cur;
		if (p == -1) state[cur].link = head;
		else if (state[state[p].trans(c)].maxlen == state[p].maxlen+1)
			state[cur].link = state[p].trans(c);
		else {
			int q = state[p].trans(c);
			int nq = NewState(state[p].maxlen+1);
			state[nq].cptrans(state[q]);
			for (; p != -1 && state[p].trans(c) == q; p = state[p].link)
				state[p].trans(c) = nq;
			state[nq].link = state[q].link;
			state[cur].link = state[q].link = nq;
		}
		last = cur;
	}
	// set 'accept' field of the states.
	void set_accept() {
		for (int p = last; state[p].link != -1; p = state[p].link)
			state[p].accept = true;
	}
	// set 'num' field of the states recursively.
	// cur:		current state
	int set_num(int cur) {
		if (state[cur].num != 0) return state[cur].num;
		int ret = 0;
		if (state[cur].accept) ret++;
		for (auto i : state[cur].transs) {
			if (i != -1) ret += set_num(i);
		}
		state[cur].num = ret;
		return ret;
	}
	// build SAM with a string
	// str:		the string
	// n:		the length of str
	void build(const ELE * str, int n) {
		init();
		for (int i = 0; i < n; ++i) addone(str[i]);
		set_accept();
		set_num(head);
	}
	// return how many times a substring occurs(overlay).
	// s:	the substring
	// n:	the length of s
	int search(const ELE * s, int n) {
		int p = head;
		for (int i = 0; i < n; ++i) {
			if (!(state[p].hastrans(s[i]))) return 0;
			p = state[p].trans(s[i]);
		}
		return state[p].num;
	}
} sam;

int main() {
	return 0;
}
