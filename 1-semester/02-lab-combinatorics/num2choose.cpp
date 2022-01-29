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

void gen(vector<int> &a, int n, int k, int m) {
	if (k == (int) a.size()) {
		for (auto i : a) {
			cout << i << ' ';
		}
		return;
	}

	for (int i = (a.empty() ? 0 : a.back()) + 1; i <= n; i++) {
		int sz = cnk(n - i, k - 1 - (int) a.size());
		if (m >= sz) {
			m -= sz;
		} else {
			a.push_back(i);
			gen(a, n, k, m);
			return;
		}
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("num2choose.in", "r", stdin);
		freopen("num2choose.out", "w", stdout);
	#endif

	int n, k, m;
	cin >> n >> k >> m;

	vector<int> a;
	gen(a, n, k, m);
}
