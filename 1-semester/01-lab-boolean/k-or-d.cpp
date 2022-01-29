#include <iostream>
#include <vector>
#include <map>
  
using namespace std;

typedef long long ll;
  
string get(ll i, bool f) {
    string ans = "";
    if (f == 0) {
        ans += "~";
    }
    ans += char('0' + i + 1);
    return ans;
}
 
int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif
  
    ios_base::sync_with_stdio(false);

    ll n;
    cin >> n;
  
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll s;
    cin >> s;
  
    map<ll, string> to_and;
    to_and[0] = "1&~1";
    for (ll mask = 0; mask < (1 << n); mask++) {
        vector<ll> pos;
        for (ll i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                pos.push_back(i);
            }
        }
        for (ll mask1 = 0; mask1 < (1 << size(pos)); mask1++) {
            string s = "";
            ll x;
            for (ll i = 0; i < size(pos); i++) {
                ll val = (((mask1 >> i) & 1) ? a[pos[i]] : (~a[pos[i]]));
                if (i == 0) {
                    x = val;
                    s = get(pos[i], ((mask1 >> i) & 1));
                } else {
                    x = x & val;
                    s += "&" + get(pos[i], ((mask1 >> i) & 1));
                }
            }
            if (!s.empty()) {
                to_and[x] = s;
            }
        }
    }
 
    if (s == 0) {
        cout << to_and[0];
        return 0;
    }
  
    string ans = "";
  
    for (ll i = 0; i < 32; i++) {
        if ((s >> i) & 1) {
            bool ok = false;
            for (ll j = 0; j < n && !ok; j++) {
                if ((a[j] >> i) & 1) {
                    for (auto it : to_and) {
                        ll val = (it.first & a[j]);
                        if (((val >> i) & 1) && (val | s) == s)  {
                            if (ans.size()) {
                                ans += "|";
                            }
                            ans += "(" + get(j, 1) + "&" + it.second + ")";
                            ok = true;
                            break;
                        }
                        val = ((~it.first) & a[j]);
                        if (((val >> i) & 1) && (val | s) == s)  {
                            if (ans.size()) {
                                ans += "|";
                            }
                            ans += "(" + get(j, 1) + "&~(" + it.second + "))";
                            ok = true;
                            break;
                        }
                    }
                } else {
                    for (auto it : to_and) {
                        ll val = (it.first & (~a[j]));
                        if (((val >> i) & 1) && (val | s) == s)  {
                            if (ans.size()) {
                                ans += "|";
                            }
                            ans += "(~" + get(j, 1) + "&" + it.second + ")";
                            ok = true;
                            break;
                        }
                        val = (~it.first & (~a[j]));
                        if (((val >> i) & 1) && (val | s) == s)  {
                            if (ans.size()) {
                                ans += "|";
                            }
                            ans += "(~" + get(j, 1) + "&~(" + it.second + "))";
                            ok = true;
                            break;
                        }
                    }
                }
            }
            if (!ok) {
                cout << "Impossible";
                return 0;
            }
        }
    }
    cout << ans;
}