template<class T>
struct adder{
	int n;
	vector<T> data;
	adder(int n): n(n), data(n + 2){}
	void update(int l, int r, T start, T step){
        r ++;
		if(l < 0 or l > r or l > n) return;
		data[l] += start;
		data[l + 1] -= start - step;
		data[r] -= start + (r - l) * step;
		data[r + 1] += start + (r - l - 1) * step;
	}
	vector<T> solve() const{
		vector<T> res(data.begin(), data.end() - 2);
		for(auto i = 1; i < n; ++ i) res[i] += res[i - 1];
		for(auto i = 1; i < n; ++ i) res[i] += res[i - 1];
		return res;
	}
};
