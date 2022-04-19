#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

void gen(string str, int n, int bal) {
    if (size(str) == n) {
        cout << str << '\n';
        return;
    }
    if (bal + 1 <= n - size(str) - 1) {
        gen(str + "(", n, bal + 1);
    }
    if (bal > 0) {
        gen(str + ")", n, bal - 1);
    }
}

ll get_id(string &s, vector<vector<ll>> &cnt) {
	ll id = 0;
	int bal = 0;
	for (int i = 0; i < size(s); i++) {
		if (s[i] == '(') {
			bal++;
		} else {
			id += cnt[size(s) - 1 - i][bal + 1];
			bal--;
		}
	}
	return id;
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("brackets2num.in", "r", stdin);
		freopen("brackets2num.out", "w", stdout);
	#endif

	string s;
	cin >> s;

	// gen("", size(s), 0);

	int n = size(s);
	vector<vector<ll>> cnt(n + 1, vector<ll> (n + 1, 0));
	cnt[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			cnt[i][j] = (j ? cnt[i - 1][j - 1] : 0) + (j + 1 <= n ? cnt[i - 1][j + 1] : 0);
		}
	}

	cout << get_id(s, cnt);
}
