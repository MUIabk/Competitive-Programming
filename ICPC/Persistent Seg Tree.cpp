int id = -1;
struct Node {
    int val;
    int lc, rc;
    Node(): Node(0) {}
    Node(int x) {
        val = x;
        lc = rc = - 1;
    }

    void merge(Node &l, Node &r, int lid, int rid) {
        val = l.val + r.val;
        lc = lid, rc = rid;
    }

    void update(int x) {
        val = x;
    }

} st[N * 28];

int build(int l = 0, int r = n - 1) {
    if(l == r) {
        st[++ id] = Node(a[l]);
        return id;
    }
    int m = (l + r) >> 1;
    int lc = build(l, m);
    int rc = build(m + 1, r);
    st[++ id].merge(st[lc], st[rc], lc, rc);
    return id;
}

int update(int i, int pos, int val, int l = 0, int r = n - 1) {
    if(l == r) {
        st[++ id].update(val);
        return id;
    }
    int m = (l + r) >> 1;
    if(pos <= m) {
        int lc = update(st[i].lc, pos, val, l, m);
        st[++ id].merge(st[lc], st[st[i].rc], lc, st[i].rc);
    } else {
        int rc = update(st[i].rc, pos, val, m + 1, r);
        st[++ id].merge(st[st[i].lc], st[rc], st[i].lc, rc);
    }
    return id;
}

Node get(int i, int x, int y, int l = 0, int r = n - 1) {
    if(x > y or l > y or r < x) return 0;
    if(x <= l and r <= y) return st[i];
    int m = (l + r) >> 1;
    Node res, lc, rc;
    lc = get(st[i].lc, x, y, l, m);
    rc = get(st[i].rc, x, y, m + 1, r);
    res.merge(lc, rc, -1, -1);
    return res;
}

int copy(int i) {
    st[++ id] = st[i];
    return id;
}
