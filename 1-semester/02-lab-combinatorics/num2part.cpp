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

vector<int> get_seq(int n, int k, vector<vector<int>> &dp) {
	int last = 1;
	vector<int> a;
	while (n > 0) {
		while (last <= n) {
			int val = dp[n][last] - (last + 1 <= n ? dp[n][last + 1] : 0);
			if (k < val) {
				n -= last;
				a.push_back(last);
				break;
			}
			k -= val;
			last++;
		}
	}
	return a;
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("num2part.in", "r", stdin);
		freopen("num2part.out", "w", stdout);
	#endif

	int n, k;
	cin >> n >> k;

	vector<vector<int>> dp(n + 1, vector<int> (n + 1, 0)); // number i break down to term each geq j
	for (int i = 1; i <= n; i++) {
		dp[i][i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			dp[i][j] = dp[i][j + 1] + dp[i - j][j];
		}
	}

	vector<int> ans = get_seq(n, k, dp);

	for (int i = 0; i < size(ans); i++) {
		cout << ans[i];
		if (i + 1 < size(ans)) {
			cout << '+';
		}
	}
}
