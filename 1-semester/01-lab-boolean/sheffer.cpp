#include <iostream>
#include <vector>

using namespace std;

string get_id(int n) {
	string ans = "";
	while (n) {
		ans = char('0' + n % 10) + ans;
		n /= 10;
	}
	return ans;
}

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    string s = "((A0|B0)|(A0|B0))";
    // cout << char(124);

    for (int i = 1; i < n; i++) {
    	string id = get_id(i);
    	s = "((" + s + "|" + "((A" + id + "|A" + id + ")|(B" + id + "|B" + id + ")))|(A" + id + "|B" + id + "))";
    }
    cout << s;
}