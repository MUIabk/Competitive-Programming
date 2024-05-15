template<class T>
class BIT {
    public:
    vector<T> bit;  // binary indexed tree
    int n;
 
    BIT(int n) {
        n += 5;
        this->n = n;
        bit.assign(n, T());
    }
 
    BIT(vector<int> const &a) : BIT(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
 
    T sum(int r) {
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
 
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
 
    void add(int idx, T delta) {
        for (; idx < n; idx = (idx | (idx + 1)))
            bit[idx] += delta;
    }

    void add(int l,int r,T delta){
        add(l ,delta);
        add(r+1 ,-delta);
    }
};
