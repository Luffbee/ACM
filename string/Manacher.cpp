#include <bits/stdc++.h>
#define FOR(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define FOR1(i, n) for (int (i) = 1; (i) <= (n); (i)++)

using namespace std;

typedef long long LL;

const int MAXN = 3e5;

// s:		origin string
// tmpstr:		string with interval
// ans[i]:	the length of palindrome with this place as central
char txt[MAXN+10], tmpstr[MAXN*2+10];
int ans[MAXN*2+10];
int manacher(char * s) {
	int i = 0, pos = 0, j = 0, ret = 0;
	tmpstr[0] = '$';
	do{
		tmpstr[2*i+1] = '#';
		tmpstr[2*i+2] = s[i];
	} while (s[i++]);
	ans[0] = 0;
	for (i = 1; tmpstr[i]; i++) {
		int t = i >= j ? 0: min(j-i, ans[pos*2-i]);
		while (tmpstr[i+t+1] == tmpstr[i-t-1]) {
			++t;
		}
		if (i+t > j) {
			j = i + t;
			pos = i;
		}
		ans[i] = t;
		ret = max(ret, t);
	}
	return ret; // return the max length
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> txt;
		cout << manacher(txt) << endl;;
	}
	return 0;
}
