// https://www.spoj.com/problems/UCV2013E/
#pragma region Template
#include <bits/stdc++.h>
using namespace std;

#define io                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define all(x) begin(x), end(x)
using ld = long double;
using ll = long long;
using ull = unsigned long long;
#pragma endregion Template

#pragma region Constraints and Declarations
const ll mex = 555;         // edit considering constraints
const ll mod = 1000000007;  // edit considering constraints

ll fact[mex];
ll invfact[mex];
#pragma endregion Constraints and Declarations

#pragma region Combinatorics
ll binadd(ll a, ll b, const ll m = mod) {
    a %= m;
    ll res = 0;
    while (b) {
        if (b & 1)
            res = (res % m + a % m) % m;
        a = (a % m + a % m) % m;
        b >>= 1;
    }
    return res;
}

ll binpow(ll a, ll b, const ll m = mod) {
    a %= m;
    ll res = 1;
    while (b) {
        if (b & 1)
            res = binadd(res, a, m);
        a = binadd(a, a, m);
        b >>= 1;
    }
    return res;
}

ll inv(ll a, const ll m = mod) { return binpow(a, m - 2, m); }

void genfact(const ll m = mod) {
    fact[0] = 1;
    for (ll i = 1; i < mex; i++)
        fact[i] = (fact[i - 1] % m * i % m) % m;
}

void geninvfact(const ll m = mod) {
    invfact[mex - 1] = inv(fact[mex - 1], m);
    for (ll i = mex - 1; i >= 1; i--)
        invfact[i - 1] = (invfact[i] % m * i % m) % m;
}

void genfs(const ll m = mod) {
    genfact(m);
    geninvfact(m);
}

ll nCk(ll n, ll k, const ll m = mod) {
    ll top = fact[n];
    ll bottom = (invfact[n - k] * invfact[k]) % m;
    ll res = (top * bottom) % m;
    return res;
}
#pragma endregion Combinatorics

ll n;
ll a[mex];
ll b[mex];
ll c[mex];
ll d[mex];
int main() {
    io;
    genfs();
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            a[i] = b[i] - a[i];
        }
        b[0] = 0;
        for (int i = 1; i <= n; i++)
            b[i] = b[i - 1] + a[i];
        ll ans = 1;
        for (int i = 1; i <= n; i++)
            ans = (ans % mod * nCk(b[i], a[i])) % mod;
        cout << ans << '\n';
    }

    return 0;
}