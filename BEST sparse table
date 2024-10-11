template<typename Node>
struct sparse {
	vector<vector<Node>> table;
	vector<int> logValues;
	int n;
	int maxLog;
	vector<int> a;
	sparse(int n1, vector<int> &arr) {
		n = n1;
		a = arr;
		table.resize(n);
		logValues.resize(n + 1);
		maxLog = log2(n);
		logValues[1] = 0;
		for (int i = 2; i <= n; i++) {
			logValues[i] = logValues[i / 2] + 1;
		}
		for (int i = 0; i < n; i++) {
			table[i].resize(maxLog + 1);
			fill(all(table[i]), Node());
		}
		build();
	}
	void build() {
		for (int i = 0; i < n; i++) {
			table[i][0] = Node(a[i]);
		}
		for (int i = 1; i <= maxLog; i++) {
			for (int j = 0; (j + (1 << i)) <= n; j++) {
				table[j][i].merge(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
	Node queryNormal(int left, int right) {
        	if(right < left) return Node();
		Node ans = Node();
		for (int j = logValues[right - left + 1]; j >= 0; j--) {
			if ((1 << j) <= right - left + 1) {
				ans.merge(ans, table[left][j]);
				left += (1 << j);
			}
		}
		return ans;
	}
	Node queryIdempotent(int left, int right) {        //min, max, gcd, and, or
        	if(right < left) return Node();
		int j = logValues[right - left + 1];	   //xor is not idempotent
		Node ans = Node();
		ans.merge(table[left][j], table[right - (1 << j) + 1][j]);
		return ans;
	}
};
struct Node1 {
	int val; // store more info if required
	Node1() { // Identity Element
		val = 0;
	}
	Node1(ll v) {
		val = v;
	}
	void merge(Node1 &l, Node1 &r) {
		val = l.val ^ r.val;
	}
};
