#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;

// str:		text
// s:		pattern
// MAXN:	max length
int fail[MAXN+1];	
void makefail(char * s) {
	fail[0] = 0;
	for (int i = 1, j = 0; s[i]; ++i) {
		while (s[i] != s[j] && j != 0) j = fail[j-1];
		if (s[i] == s[j]) ++j;
		fail[i] = j;
	}
}

int kmp(char * str, char * s) {
	int ret = 0, i, j;
	for (i = 0, j = 0; str[i]; ++i) {
		while (str[i] != s[j] && j != 0) j = fail[j-1];
		if (str[i] == s[j]) ++j;
		if (!s[j]) {
			++ret;
			j = 0; // no overlay
			// j = fail[j-1]; // overlay
		}
	}
	return ret;
}
