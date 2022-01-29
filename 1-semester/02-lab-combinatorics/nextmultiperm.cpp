#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

void print_zeroes(int n) {
	for (int i = 0; i < n; i++) {
		cout << 0 << ' ';
	}
	cout << '\n';
}

void nxt(vector<int> a) {
	int n = size(a);
	vector<int> used(n + 1, 0);
	int i = n - 1;
	used[a.back()]--;
	while (i && a[i] <= a[i - 1]) {
		used[a[--i]]--;
	}
	if (i == 0) {
		print_zeroes(n);
		return;
	}
	i--;
	used[a[i]]--;
	for (int j = a[i] + 1; j <= n; j++) {
		if (used[j] < 0) {
			a[i++] = j;
			used[j]++;
			break;
		}
	}

	for (int j = 1; j <= n; j++) {
		while (used[j] < 0) {
			a[i++] = j;
			used[j]++;
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
		freopen("nextmultiperm.in", "r", stdin);
		freopen("nextmultiperm.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	nxt(a);

}
