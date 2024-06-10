template<int K = 2>
struct StringHash {   //0 based
    using ll = long long;
    static inline array<ll, 3> mods = {1000000007, 998244353, 1000000009};
    
    int n;
    array<ll, K> base;
    array<ll, K> M;
    vector<array<ll, K>> ps;
    vector<array<ll, K>> powf;
    
    StringHash(string s) {
        n = s.length();
        ps.resize(n + 1);
        powf.resize(n + 1);
        powf[0].fill(1);

        getRand();
        build(s);
    }
    
    StringHash(string s, const StringHash<K>& p){
        n = s.length();
        ps.resize(n + 1);
        powf.resize(n + 1);
        powf[0].fill(1);

        M = p.M;
        base = p.base;
        build(s);
    }

    void build(string s){

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < K; j++) {
                ps[i][j] = (base[j] * ps[i - 1][j] + s[i - 1] + 1) % M[j];
                powf[i][j] = (powf[i - 1][j] * base[j]) % M[j];
            }
        }
    }

    inline void getRand(){
        for (int i = 0; i < K; i++) {
            M[i] = mods[rng() % 3];
            base[i] = rng() % (M[i] / 10);
        }
    }

    inline array<ll, K> getHash(string s) {
        int n = s.length();
        array<ll, K> ps;
 
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < K; j++) {
                ps[j] = (base[j] * ps[j] + s[i - 1] + 1) % M[j];
            }
        }
 
        return ps;
    }
 
    inline array<ll, K> substrHash(int start, int end)  {
        array<ll, K> res;
        for (int j = 0; j < K; j++) {
            ll rem = (powf[end - start + 1][j] * ps[start][j]) % M[j];
            res[j] = (ps[end + 1][j] - rem + M[j]) % M[j];
        }
        return res;
    }
 
    inline bool operator==(StringHash<K> &other) {
        return (ps.back() == other.ps.back());
    }

    inline bool isPali(int l,int r,StringHash<K> &bc){
        if(l == r)return true;
        int del = (r - l + 1)/2 - 1;
        return substrHash(l, l + del) == bc.substrHash(n - r - 1, n - r - 1 + del);
    }
};
