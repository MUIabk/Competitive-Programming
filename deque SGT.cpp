struct sum_kth_smallest {
 
	struct Node {
		long long sum;
		int cnt;
		int lCh, rCh;//children, indexes into `tree`
	};
 
	int mn, mx;
	vector<int> roots;
	deque<Node> tree;
 
	sum_kth_smallest(const vector<int>& arr) : mn(INT_MAX), mx(INT_MIN), roots(arr.size() + 1, 0) {
		tree.push_back({0, 0, 0}); //acts as null
		for (int val : arr) mn = min(mn, val), mx = max(mx, val);
		for (int i = 0; i < (int)arr.size(); i++)
			roots[i + 1] = update(roots[i], -mx, mx, arr[i]);
	}
	int update(int v, int tl, int tr, int idx) {
		if (tl == tr) {
			tree.push_back({tree[v].sum + tl, tree[v].cnt + 1, 0, 0});
			return tree.size() - 1;
		}
		int tm = tl + (tr - tl) / 2;
		int lCh = tree[v].lCh;
		int rCh = tree[v].rCh;
		if (idx <= tm)
			lCh = update(lCh, tl, tm, idx);
		else
			rCh = update(rCh, tm + 1, tr, idx);
		tree.push_back({tree[lCh].sum + tree[rCh].sum, tree[lCh].cnt + tree[rCh].cnt, lCh, rCh});
		return tree.size() - 1;
	}
 
 
	/* find kth smallest number among arr[l], arr[l+1], ..., arr[r]
	 * k is 1-based, so find_kth(l,r,1) returns the min
	 */
	int query(int l, int r, int k) const {
		assert(1 <= k && k <= r - l + 1); //note this condition implies L <= R
		assert(0 <= l && r + 1 < (int)roots.size());
		return query(roots[l], roots[r + 1], -mx, mx, k);
	}
	int query(int vl, int vr, int tl, int tr, int k) const {
		if (tl == tr)
			return tl;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].lCh].cnt - tree[tree[vl].lCh].cnt;
		if (left_count >= k) return query(tree[vl].lCh, tree[vr].lCh, tl, tm, k);
		return query(tree[vl].rCh, tree[vr].rCh, tm + 1, tr, k - left_count);
	}
 
	/* find **sum** of k smallest numbers among arr[l], arr[l+1], ..., arr[r]
	 * k is 1-based, so find_kth(l,r,1) returns the min
	 */
	long long query_sum(int l, int r, int k) const {
		assert(1 <= k && k <= r - l + 1); //note this condition implies L <= R
		assert(0 <= l && r + 1 < (int)roots.size());
		return query_sum(roots[l], roots[r + 1], -mx, mx, k);
	}
	long long  query_sum(int vl, int vr, int tl, int tr, int k) const {
		if (tl == tr)
			return 1LL * tl * k;
		int tm = tl + (tr - tl) / 2;
		int left_count = tree[tree[vr].lCh].cnt - tree[tree[vl].lCh].cnt;
		long long left_sum = tree[tree[vr].lCh].sum - tree[tree[vl].lCh].sum;
		if (left_count >= k) return query_sum(tree[vl].lCh, tree[vr].lCh, tl, tm, k);
		return left_sum + query_sum(tree[vl].rCh, tree[vr].rCh, tm + 1, tr, k - left_count);
	}
};
