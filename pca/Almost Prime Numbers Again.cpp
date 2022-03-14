// https://www.spoj.com/problems/KPRIMESB/
#pragma region Template
#include <bits/stdc++.h>
using namespace std;

#define io                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define all(x) begin(x), end(x)
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
#pragma endregion Template

void subsetsUtil(vector<ll>& A, vector<vector<ll>>& res, vector<ll>& subset, ll index) {
    // In the array A at every step we have two choices for each element either  we can ignore the element or we can include the element in our subset
    res.push_back(subset);
    for (ll i = index; i < ll(A.size()); i++) {
        // include the A[i] in subset.
        subset.push_back(A[i]);

        // move onto the next element.
        subsetsUtil(A, res, subset, i + 1);

        // exclude the A[i] from subset and triggers
        // backtracking.
        subset.pop_back();
    }

    return;
}

vector<vector<ll>> subsets(vector<ll>& A) {  // below function returns the subsets of vector A.
    vector<ll> subset;
    vector<vector<ll>> res;

    // keeps track of current element in vector A;
    ll index = 0;
    subsetsUtil(A, res, subset, index);

    return res;
}

ll n, m;
ll x;
const int mex = 1000010;
bool mark[mex];
int cnt[mex];
int tt;
int main() {
    io;
    for (int i = 2; i < mex; i++) {
        if (mark[i])
            continue;
        for (int j = i + i; j < mex; j += i)
            mark[j] = 1;
    }
    cnt[1] = 1;
    for (int i = 2; i < mex; i++)
        cnt[i] = cnt[i - 1] + !mark[i];
    cin >> tt;
    int tc = 0;
    while (tt--) {
        cin >> n >> m;

        vector<ll> vals;
        for (ll i = 0; i < m; i++) {
            cin >> x;
            vals.push_back(x);
        }
        if ((n == 1) || (n == 0)) {
            cout << "Case " << ++tc << ": 0\n";
            continue;
        } else {
            vector<vector<ll>> subs = subsets(vals);
            vector<pair<ll, ll>> vans;
            for (auto el : subs) {
                if (el.size()) {
                    ll ans = 1;
                    for (auto it : el)
                        ans = ans * it;
                    vans.push_back({ans, el.size()});
                }
            }
            ll res = 0;
            for (auto el : vans)
                if (el.second & 1)
                    res += n / el.first;
                else
                    res -= n / el.first;

            cout << "Case " << ++tc << ": " << n - res - cnt[n] + m << '\n';
        }
    }

    return 0;
}