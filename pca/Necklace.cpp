// https://lightoj.com/problem/necklace
#pragma region Template
#include <bits/stdc++.h>
using namespace std;

#define io                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
#pragma endregion Template

const ll mex = 2000010;  // edit considering conditions
const ll mod = 1000000007;
ll fact[mex];
ll invfact[mex];

ll binadd(ll a, ll b, ll m) {
    a %= m;
    ll res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}

ll binpow(ll a, ll b, ll m) {
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

ll invmod(ll a, ll m) { return binpow(a, m - 2, m); }

void genfact(ll m) {
    fact[0] = 1;
    for (ll i = 1; i < mex; i++)
        fact[i] = (fact[i - 1] % m * i % m) % m;
}

void geninvfact(ll m) {
    invfact[mex - 1] = invmod(fact[mex - 1], m);
    for (ll i = mex - 1; i >= 1; i--)
        invfact[i - 1] = (invfact[i] % m * i % m) % m;
}

ll nCk(ll n, ll k, ll m) {
    ll top = fact[n];
    ll bottom = (invfact[n - k] * invfact[k]) % m;
    ll res = (top * bottom) % m;
    return res;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
int tt;
ll n, k;
int main() {
    io;
    cin >> tt;
    int tc = 0;
    while (tt--) {
        cin >> n >> k;
        ll sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += binpow(k, gcd(i, n), mod);
            sum %= mod;
        }
        sum *= binpow(n, mod - 2, mod);
        sum %= mod;
        cout << "Case " << ++tc << ": " << sum << '\n';
    }

    return 0;
}