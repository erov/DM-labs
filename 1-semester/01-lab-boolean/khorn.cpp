#include <iostream>
#include <vector>

using namespace std;

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    int a[k][n], cnt[k];
    for (int i = 0; i < k; i++) {
    	cnt[i] = 0;
    	for (int j = 0; j < n; j++) {
    		cin >> a[i][j];
    		cnt[i] += (a[i][j] != -1);
    	}
    }

    while (true) {
    	int id = -1, row;
    	for (int i = 0; i < k && id == -1; i++) {
    		if (cnt[i] == 1) {
    			for (int j = 0; j < n; j++) {
    				if (a[i][j] != -1) {
    					id = j;
    					row = i;
    					break;
    				}
    			}
    		}
    	}
    	if (id == -1) {
    		cout << "NO";
    		return 0;
    	}
    	int val = (a[row][id] == 1);
    	for (int i = 0; i < k; i++) {
    		if (cnt[i] == 0 || a[i][id] == -1) {
    			continue;
    		}
			if (a[i][id] == val) {
				cnt[i] = 0;
			} else {
				a[i][id] = -1;
				cnt[i]--;
				if (cnt[i] == 0) {
					cout << "YES";
					return 0;
				}
			}
		}
    }
}