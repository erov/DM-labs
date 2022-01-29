#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

void gen(vector<int> &a, int pos, int n) {
	for (auto it : a) {
		cout << it << ' ';
	}
	cout << '\n';
	if (pos == n) {
		return;
	}
	for (int i = (a.empty() ? 1 : a.back() + 1); i <= n; i++) {
		a.push_back(i);
		gen(a, pos + 1, n);
		a.pop_back();
	}

}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("subsets.in", "r", stdin);
		freopen("subsets.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> a;
	gen(a, 0, n);
}
