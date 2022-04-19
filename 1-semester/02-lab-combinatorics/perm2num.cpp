#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("perm2num.in", "r", stdin);
		freopen("perm2num.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
	}

	vector<ll> f(n + 1);
	f[0] = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] * i;
	}

	ll k = 0;
	vector<bool> used(n, false);
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < a[i]; j++) {
			cnt += (!used[j]);
		}
		used[a[i]] = true;
		k += f[n - 1 - i] * cnt;
	}

	cout << k;
}
