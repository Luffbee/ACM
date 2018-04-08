int wa[N], wb[N], bu[N];
bool equal(int*s,int a,int b,int l) {
	return s[a]==s[b]&&s[a+l]==s[b+l];
}
void busort(int n,int*key,int*ord,int m) {
  int i; memset(bu,0,sizeof(int)*m);
	for (i=0;i<n;++i) ++bu[key[i]];
	for (i=1;i<m;++i) bu[i]+=bu[i-1];
	for (i=n-1;i>=0;--i) sa[--bu[key[ord[i]]]]=ord[i];
}
void DA(char*str,int n,int m,int*sa) {
	int*x=wa,*y=wb,p,i,l;
  for (i=0;i<n;++i) x[i]=str[i],y[i]=i;
  busort(n,x,y,m);
	for (l=1,p=1;p<n;l<<=1,m=p) {
		for (p=0,i=n-l;i<n;++i) y[p++]=i;
		for (i=0;i<n;++i) if (sa[i]>=l) y[p++]=sa[i]-l;
    busort(n,x,y,m); swap(x,y);
		for (i=p=1,x[sa[0]]=0;i<n;++i)
			x[sa[i]]=equal(y,sa[i],sa[i-1],l)?p-1:p++;
	}
}
void height(char*str,int n,int*sa,int*rk,int*h) {
  int i,j,k=0;
  for (i=0;i<n;h[rk[i++]]=k) {
    if (rk[i] == 0) k = 0;
    else for (k?k--:0,j=sa[rk[i]-1];str[i+k]==str[j+k];++k);
  }
}
