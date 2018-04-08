void makefail(char*s) {
	for (int i=1,j=0;s[i];++i) {
		while (s[i]!=s[j]&&j!=0) j=fail[j-1];
		if (s[i]==s[j]) ++j;
		fail[i]=j;
} }
int kmp(char*txt, char*s) {
	int ret=0,i,j;
	for (i=0,j=0;txt[i];++i) {
		while (txt[i]!=s[j]&&j!=0) j=fail[j-1];
		if (txt[i]==s[j]) ++j;
		if (!s[j]) ++ret, j = 0; // no overlay
			// j = fail[j-1]; // overlay
	}
  return ret;
}
