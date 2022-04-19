#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

void gen(vector<int> a, int pos, int k, int n) {
	if (pos == k) {
		for (int i = 0; i < k; i++) {
			cout << a[i] << ' ';
		}
		cout << '\n';
		return;
	}

	bool nxt = false;
	for (int i = (a.empty() ? 0 : a.back()) + 1; i <= n; i++) {
		a.push_back(i);
		nxt = true;
		gen(a, pos + 1, k, n);
		a.pop_back();
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("choose.in", "r", stdin);
		freopen("choose.out", "w", stdout);
	#endif

	int n, k;
	cin >> n >> k;

	vector<int> a;
	gen(a, 0, k, n);
}
