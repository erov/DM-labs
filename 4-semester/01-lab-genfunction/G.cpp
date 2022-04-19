#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    #ifdef HOME
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        clock_t start_clock = clock();
    #else
     // freopen(".in", "r", stdin);
     // freopen(".out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
        // system("pause");
    #endif
}


void trim(vector<int64_t>& coeffs) {
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

void trim(vector<int64_t>& coeffs, size_t size) {
    coeffs.resize(size);
}

void print(vector<int64_t>& coeffs, bool print_size = true) {
    if (print_size) {
        cout << coeffs.size() - (coeffs.empty() ? 0 : 1) << '\n';
    }
    for (int64_t coeff : coeffs) {
        cout << coeff << ' ';
    }
    cout << '\n';
}

vector<int64_t> add(vector<int64_t>& p, vector<int64_t>& q) {
    vector<int64_t> sum(max(p.size(), q.size()), 0);
    for (size_t i = 0; i != p.size(); ++i) {
        sum[i] = p[i];
    }

    for (size_t i = 0; i != q.size(); ++i) {
        sum[i] = sum[i] + q[i];
    }

    trim(sum);
    return sum;
}

vector<int64_t> multiply(vector<int64_t>& p, vector<int64_t>& q) {
    vector<int64_t> mul(p.size() * q.size() + 1, 0);
    for (size_t i = 0; i != p.size(); ++i) {
        for (size_t j = 0; j != q.size(); ++j) {
            mul[i + j] = mul[i + j] + p[i] * q[j];
        }
    }

    trim(mul);
    return mul;
}

vector<int64_t> multiply(vector<int64_t>& p, int64_t lambda) {
    vector<int64_t> result(p.size(), 0);
    for (size_t i = 0; i != p.size(); ++i) {
        result[i] = p[i] * lambda;
    }
    return result;
}


vector<int64_t> power(vector<int64_t> p, uint64_t deg, size_t const COEFFS) {
    vector<int64_t> result = {1};
    while (deg != 0) {
        if (deg % 2 == 1) {
            result = multiply(result, p);
            trim(result, COEFFS);
        }
        p = multiply(p, p);
        trim(p, COEFFS);
        deg /= 2;
    }
    return result;
}

vector<int64_t> divide(vector<int64_t>& p, vector<int64_t>& q, size_t const COEFFS) {
    assert(!p.empty());
    assert(!q.empty());

    vector<int64_t> div(COEFFS, 0);
    
    if (div.size() > 0) {
        div[0] = p[0] / q[0];
        
        for (size_t i = 1; i != div.size(); ++i) {
            div[i] = (i < p.size() ? p[i] : 0);
            int64_t value = 0;
            for (size_t j = 0; j != i; ++j) {
                value = value + div[j] * (i - j < q.size() ? q[i - j] : 0);
            }
            div[i] = div[i] - value;
            div[i] = div[i] / q[0];
        }
    }

    return div;
}


vector<int64_t> parse(string const& object, size_t const SIZE, size_t& id) {
    if (object[id] == 'B') {
        ++id;
        return {0, 1};
    }

    if (object[id] == 'L') {
        id += 2;
        auto p = parse(object, SIZE, id);
        p[0] = 0; // !
        ++id;

        vector<int64_t> num = {1};
        vector<int64_t> denom = multiply(p, -1);
        ++denom[0];
        return divide(num, denom, SIZE);
    }

    if (object[id] == 'S') {
        id += 2;
        auto p = parse(object, SIZE, id);
        p[0] = 0; // !
        ++id;

        vector<int64_t> result = {1};
        for (size_t n = 0; n != SIZE && n != p.size(); ++n) {
            if (p[n] == 0) {
                continue;
            }
            vector<int64_t> temp(n + 1, 0);
            temp[0] = 1;
            temp[n] = -1;
            if (p[n] > 0) {
                vector<int64_t> one = {1};
                temp = divide(one, temp, SIZE);
            }
            temp = power(temp, abs(p[n]), SIZE);
            result = multiply(result, temp);
            trim(result, SIZE);
        }

        return result;
    }

    if (object[id] == 'P') {
        id += 2;
        auto lhs = parse(object, SIZE, id);
        ++id;
        auto rhs = parse(object, SIZE, id);
        ++id;

        lhs = multiply(lhs, rhs);
        trim(lhs, SIZE);
        return lhs;
    }

    throw runtime_error(":(");
}


void solve() {
    string object;
    cin >> object;

    constexpr size_t SIZE = 7;
    size_t id = 0;
    vector<int64_t> result = parse(object, SIZE, id);

    for (size_t i = 0; i != SIZE; ++i) {
        cout << (i < result.size() ? result[i] : 0) << ' ';
    }
}

