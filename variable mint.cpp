template<typename T>
T sqr(T x) {
	return x * x;
}
 
 
template<typename T>
T euclid(T x, T y, T &k, T &l) {
	if (x < 0) {
		T g = euclid(-x, y, k, l);
		k = -k;
		return g;
	}
	if (y < 0) {
		T g = euclid(x, -y, k, l);
		l = -l;
		return g;
	}
	if (y == 0) {
		k = 1;
		l = 0;
		return x;
	}
	T g = euclid(y, x % y, l, k);
	l -= k * (x / y);
	return g;
}
unsigned int MOD = 998244353;
struct Mint {
	unsigned int x;
 
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
		ll g, k, l;
		g = euclid<ll>(x, MOD, k, l);
		assert(g == 1);
		k %= MOD;
		if (k < 0) k += MOD;
		return k;
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
