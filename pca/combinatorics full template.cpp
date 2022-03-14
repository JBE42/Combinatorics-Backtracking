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
const ll mex = 2000010;     // edit considering constraints
const ll mod = 1000000007;  // edit considering constraints

ll fact[mex];
ll invfact[mex];
ll phi[mex];
#pragma endregion Constraints and Declarations

#pragma region Combinatorics
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }  // computes the normal gcd

ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }  // computes the lcm

ll incl_excl_bts(ll n, ll k, vector<ll>& v) {  // Inclusion/Exclusion principle & bitmask for large n, small k
    ll res = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        ll ans = 1;
        int count = 0;
        for (int i = 0; i < k; i++)
            if (mask & (1 << i)) {
                ans = (ans * v[i]) / __gcd(ans, v[i]);
                ++count;
            }
        ll aux = (n - 1) / ans + 1;
        res += (aux + (-2 * ((count & 1) == false) * aux));
    }
    res = n - res;
    return res;
}

ll sieve_incl_excl(ll n, ll k, vector<ll>& v) {  // finds all the multiples of the elements from v until maxn for small n, large k
    const int maxn = 1000007;                    // edit considering constraints
    ll divis[maxn] = {0};
    for (int i = 0; i < k; i++)
        for (ll j = 0; j < n; j += v[i])
            divis[j] = 1;
    return n - accumulate(all(divis), 0);
}

ll incl_excl(ll n, ll k, vector<ll>& v) { return ((k <= 20) ? incl_excl_bts(n, k, v) : sieve_incl_excl(n, k, v)); }  // optimized Include/Exclude, edit considering constraints

ll binadd(ll a, ll b, const ll m = mod) {  // computes a*b using addition in log2(b) steps
    ll res = 0;
    a %= m;
    while (b) {
        if (b & 1)
            res = (res % m + a % m) % m;
        a = (a % m + a % m) % m;
        b >>= 1;
    }
    return res;
}

ll binpow(ll a, ll b, const ll m = mod) {  // binary exponentiation
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1)
            res = binadd(res, a, m) % m;

        a = binadd(a, a, m) % m;
        b >>= 1;
    }
    return res;
}

ll invmd(ll a, ll m) { return binpow(a, m - 2, m); }  // computes MMI using Fermat's little theorem

void genfact(ll m) {  // computes the factorial modulo big prime
    fact[0] = 1;
    for (ll i = 1; i < mex; i++)
        fact[i] = (fact[i - 1] % m * i % m) % m;
}

void geninvfact(ll m) {  // computes the inverse factorial modulo big prime
    invfact[mex - 1] = invmd(fact[mex - 1], m);
    for (ll i = mex - 1; i >= 1; i--)
        invfact[i - 1] = (invfact[i] % m * i % m) % m;
}

void genfs(const ll m = mod) {  // precomputes the factorial and inverse factorial
    genfact(m);
    geninvfact(m);
}

void genphi() {  // computes phi from 1 to mex-1 using the divisor sum property
    for (ll i = 1; i < mex; i++) {
        phi[i] += i;
        for (ll j = i + i; j < mex; j += i)
            phi[j] -= phi[i];
    }
}

ll nCkmd(ll n, ll k, ll m) {  // compues nCk modulo big prime
    ll top = fact[n];
    ll bottom = (invfact[n - k] * invfact[k]) % m;
    ll res = (top * bottom) % m;
    return res;
}

ll Cmd(ll n, ll m) {  // compues Catalan(n) = (2 * n)!/((n + 1)! * n!) modulo big prime
    ll top = fact[2 * n];
    ll bottom = (invfact[n + 1] * invfact[n]) % m;
    ll res = (top * bottom) % m;
    return res;
}

ll exgcd(ll a, ll b, ll& x, ll& y) {  // recursive extended Euclidean algorithm, also computes gcd
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);  // Solutions of the form : x = x0 + (k * b)/g | y = y0 - (k * a)/g
    y = y - a / b * x;
    return g;
}

