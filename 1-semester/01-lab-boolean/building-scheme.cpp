#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<int>> ans(n);
    for (int i = 0; i < n; i++) {
    	ans.push_back({1, i + 1});
    }

    vector<int> to_or;
    bool zero = true;

    for (int i = 0; i < (1 << n); i++) {
    	string s;
    	int val;
    	cin >> s >> val;
    	if (val == 1) {
    		zero = false;
    		int last = (s[0] == '1' ? 1 : n + 1);
    		for (int j = 1; j < n; j++) {
    			ans.push_back({2, last, (s[j] == '1' ? j + 1 : j + n + 1)});
    			last = size(ans);
    		}
    		to_or.push_back(size(ans));
    	}
    }

   	if (zero) {
   		cout << n + 2 << "\n1 1\n" << "2 1 " << n + 1;
   	} else {
   		int last = to_or[0];
	    for (int i = 1; i < size(to_or); i++) {
	    	ans.push_back({3, last, to_or[i]});
	    	last = size(ans);
	    }
   		cout << size(ans) << '\n';
   		for (int i = n; i < size(ans); i++) {
   			for (int j : ans[i]) {
   				cout << j << ' ';
   			}
   			cout << '\n';
   		}
   	}
}