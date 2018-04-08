// s:		origin string
// tmp:		string with interval
// ans[i]:	the length of palindrome
char txt[MAXN+10],tmp[MAXN*2+10];
int ans[MAXN*2+10];
int manacher(char*s) {
	int i=0,pos=0,j=0,ret=0;
	tmp[0]='$';
	do {
    tmp[2*i+1]='#'; tmp[2*i+2]=s[i];
	} while (s[i++]);
	ans[0]=0;
	for (i=1;tmp[i];i++) {
		int t=i>=j?0:min(j-i,ans[pos*2-i]);
		while (tmp[i+t+1]==tmp[i-t-1]) ++t;
		if (i+t > j) j = i + t, pos = i;
		ans[i]=t; ret=max(ret, t);
	}
	return ret; // return the max length
}
