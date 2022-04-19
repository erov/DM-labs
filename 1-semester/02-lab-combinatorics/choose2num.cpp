#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

map<pair<int, int>, int> mem;
int cnk(int n, int k) {
    if (mem.count({n, k})) {
        return mem[{n, k}];
    }
    if (k == 0 || k == n) {
        return mem[{n, k}] = 1;
    }
    return mem[{n, k}] = (cnk(n - 1, k - 1) + cnk(n - 1, k));
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("choose2num.in", "r", stdin);
		freopen("choose2num.out", "w", stdout);
	#endif

	int n, k;
	cin >> n >> k;

	vector<int> a(k);
	for (int i = 0; i < k; i++) {
		cin >> a[i];
	}

	vector<bool> used(n + 1, false);
	ll m = 0;
	for (int i = 0; i < k; i++) {
		for (int j = (!i ? 0 : a[i - 1]) + 1; j < a[i]; j++) {
			if (!used[j]) {
				m += cnk(n - j, k - i - 1);
			}
		}
		used[a[i]] = true;
	}

	cout << m;
}
