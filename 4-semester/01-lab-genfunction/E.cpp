#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
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


void solve() {
    int64_t r;
    cin >> r;

    size_t d;
    cin >> d;

    vector<int64_t> a(d + 1);
    for (size_t i = 0; i != a.size(); ++i) {
        cin >> a[i];
    }

    vector<int64_t> p = {0};
    vector<int64_t> q = {1};

    vector<int64_t> q_multiplier = {1, -r};

    for (size_t iter = a.size(); iter != 0; --iter) {
        vector<int64_t> basis_coeffs(iter, 0);
        vector<int64_t> working(a.size(), 0);
        working[iter - 1] = a[iter - 1];

        for (size_t basis_ind = iter; basis_ind != 0; --basis_ind) {
            vector<int64_t> basis(1, 1);
            vector<int64_t> temp = {1, 1};
            int64_t denom = 1;
            for (size_t i = 1; i != basis_ind; ++i) {
                temp[0] = i;
                denom *= i;
                basis = multiply(basis, temp);
            }
            basis_coeffs[basis_ind - 1] = denom * working[basis_ind - 1];
            basis = multiply(basis, -working[basis_ind - 1]);
            working = add(working, basis);
        }

        trim(working);
        assert(working.empty());

        vector<int64_t> p_i = {0};
        vector<int64_t> denom_multiplier = q;
        for (size_t i = basis_coeffs.size(); i != 0; --i) {
            vector<int64_t> temp = {basis_coeffs[i - 1]};
            temp = multiply(temp, denom_multiplier);
            p_i = add(p_i, temp);
            denom_multiplier = multiply(denom_multiplier, q_multiplier);
        }

        p = add(p, p_i);

        q = multiply(q, q_multiplier);
    }

    print(p);
    print(q);
}

