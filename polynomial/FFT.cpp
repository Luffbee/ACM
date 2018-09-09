#include <iostream>
#include <cstdio>
#include <complex>

using namespace std;
const int MAXN = (1 << 18);

typedef complex<double> C;
typedef long long LL;
const double PI = 3.1415926535897932384626433832795028841971;
class Polynomial {
public:
	// MAXN:	the maxium size of a polynomial
	static const int MAXN = (1 << 18);
	// MOL:		a prime, MOL = R * 2 ^ DEG + 1
	// R:		see MOL
	// DEG:		see MOL, 2 ^ DEG should greater than MAXN
	// G:		the primitive root of MOL
	// there are some useful examples:
	// MOL		R		DEG		G
	//
	// p: 167772161, r: 5, deg: 25, g: 3
	// p: 469762049, r: 7, deg: 26, g: 3
	// p: 754974721, r: 45, deg: 24, g: 11
	// p: 998244353, r: 119, deg: 23, g: 3
	// p: 1107296257, r: 33, deg: 25, g: 10
	// p: 99857989633, r: 93, deg: 30, g: 2
	// p: 110595407873, r: 103, deg: 30, g: 2
	// p: 970662608897, r: 113, deg: 33, g: 2
	// p: 1009317314561, r: 235, deg: 32, g: 2
	// p: 12025908428801, r: 175, deg: 36, g: 2
	// p: 98406290685953, r: 179, deg: 39, g: 2
	// p: 106652627894273, r: 97, deg: 40, g: 2
	static const LL R = 45, DEG = 24, G = 11;
	static const LL MOL = R * (1 << DEG) + 1; 
	int g[MAXN+5];
	
	// DFT for FFT
	// a:	the polynomial
	// f:	1 for DFT, -1 for IDFT
	// n:	size of a
	void dft(C * a, int f, int n) {
		for (int i = 0; i < n; ++i) if (g[i] > i) swap(a[g[i]], a[i]);
		for (int i = 1; i < n; i <<= 1) {
			C e(cos(PI/i), f*sin(PI/i));
			for (int j = 0; j < n; j += (i<<1)) {
				C w(1, 0);
				for (int k = 0; k < i; ++k, w *= e) {
					C x = a[j+k], y = w*a[i+j+k];
					a[j+k] = x+y; a[i+j+k] = x-y;
				}
			}
		}
		if (f == -1) for (int i = 0; i < n; ++i) a[i] /= n;
	}	

	// FFT
	// a:	the first polynomial (result will store in it)
	// b:	the second polynomial (data in it will be modified)
	// n:	the maxium degree of result
	void fft(C * a, C * b, int n) {
		int t = -1;
		while (n >= (1 << (t+1))) ++t;
		n = (1 << (t+1));
		for (int i = 1; i < n; ++i) g[i] = (g[i>>1]>>1) | ((i&1) << t);
		dft(a, 1, n); dft(b, 1, n);
		for (int i = 0; i < n; ++i) a[i] = a[i] * b[i];
		dft(a, -1, n);
	}
	
	// fast power
	LL mpow(LL a, int b, LL mol=MOL) {
		LL ret = 1;
		for (int i = 1; i <= b; i <<= 1) {
			if (i & b) ret = ret * a % mol;
			a = a * a % mol;
		}
		return ret;
	}
	
	// DFT for NTT
	// parameters are as same as dft()
	void ndft(LL * a, int f, int n) {
		for (int i = 0; i < n; ++i) if (g[i] > i) swap(a[i], a[g[i]]);
		LL gg = mpow(G, R);
		for (int b = 1, i = 1; i < n; ++b, i <<= 1) {
			LL e = mpow(gg, 1 << (DEG-b));
			if (f < 0) e = mpow(e, MOL-2);
			for (int j = 0; j < n; j += i<<1) {
				LL w = 1;
				for (int k = 0; k < i; ++k, w = w*e%MOL) {
					LL x = a[j+k], y = w * a[j+k+i] % MOL;
					a[j+k] = x+y; a[j+k+i] = x-y;
					if (a[j+k] >= MOL) a[j+k] -= MOL;
					if (a[j+k+i] < 0) a[j+k+i] += MOL;
				}
			}
		}
		if (f < 0) {
			LL v = mpow(n, MOL-2);
			for (int i = 0; i < n; ++i) a[i] = a[i] * v % MOL;
		}
	}

	// NTT
	// parameters are as same as FFT
	void ntt(LL * a, LL * b, int n) {
		int t = -1;
		while (n >= (1 << (t+1))) ++t;
		n = (1 << (t+1));
		for (int i = 1; i < n; ++i) g[i] = (g[i>>1]>>1) | ((i&1) << t);
		ndft(a, 1, n); ndft(b, 1, n);
		for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % MOL;
		ndft(a, -1, n);
	}
} poly; 

LL ploy1[MAXN+5], ploy2[MAXN+5];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n+1; ++i) cin >> ploy1[i];
	for (int i = 0; i < m+1; ++i) cin >> ploy2[i];
	poly.ntt(ploy1, ploy2, n+m);
	for (int i = 0; i <= n+m; ++i) {
		cout << ploy1[i] << ' ';
	}
	cout << endl;
}
