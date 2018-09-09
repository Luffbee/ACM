#include <algorithm>
#define FOR(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define FOR1(i, n) for (int (i) = 1; (i) <= (n); (i)++)

using namespace std;

// f[]: result
// v:	volume of package
// c:	cost
// w:	value
// MAXV: max volme
const int MAXV = 2e4;
int deq[MAXV+10], q[MAXV+10];
void pack(int f[], int v, int c, int w, int n) {
	if (n == 0 || v < c || w == 0) return;
	if (n == 1) {
		// ZeroOne
		for (int i = v; i >= c; --i) {
			f[i] = max(f[i], f[i-c] + w);
		}
		return;
	} else if (n*c >= v-c+1) {
		// Complete
		for (int i = c; i <= v; ++i) {
			f[i] = max(f[i], f[i-c] + w);
		}
		return;
	} else {
		// Multiple O(vn)
		for (int i = 0; i < c; ++i) {
			int dl, dr, ql, qr;
			dl = dr = ql = qr = 0;
			for (int j = i, a = 0; j <= v; j += c, ++a) {
				if (qr == ql+n+1) {
					if (deq[dl] == q[ql]) ++dl;
					++ql;
				}
				q[qr++] = f[j] - a*w;
				while (dr > dl && deq[dr-1] < q[qr-1]) --dr;
				deq[dr++] = q[qr-1];
				f[j] = deq[dl] + a*w;
			}
		}
		return;
	}
}

int main() {
	return 0;
}
