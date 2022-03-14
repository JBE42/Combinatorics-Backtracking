//  https://open.kattis.com/problems/fiat
#include <iostream>
using namespace std;
long long q;
long long f[1000001];

long long pow(long long a, long long b, long long MOD) {
    long long x = 1, y = a;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x * y);
            if (x > MOD) x %= MOD;
        }
        y = (y * y);
        if (y > MOD) y %= MOD;
        b /= 2;
    }
    return x;
}

/* Modular Multiplicative Inverse
 Using Euler's Theorem
 a^(phi(m)) = 1 (mod m)
 a^(-1) = a^(m-2) (mod m) */
long long InverseEuler(long long n, long long MOD) {
    return pow(n, MOD - 2, MOD);
}

long long C(long long n, long long r, long long MOD) {
    return (f[n] * ((InverseEuler(f[r], MOD) * InverseEuler(f[n - r], MOD)) % MOD)) % MOD;
}

int main() {
    cin >> q;
    int INF = 1000000007;
    f[0] = 1;
    for (int i = 1; i <= 1000000; i++)
        f[i] = (f[i - 1] * i) % INF;
    cout << (InverseEuler(q + 1, INF) * C(2 * q, q, INF)) % INF << endl;
}