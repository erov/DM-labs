#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <algorithm>
#include <stack>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

ll get_id(string &s, vector<vector<ll>> &cnt) {
	ll id = 0;
	int bal = 0;
	int n = size(s);
	stack<char> st;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			bal++;
			st.push(s[i]);
		}
		if (s[i] == ')') {
			int suf = n - i - 1 - bal - 1;
			id += cnt[n - i - 1][bal + 1] * (1LL << (suf / 2));
			bal--;
			st.pop();
		}
		if (s[i] == '[') {
			int suf = n - i - 1 - bal + 1;
			if (!st.empty() && st.top() == '(') {
				id += cnt[n - i - 1][bal - 1] * (1LL << (suf / 2));
			}
			suf = n - i - 1 - bal - 1;
			id += cnt[n - i - 1][bal + 1] * (1LL << (suf / 2));
			bal++;
			st.push(s[i]);
		}
		if (s[i] == ']') {
			int suf = n - i - 1 - bal + 1;
			if (!st.empty() && st.top() == '(') {
				id += cnt[n - i - 1][bal - 1] * (1LL << (suf / 2));
			}
			suf = n - i - 1 - bal - 1;
			id += cnt[n - i - 1][bal + 1] * (1LL << (suf / 2)) * 2;
			bal--;
			st.pop();
		}
	}
	return id;
}


int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("brackets2num2.in", "r", stdin);
		freopen("brackets2num2.out", "w", stdout);
	#endif


	string str;
	cin >> str;

	int n = size(str);

	vector<vector<ll>> cnt(n + 1, vector<ll> (n + 1, 0));
	cnt[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			cnt[i][j] = (j ? cnt[i - 1][j - 1] : 0) + (j + 1 <= n ? cnt[i - 1][j + 1] : 0);
		}
	}

	cout << get_id(str, cnt);
}
