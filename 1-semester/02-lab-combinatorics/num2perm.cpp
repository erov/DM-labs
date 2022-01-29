#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;
typedef long long ll;

void gen(vector<int> &a, vector<bool> &used, vector<ll> &f, int n, ll k) {
	if (n == (int) a.size()) {
		for (auto i : a) {
			cout << i << ' ';
		}
		return;
	}
	ll suffix = f[n - 1 - (int) a.size()];
	int pos = k / suffix;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			if (pos == 0) {
				a.push_back(i + 1);
				used[i] = true;
				break;
			}
			pos--;
		}
	}
	gen(a, used, f, n, k % suffix);

}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("num2perm.in", "r", stdin);
		freopen("num2perm.out", "w", stdout);
	#endif

	int n;
	ll k;
	cin >> n >> k;

	vector<ll> f(n + 1);
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] * i;
	}

	vector<int> a;
	vector<bool> used(n, false);
	gen(a, used, f, n, k);
}
