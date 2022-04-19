#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("nextchoose.in", "r", stdin);
		freopen("nextchoose.out", "w", stdout);
	#endif

	int n, k;
	cin >> n >> k;

	vector<bool> used(n + 1, false);
	vector<int> a(k);
	for (int i = 0; i < k; i++) {
		cin >> a[i];
		used[a[i]] = true;
	}

	bool found = false;
	for (int i = k - 1; i >= 0 && !found; i--) {
		for (int j = a[i] + 1; j <= n; j++) {
			if (!used[j]) {
				found = true;
				a[i++] = j;
				for (int p = i; p < k; p++) {
					used[a[p]] = false;
				}
				for (int p = j + 1; p <= n && i < k; p++) {
					if (!used[p]) {
						a[i++] = p;
					}
				}
				break;
			}
		}
	}

	if (found) {
		for (auto i : a) {
			cout << i << ' ';
		}
	} else {
		cout << -1;
	}
}
