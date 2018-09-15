#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 9;
int MOD = 1e9+7;
struct Matrix{
	int a[N][N], n;
	Matrix(int n = 0) :n(n){}
	void zero(){
		for (int i = 0; i < n; i++)
			memset(a[i], 0, sizeof(int)*n);
	}
	void one(){
		zero();
		for (int i = 0; i < n; i++)a[i][i] = 1;
	}
	Matrix operator * (const Matrix& x)const{
		Matrix r(n); r.zero();
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (a[i][j]){
					for (int k = 0; k < n; k++)
						r.a[i][k] = (r.a[i][k] + (LL)a[i][j] * x.a[j][k]) % MOD;
				}
			}
		}
		return r;
	}
	Matrix operator ^ (LL k)const{
		Matrix r(n), t = *this; r.one();
		for (; k; k >>= 1){
			if (k & 1)r = r * t;
			t = t * t;
		}
		return r;
	}
};
