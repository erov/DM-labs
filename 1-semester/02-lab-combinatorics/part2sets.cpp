#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

void print(vector<int> &a, int const n, int const k) {
	vector<vector<int>> block(k);
	for (int i = 0; i < n; i++) {
		block[a[i]].push_back(i + 1);
	}
	bool ok = true;
	for (int i = 0; i < k; i++) {
		ok &= (!block[i].empty());
	}
	if (ok) {
		for (int i = 0; i < k; i++) {
			for (auto it : block[i]) {
				cout << it << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}

void gen(vector<int> &a, int pos, int cnt, int const n, int const k) {
	if (pos == n) {
		print(a, n, k);
		return;
	}

	for (int i = 0; i <= cnt; i++) {
		a[pos] = i;
		if (i == cnt && cnt + 1 < k) {
			gen(a, pos + 1, cnt + 1, n, k);
		} else {
			gen(a, pos + 1, cnt, n, k);
		}
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
        freopen("part2sets.in", "r", stdin);
        freopen("part2sets.out", "w", stdout);
    #endif

	int n, k;
	cin >> n >> k;

	vector<int> a(n);
	gen(a, 0, 0, n, k);
}
