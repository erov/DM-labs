// #pragma GCC optimize("Ofast")
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <stack>
#include <climits>

// continue push_back setprecision __builtin_popcount

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937 rnd(228);

const double EPS = 1e-7;
const double PI = acos(-1);
const int oo = INT_MAX;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp(a, b) make_pair(a, b)
#define size(a) (int)a.size()
#define f first
#define s second

void solve();

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		// freopen("censored.in", "r", stdin);
		// freopen("censored.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	#ifdef HOME
		clock_t start = clock();
	#endif

	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
		// system("pause");
	#endif

	exit(0);
}

void solve() {
	string s;
	cin >> s;

	vector<string> a;
	string stamp = "";
	for (int i = 0; i < size(s); i++) {
		stamp += "#";
	}

	for (int i = 0; i < size(s); i++) {
		a.push_back(stamp);
	}

	for (int i = size(s) - 1; i >= 0; i--) {
		for (int j = 0; j < size(s); j++) {
			a[j][i] = s[j];
		}
		sort(all(a));
	}

	// for (auto it : a) {
	// 	cout << it << '\n';
	// }

	cout << a[0];
}
