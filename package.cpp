// f[]: result; v:	volume of package
// c:	cost; w:	value; V: max volme
int deq[V], q[V];
void pack(int f[], int v, int c, int w, int n) {
	if (n==0||v<c||w==0) return;
	if (n == 1) { // ZeroOne
		for (int i=v;i>=c;--i) f[i]=max(f[i],f[i-c]+w);
	} else if (n*c>v-c) { // Complete
		for (int i=c;i<=v;++i) f[i]=max(f[i],f[i-c]+w);
	} else { // Multiple O(vn)
		for (int i=0;i<c;++i) {
			int dl=0, dr=0, ql=0, qr=0;
			for (int j=i,a=0;j<=v;j+=c,++a) {
				if (qr==ql+n+1) {
					if (deq[dl]==q[ql]) ++dl;
					++ql;
				}
				q[qr++]=f[j]-a*w;
				while (dr>dl&&deq[dr-1]<q[qr-1]) --dr;
				deq[dr++]=q[qr-1]; f[j]=deq[dl]+a*w;
} }	} }
