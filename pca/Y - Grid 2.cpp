// https://atcoder.jp/contests/dp/tasks/dp_y
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

#pragma region Debug
#define sim template <class c
#define ris return *this
#define dor > debug& operator<<
#define eni(x) sim > typename enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef HOME
    ~debug() { /*cerr << endl;*/
    }
    eni(!=) cerr << boolalpha << i;
    ris;
} eni(==) ris << range(begin(i), end(i));
}
sim, class b dor(pair<b, c> d) {
    ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; ++it)
        *this << ", " + 2 * (it == d.b) << *it;
    ris << "]";
}
#else
    sim dor(const c&) { ris; }
#endif
}
;
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define dbg(x)          \
    debug() << imie(x); \
    cerr << endl
#define darr(x)                                          \
    debug() << " [" << #x ": " << range(all(x)) << "] "; \
    cerr << endl
#define darr2D(x)                                  \
    size_t step = 0;                               \
    cerr << " [" << #x ": [";                      \
    for_each(all(x), [&step](const auto& it) { debug() << range(all(it)); if(step < sizeof(x) / sizeof(x[0])-1) cerr << ", "; ++step; }); \
    cerr << "]] " << endl
#define TwoD(x)                                    \
    size_t step = 0;                               \
    cerr << "[";                                   \
    for_each(all(x), [&step](const auto& it) { debug() << range(all(it)); if(step < sizeof(x) / sizeof(x[0])-1) cerr << ", "; ++step; }); \
    cerr << "]"
#define darr3D(x)                                    \
    size_t step1 = 0;                                \
    cerr << " [" << #x ": [";                        \
    for_each(all(x), [&step1](const auto& it1) { TwoD(it1); if(step1 < sizeof(x) / sizeof(x[0])-1) cerr << ", "; ++step1; }); \
    cerr << "]] " << endl
#pragma endregion Debug

#pragma region Constraints and Declarations
const ll mex = 200010;      // edit considering conditions
const ll mex2 = 3010;       // edit considering conditions
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

int H, W, N;
vector<pair<int, int>> points;
ll dp[mex2];
int main() {
    io;
    genfs();  // generates the factorial and inverse factorial
    cin >> H >> W >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back({x, y});
    }
    points.push_back({H, W});
    sort(all(points));
    for (int i = 0; i <= N; i++) {
        dp[i] = nCk(points[i].first + points[i].second - 2, points[i].first - 1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int dy = points[j].first - points[i].first;
            int dx = points[j].second - points[i].second;
            if (dx < 0 || dy < 0)
                continue;
            dp[j] -= (nCk(dx + dy, dy) * dp[i]) % mod;
            dp[j] %= mod;
        }
    }
    if (dp[N] < 0)
        dp[N] += mod;
    cout << dp[N];

    return 0;
}