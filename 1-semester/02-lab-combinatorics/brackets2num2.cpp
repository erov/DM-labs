#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <algorithm>
#include <stack>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

// void gen(string str, int n, int bal) {
//     if (size(str) == n) {
//         cout << str << '\n';
//         return;
//     }
//     if (bal + 1 <= n - size(str) - 1) {
//         gen(str + "(", n, bal + 1);
//     }
//     if (bal > 0) {
//         gen(str + ")", n, bal - 1);
//     }
// }

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

// string get_seq(int n, ll k, vector<vector<ll>> &cnt) {
// 	int bal = 0;
// 	string str = "";
// 	for (int i = 0; i < n; i++) {
// 		if (k < cnt[n - 1 - i][bal + 1]) {
// 			str += "(";
// 			bal++;
// 		} else {
// 			if (k < cnt[n - 1 - i][bal + 1] * (1 << (n - 1 - i - bal - 1))) {
// 				str += "[";
// 			} else {
				
// 			}
// 		}
// 	}
// 	return str;
// }

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

	// cout << int('(') << ' ' <<  int(')') << ' ' << int('[') << ' ' << int(']') << '\n';
	// vector<string> s = {"(())", "()()", "([])", "[()]", "[[]]", "()[]", "[]()", "[][]"};
	// sort(s.begin(), s.end() );
	// for (auto it : s) {
	// 	cout << it << '\n';
	// }

	int n = size(str);

	vector<vector<ll>> cnt(n + 1, vector<ll> (n + 1, 0));
	cnt[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			cnt[i][j] = (j ? cnt[i - 1][j - 1] : 0) + (j + 1 <= n ? cnt[i - 1][j + 1] : 0);
		}
	}

	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 0; j <= n; j++) {
	// 		cout << cnt[i][j] << ' ';
	// 	}
	// 	cout << '\n';
	// }

	cout << get_id(str, cnt);
}
