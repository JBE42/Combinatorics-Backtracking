// https://www.spoj.com/problems/EASYMATH/
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

const int md = 1000000007;
const ll mex = 2000010;  // edit considering conditions

ll fact[mex];
ll invfact[mex];
ll phi[mex];

#pragma region Combinatorics
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }  // computes the normal gcd

ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }  // computes the lcm

void subsetsUtil(vector<ll>& A, vector<vector<ll>>& res, vector<ll>& subset, int index) {
    // In the array A, at every step, we have two choices for each element : either we can ignore the element or we can include the element in our subset
    res.push_back(subset);
    for (int i = index; i < int(A.size()); i++) {
        // include the A[i] in subset
        subset.push_back(A[i]);
        // move onto the next element
        subsetsUtil(A, res, subset, i + 1);
        // excludes A[i] from the subset and triggers backtracking
        subset.pop_back();
    }
    return;
}

vector<vector<ll>> subsets(vector<ll>& A) {  // returns the subsets of vector A, used for Inclusion/Exclusion
    vector<ll> subset;
    vector<vector<ll>> res;
    // keeps track of current element in vector A
    int index = 0;
    subsetsUtil(A, res, subset, index);
    // also includes the empty set so consider if(subsets.size())
    return res;
}

int binadd(int a, ll b, int mod) {  // computes a*b using addition in log2(b) steps
    int res = 0;
    a %= mod;
    while (b) {
        if (b & 1)
            res = (ll(res) + a) % mod;
        a = (ll(a) + a) % mod;
        b >>= 1;
    }
    return res;
}

int binpow(int a, ll b, int mod) {  // binary exponentiation
    int res = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            res = ll(binadd(res, a, mod)) % mod;

        a = ll(binadd(a, a, mod)) % mod;
        b >>= 1;
    }
    return res;
}

ll invmd(ll a, ll m) { return ll(binpow(a, m - 2, m)); }  // computes MMI using Fermat's little theorem

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

void genphi() {  // computes phi from 1 to mex-1 using the divisor sum property
    for (int i = 1; i < mex; i++) {
        phi[i] += i;
        for (int j = i + i; j < mex; j += i)
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
    // Solutions of the form : x = x0 + (k * b)/g | y = y0 - (k * a)/g
    ll g = exgcd(b, a % b, y, x);
    y = y - a / b * x;
    return g;
}

ll inv(ll a, int mod) {  // modular inverse with extended Euclidean algorithm
    ll x, y;
    exgcd(a, mod, x, y);
    return (x + mod) % mod;  // normalize
}

ll cx(ll x, int p) {  // the biggest exponent c such that p^c divides x!
    ll res = 0;
    while (x) {
        x /= p;
        res += x;
    }
    // computed using Legendre formula
    return res;
}

int gx(ll x, int p, int k, int mod) {  // computes g(x) = x!/p^c(x) mod p^b using recursion and wo auxiliary memory
    if (!x)
        return 1;
    int temp = 1;
    for (int i = 1; i <= x % mod; i++)
        if (i % p)
            temp = ll(temp) * i % mod;
    temp = ll(temp) * gx(x / p, p, k, mod) % mod;
    if (x / mod % 2 && (p > 2 || (p == 2 && k == 2)))
        temp = (mod - temp) % mod;
    return temp;
}

int comb(ll n, ll m, int p, int k) {  // computes nCk modulo mod = p^k where p is prime
    int mod = binpow(p, k, md);
    int temp = ll(gx(n, p, k, mod)) * inv(gx(m, p, k, mod), mod) % mod * inv(gx(n - m, p, k, mod), mod) % mod;
    int s = cx(n, p) - cx(m, p) - cx(n - m, p);
    temp = ll(temp) * binpow(p, s, mod) % mod;  // nCk modulo mod = g(n)/((g(n-k)*g(k))*p^(c(n)-c(n-k)-c(k))
    return temp;
}

int combcat(ll n, int p, int k) {  // computes Catalan(n) modulo mod = p^k where p is prime
    int mod = binpow(p, k, md);
    int temp = ll(gx(2 * n, p, k, mod)) * inv(gx(n + 1, p, k, mod), mod) % mod * inv(gx(n, p, k, mod), mod) % mod;
    int s = cx(2 * n, p) - cx(n + 1, p) - cx(n, p);
    temp = ll(temp) * binpow(p, s, mod) % mod;
    // Catalan(n) modulo mod = g(2*n)/((g(n+1)*g(n))*p^(c(2*n)-c(n+1)-c(n))
    return temp;
}

int C(ll n, int m) {  // computes Catalan(n) modulo (p1^e1)*(p2^e2)*...*(pn^en) using comb and CRT
    if (m == md)
        return int(Cmd(n, md));
    int temp = m;
    int ans = 0;
    for (int i = 2; i <= temp; i++)  // prime decomposition of m
        if (temp % i == 0) {
            int pitoei = 1;  // pi^ei
            int ei = 0;
            while (temp % i == 0) {
                pitoei *= i;
                ei++;
                temp /= i;
            }
            int v = combcat(n, i, ei);                                                 // Computes Catalan(n) modulo pi^ei
            ans = (ll(v) * inv(m / pitoei, pitoei) % m * (m / pitoei) % m + ans) % m;  // CRT formula
        }
    return ans;
}

int nCk(ll n, ll k, int m) {  // computes nCk modulo (p1^e1)*(p2^e2)*...*(pn^en) using comb and CRT
    if (m == md)
        return int(nCkmd(n, k, md));
    int temp = m;
    int ans = 0;
    for (int i = 2; i <= temp; i++)  // prime decomposition of m
        if (temp % i == 0) {
            int pitoei = 1;  // pi^ei
            int ei = 0;
            while (temp % i == 0) {
                pitoei *= i;
                ei++;
                temp /= i;
            }
            int v = comb(n, k, i, ei);                                                 // Computes nCk modulo pi^ei
            ans = (ll(v) * inv(m / pitoei, pitoei) % m * (m / pitoei) % m + ans) % m;  // CRT formula
        }
    return ans;
}
#pragma endregion Combinatorics

ll n, m, a, d;
int tt;
int main() {
    io;
    cin >> tt;
    while (tt--) {
        cin >> n >> m >> a >> d;
        if (a == 1)
            cout << 0 << '\n';
        else {
            vector<ll> v = {a, a + d, a + 2 * d, a + 3 * d, a + 4 * d};
            vector<vector<ll>> subs = subsets(v);
            vector<pair<ll, ll>> vans;
            for (auto el : subs) {
                if (el.size()) {
                    ll ans = 1;
                    for (auto it : el)
                        ans = lcm(ans, it);
                    vans.push_back({ans, el.size()});
                }
            }
            ll ans1 = 0;
            ll ans2 = 0;
            for (auto el : vans)
                if (el.second & 1) {
                    ans1 += (n - 1) / el.first;
                    ans2 += m / el.first;
                } else {
                    ans1 -= (n - 1) / el.first;
                    ans2 -= m / el.first;
                }
            ans1 = n - 1 - ans1;
            if (n == 1)
                ans1 = 0;
            ans2 = m - ans2;
            cout << ans2 - ans1 << '\n';
        }
    }
    return 0;
}