ll inv(ll a, const ll m = mod) {  // modular inverse with extended Euclidean algorithm
    ll x, y;
    exgcd(a, m, x, y);
    return (x + m) % m;  // normalize
}

ll cx(ll x, ll p) {  // the biggest exponent c such that p^c divides x!
    ll res = 0;
    while (x) {
        x /= p;
        res += x;
    }  // computed using Legendre formula
    return res;
}

ll gx(ll x, ll p, ll k, ll m) {  // computes g(x) = x!/p^c(x) mod p^b using recursion and wo auxiliary memory
    if (!x)
        return 1;
    ll temp = 1;
    for (ll i = 1; i <= x % m; i++)
        if (i % p)
            temp = temp * i % m;
    temp = temp * gx(x / p, p, k, m) % m;
    if (x / m % 2 && (p > 2 || (p == 2 && k == 2)))
        temp = (m - temp) % m;
    return temp;
}

ll comb(ll n, ll m, ll p, ll k) {  // computes nCk modulo mod = p^k where p is prime
    ll md = binpow(p, k, mod);
    ll temp = gx(n, p, k, md) * inv(gx(m, p, k, md), md) % md * inv(gx(n - m, p, k, md), md) % md;
    ll s = cx(n, p) - cx(m, p) - cx(n - m, p);
    temp = temp * binpow(p, s, md) % md;  // nCk modulo mod = g(n)/((g(n-k)*g(k))*p^(c(n)-c(n-k)-c(k))
    return temp;
}

int combcat(ll n, ll p, ll k) {  // computes Catalan(n) modulo mod = p^k where p is prime
    ll md = binpow(p, k, mod);
    ll temp = gx(2 * n, p, k, md) * inv(gx(n + 1, p, k, md), md) % md * inv(gx(n, p, k, md), md) % md;
    ll s = cx(2 * n, p) - cx(n + 1, p) - cx(n, p);
    temp = temp * binpow(p, s, md) % md;  // Catalan(n) modulo mod = g(2*n)/((g(n+1)*g(n))*p^(c(2*n)-c(n+1)-c(n))
    return temp;
}

ll C(ll n, const ll m = mod) {  // computes Catalan(n) modulo (p1^e1)*(p2^e2)*...*(pn^en) using comb and CRT
    if (m == mod)
        return Cmd(n, mod);
    ll temp = m;
    ll ans = 0;
    for (ll i = 2; i <= temp; i++)  // prime decomposition of m
        if (temp % i == 0) {
            ll pitoei = 1;  // pi^ei
            ll ei = 0;
            while (temp % i == 0) {
                pitoei *= i;
                ei++;
                temp /= i;
            }
            ll v = combcat(n, i, ei);                                              // Computes Catalan(n) modulo pi^ei
            ans = (v * inv(m / pitoei, pitoei) % m * (m / pitoei) % m + ans) % m;  // CRT formula
        }
    return ans;
}

ll nCk(ll n, ll k, const ll m = mod) {  // computes nCk modulo (p1^e1)*(p2^e2)*...*(pn^en) using comb and CRT
    if (m == mod)
        return nCkmd(n, k, mod);
    ll temp = m;
    ll ans = 0;
    for (ll i = 2; i <= temp; i++)  // prime decomposition of m
        if (temp % i == 0) {
            ll pitoei = 1;  // pi^ei
            ll ei = 0;
            while (temp % i == 0) {
                pitoei *= i;
                ei++;
                temp /= i;
            }
            ll v = comb(n, k, i, ei);                                              // Computes nCk modulo pi^ei
            ans = (v * inv(m / pitoei, pitoei) % m * (m / pitoei) % m + ans) % m;  // CRT formula
        }
    return ans;
}
#pragma endregion Combinatorics

int main() {
    io;

    return 0;
}