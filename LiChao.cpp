template <class T>
struct Line {
    T m, c;
    Line(): Line(0, - numeric_limits<T>::max() / 2) {}
    Line(T _m, T _c): m(_m), c(_c) {}
    T operator() (T x) {
        return m * x + c;
    } 
};  
template <class T>
struct LiChao {
    using Line = Line<T>;
    vector<Line> st;

    LiChao(int n) {
        st.resize(n << 2);
    }

    void insert(int l, int r, Line seg, int i = 1) {
        if(l == r) {
            if(seg(l) > st[i](l)) st[i] = seg;
            return;
        }
        int m = (l + r) >> 1;
        if(st[i].m > seg.m) swap(st[i], seg);
        if(st[i](m) < seg(m)) {
            swap(st[i], seg);
            insert(l, m, seg, i << 1);
        } else insert(m + 1, r, seg, i << 1 | 1);
    }
    
    T query(int l, int r, int x, int i = 1) {
        if(l == r) return st[i](x);
        int m = (l + r) >> 1;
        if(x <= m) return max(st[i](x), query(l, m, x, i << 1));
        else return max(st[i](x), query(m + 1, r, x, i << 1 | 1));
    }
};
//https://codeforces.com/gym/316406/my
