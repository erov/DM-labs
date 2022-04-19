#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

void gen(vector<int> a, int sum, int n) {
	if (sum == n) {
		for (int i = 0; i < (int) a.size(); i++) {
			cout << a[i];
			if (i != (int) a.size() - 1) {
				cout << '+';
			}
		}
		cout << '\n';
		return;
	}
	for (int i = (a.empty() ? 1 : a.back()); sum + i <= n; i++) {
		a.push_back(i);
		gen(a, sum + i, n);
		a.pop_back();
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("partition.in", "r", stdin);
		freopen("partition.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> a;
	gen(a, 0, n);
}
