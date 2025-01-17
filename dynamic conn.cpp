struct DSUrb {
    int sz; vector<int> e; void init(int n) { e = vector<int>(n+1,-1); sz = n; }
    int get(int x) { return e[x] < 0 ? x : get(e[x]); } 
    int size(int x) { return -e[get(x)]; }
    vector<array<int,4>> mod;

    void inline rem(int s) { sz --; }
    void inline add(int s) { sz ++; }

    bool unite(int x, int y) { // union-by-rank
        x = get(x), y = get(y); 
        if (x == y) { mod.pb({-1,-1,-1,-1}); return 0; }
        if (e[x] > e[y]) swap(x,y);
        mod.pb({x,y,e[x],e[y]});
        rem(-e[x]); rem(-e[y]);
        e[x] += e[y]; e[y] = x;
        add(-e[x]);
        return 1;
    }
    void rollback() {
        auto a = mod.back(); mod.pop_back();
        if(a[0] == -1) return;
        rem(-e[a[0]]);
        e[a[0]] = a[2]; e[a[1]] = a[3];
        add(-e[a[0]]); add(-e[a[1]]);
    }
};

struct DynaCon { 
    int SZ;
    DSUrb D; vector<vector<pair<int,int>>> seg;
    vector<int> ans;
    DynaCon(int n){ SZ = n; ans.resize(n); seg.resize(2*SZ); }
    void init(int n){ D.init(n);}
    void upd(int l, int r, pair<int,int> p) {  // add edge p to all times in interval [l, r) i.e. it is removed at r
        for (l += SZ, r += SZ; l < r; l /= 2, r /= 2) {
            if (l&1) seg[l++].pb(p);
            if (r&1) seg[--r].pb(p);
        }
    }
    void solve(int i) { 
        ans[i] = D.sz; 
    }
    void process(int ind = 1) {
        for(auto &t: seg[ind]) D.unite(t.first,t.second);
        if (ind >= SZ) {
            solve(ind - SZ);
        } else process(ind << 1), process(ind << 1 | 1);
        for(auto &t: seg[ind]) D.rollback();
    }
};
