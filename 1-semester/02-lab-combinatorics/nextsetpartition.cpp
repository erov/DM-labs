#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <set>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("nextsetpartition.in", "r", stdin);
		freopen("nextsetpartition.out", "w", stdout);
	#endif

	
	while(true) {
		int n, k;
		cin >> n >> k;

		if (n == 0 && k == 0) {
			break;
		}

		vector<vector<int>> a(k);
		for (int i = 0; i < k; i++) {
			string str;
			getline(cin, str);
			if (i == 0) {
				getline(cin, str);
			}
			int num = 0;
			for (char c : str) {
				if ('0' <= c && c <= '9') {
					num = num * 10 + c - '0';
				} else {
					a[i].push_back(num);
					num = 0;
				}
			}
			a[i].push_back(num);
		}

		// for (int i = 0; i < k; i++) {
		// 	for (auto it : a[i]) {
		// 		cout << it << ' ';
		// 	}
		// 	cout << '\n';
		// }
		// cout << '\n';

		set<int> bad;
		bool found = false;
		for (int i = size(a) - 1; i >= 0 && !found; i--) {
			int last = 0;
			int j;
			for (j = size(a[i]) - 1; j >= 0; j--) {
				if (!bad.empty()) {
					auto it = bad.upper_bound(max(last, a[i][j]));
					if (it != bad.end()) {
						a[i].push_back(*it);
						bad.erase(it);
						found = true;
						break;
					}
					it = bad.lower_bound(a[i][j]);
					if (j > 0 && it != bad.end()) {
						int tmp = a[i][j];
						a[i][j] = *it;
						bad.erase(it);
						bad.insert(tmp);
						found = true;
						break;
					}
				}
				last = a[i][j];
				bad.insert(a[i][j]);
				a[i].pop_back();
			}
			if (j == -1) {
				a.pop_back();
			}
		}

		while (!bad.empty()) {
			a.push_back(vector<int> (1, *bad.begin()));
			bad.erase(bad.begin());
		}

		cout << n << ' ' << size(a) << '\n';
		for (auto it : a) {
			for (int i : it) {
				cout << i << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}
