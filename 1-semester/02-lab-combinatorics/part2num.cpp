#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

int get_id(vector<int> &a, int n, vector<vector<int>> &dp) {
	int last = 1, sum = 0, id = 0;
	for (int i = 0; i < size(a); i++) {
		while (last < a[i]) {
			id += dp[n - sum - last][last];
			last++;
		}
		sum += last;
	}
	return id;
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("part2num.in", "r", stdin);
		freopen("part2num.out", "w", stdout);
	#endif

	vector<int> a;
	int x;
	char trash;

	int n = 0;
	cin >> x;
	n += x;
	a.push_back(x);
	while (cin >> trash >> x) {
		a.push_back(x);
		n += x;
	}

	vector<vector<int>> dp(n + 1, vector<int> (n + 1, 0)); // number i break down to term each geq j
	for (int i = 1; i <= n; i++) {
		dp[i][i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			dp[i][j] = dp[i][j + 1] + dp[i - j][j];
		}
	}

	cout << get_id(a, n, dp);
}
