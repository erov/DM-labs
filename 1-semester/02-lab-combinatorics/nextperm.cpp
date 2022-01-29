#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

void print_zeroes(int n) {
	for (int i = 0; i < n; i++) {
		cout << 0 << ' ';
	}
	cout << '\n';
}

void prev(vector<int> a) {
	int n = (int) a.size();
	vector<bool> used(n + 1, true);
	int i = n - 1;
	used[a.back()] = false;
	while (i && a[i] >= a[i - 1]) {
		used[a[--i]] = false;
	}
	if (i == 0) {
		print_zeroes(n);
		return;
	}
	i--;
	used[a[i]] = false;
	for (int j = a[i] - 1; j >= 0; j--) {
		if (!used[j]) {
			a[i++] = j;
			used[j] = true;
			break;
		}
	}

	for (int j = n; j >= 1; j--) {
		if (!used[j]) {
			a[i++] = j;
		}
	}

	for (auto it : a) {
		cout << it << ' ';
	}
	cout << '\n';
}

void nxt(vector<int> a) {
	int n = (int) a.size();
	vector<bool> used(n + 1, true);
	int i = n - 1;
	used[a.back()] = false;
	while (i && a[i] <= a[i - 1]) {
		used[a[--i]] = false;
	}
	if (i == 0) {
		print_zeroes(n);
		return;
	}
	i--;
	used[a[i]] = false;
	for (int j = a[i] + 1; j <= n; j++) {
		if (!used[j]) {
			a[i++] = j;
			used[j] = true;
			break;
		}
	}

	for (int j = 1; j <= n; j++) {
		if (!used[j]) {
			a[i++] = j;
		}
	}

	for (auto it : a) {
		cout << it << ' ';
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("nextperm.in", "r", stdin);
		freopen("nextperm.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	prev(a);
	nxt(a);
}
