#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

typedef long long ll;
#define size(a) (int) a.size()

/*
1+1+1+1+1
1+1+1+2
1+1+3
1+2+2
1+4
2+3
5

1+1+1+1
1+1+2
1+3
2+2
4

1+1+1
1+2
3

1+1
2

1
*/

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
		freopen("nextpartition.in", "r", stdin);
		freopen("nextpartition.out", "w", stdout);
	#endif

	vector<int> a;
    int x;
    char trash;
 
    int n;
    cin >> n;
    while (cin >> trash >> x) {
        a.push_back(x);
    }

    if (size(a) == 1) {
    	cout << "No solution";
    	return 0;
    }

    int last = a.back();
    a.pop_back();
    while (last) {
    	a.back()++;
    	last--;
    	if (a.back() <= last) {
    		while (last >= a.back()) {
    			a.push_back(a.back());
    			last -= a.back();
    		}
    		a.back() += last;
    		last = 0;
    	}
    }

    cout << n << '=';
    for (int i = 0; i < size(a); i++) {
    	cout << a[i];
    	if (i + 1 < size(a)) {
    		cout << '+';
    	}
    }
}
