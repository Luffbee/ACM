#include <cstdio>
#include <cmath>

#define pb push_back

using namespace std;

typedef long long LL;

const LL MAXN = 1e18+1;

bool isPrime(LL x) {
	LL rt = (LL)sqrt((long double)x);
	if ((x != 2 && (x & (LL)1) == 0) || x < 2) return false;
	for (int i = 3; i <= rt; i += 2)
		if (x % i == 0) return false;
	return true;
}

LL mpow(LL a, LL b, LL mol) {
	LL ret = 1;
	for (LL i = 1; i <= b; i <<= 1) {
		if (i & b) ret = ret * a % mol;
		a = a * a % mol;
	}
	return ret;
}

LL getPrRoot(LL x, LL r) {
	for (LL g = 2; g <= x-1; ++g) {
		bool ok = true;
		if (mpow(g, (x-1)/2, x) == 1) ok = false;
		for (int i = 3; ok && i <= r; i+=2) {
			if ((x-1) % i) continue;
			if (mpow(g, (x-1)/i, x) == 1) ok = false;
		}
		if (ok) return g;
	}
	return 1;
}

int main() {
	for (int k = 1; k <= 40; ++k) {
		LL n = 1LL << k;
		for (LL r = 1; r <= 300; r += 2) {
			if (isPrime(r * n + 1)) {
				printf("p: %lld, r: %lld, deg: %d, g: %lld\n", r*n+1, r, k, getPrRoot(r*n+1, r));
			}
		}
	}
}
