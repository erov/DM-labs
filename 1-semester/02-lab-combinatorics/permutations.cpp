#include <iostream>
#include <vector>
#include <assert.h>
#include <set>

using namespace std;

void gen(vector<int> &ans, vector<bool> &used, int sz) {
	if (sz == (int) ans.size()) {
		for (auto i : ans) {
			cout << i << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = 0; i < sz; i++) {
		if (!used[i]) {
			used[i] = true;
			ans.push_back(i + 1);
			gen(ans, used, sz);
			ans.pop_back();
			used[i] = false;
		}
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("permutations.in", "r", stdin);
		freopen("permutations.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> ans;
	vector<bool> used(n, false);
	gen(ans, used, n);
}
