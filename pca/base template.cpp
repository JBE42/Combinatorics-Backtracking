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

int main() {
    io;

    return 0;
}