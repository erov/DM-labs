#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

void gen(string str, int n, int bal) {
	if ((int) str.size() == n) {
		cout << str << '\n';
		return;
	}
	if (bal + 1 <= n - (int) str.size() - 1) {
		gen(str + "(", n, bal + 1);
	}
	if (bal > 0) {
		gen(str + ")", n, bal - 1);
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("brackets.in", "r", stdin);
		freopen("brackets.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	gen("", 2 * n, 0);
}
