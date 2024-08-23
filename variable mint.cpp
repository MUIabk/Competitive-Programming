ll myRand(ll B) {
    return (ull)rng() % B;
}
 
 
ll MOD = 998244353;
struct Mint { // 1000000007  1000000009
    ll x;
 
    Mint() : x(0) {}
    Mint(ll _x) {
        _x %= MOD;
        if (_x < 0) _x += MOD;
        x = _x;
    }
 
    Mint& operator += (const Mint &a) {
        x += a.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    Mint& operator -= (const Mint &a) {
        x += MOD - a.x;
        if (x >= MOD) x -= MOD;
        return *this;
    }
    Mint& operator *= (const Mint &a) {
        x = (ull)x * a.x % MOD;
        return *this;
    }
    Mint pow(ll pw) const {
        Mint res = 1;
        Mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    Mint inv() const {
        assert(x != 0);
        ll t = x;
        ll res = 1;
        while(t != 1) {
            ll z = MOD / t;
            res = (ull)res * (MOD - z) % MOD;
            t = MOD - t * z;
        }
        return res;
    }
    Mint& operator /= (const Mint &a) {
        return *this *= a.inv();
    }
    Mint operator + (const Mint &a) const {
        return Mint(*this) += a;
    }
    Mint operator - (const Mint &a) const {
        return Mint(*this) -= a;
    }
    Mint operator * (const Mint &a) const {
        return Mint(*this) *= a;
    }
    Mint operator / (const Mint &a) const {
        return Mint(*this) /= a;
    }
 
    bool sqrt(Mint &res) const {
        if (MOD == 2 || x == 0) {
            res = *this;
            return true;
        }
        if (pow((MOD - 1) / 2) != 1) return false;
        if (MOD % 4 == 3) {
            res = pow((MOD + 1) / 4);
            return true;
        }
        int pw = (MOD - 1) / 2;
        int K = 30;
        while((1 << K) > pw) K--;
        while(true) {
            Mint t = myRand(MOD);
            Mint a = 0, b = 0, c = 1;
            for (int k = K; k >= 0; k--) {
                a = b * b;
                b = b * c * 2;
                c = c * c + a * *this;
                if (((pw >> k) & 1) == 0) continue;
                a = b;
                b = b * t + c;
                c = c * t + a * *this;
            }
            if (b == 0) continue;
            c -= 1;
            c *= Mint() - b.inv();
            if (c * c == *this) {
                res = c;
                return true;
            }
        }
        assert(false);
    }
 
    bool operator == (const Mint &a) const {
        return x == a.x;
    }
    bool operator != (const Mint &a) const {
        return x != a.x;
    }
    bool operator < (const Mint &a) const {
        return x < a.x;
    }
};
struct Factorials {
    vector<Mint> f, fi;
 
    Factorials() : f(), fi() {}
    Factorials(int n) {
        n += 10;
        f = vector<Mint>(n);
        fi = vector<Mint>(n);
        f[0] = 1;
        for (int i = 1; i < n; i++)
            f[i] = f[i - 1] * i;
        fi[n - 1] = f[n - 1].inv();
        for (int i = n - 1; i > 0; i--)
            fi[i - 1] = fi[i] * i;
    }
 
    Mint C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return f[n] * fi[k] * fi[n - k];
    }
};
struct Powers {
    vector<Mint> p, pi;
 
    Powers() : p(), pi() {}
    Powers(int n, Mint x) {
        n += 10;
        if (x == 0) {
            p = vector<Mint>(n);
            p[0] = 1;
        } else {
            p = vector<Mint>(n);
            pi = vector<Mint>(n);
            p[0] = pi[0] = 1;
            Mint xi = x.inv();
            for (int i = 1; i < n; i++) {
                p[i] = p[i - 1] * x;
                pi[i] = pi[i - 1] * xi;
            }
        }
    }
 
    Mint pow(int n) {
        if (n >= 0)
            return p[n];
        else
            return pi[-n];
    }
};
struct Inverses {
    vector<Mint> ii;
 
    Inverses() : ii() {}
    Inverses(int n) {
        n += 10;
        ii = vector<Mint>(n);
        ii[1] = 1;
        for (int x = 2; x < n; x++)
            ii[x] = Mint() - ii[MOD % x] * (MOD / x);
    }
 
    Mint inv(Mint x) {
        assert(x != 0);
        ll t = x.x;
        ll res = 1;
        while(t >= (int)ii.size()) {
            ll z = MOD / t;
            res = (ull)res * (MOD - z) % MOD;
            t = MOD - t * z;
        }
        return ii[t] * res;
    }
};
