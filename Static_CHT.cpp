template <class T = ll>
class Convex_hull_trick_monotonous {
	// 参考 : https://satanic0258.hatenablog.com/entry/2016/08/16/181331
 
	int n; // 記録している直線の本数
	bool min_flag;
	deque<pair<T, T>> lines; // 直線を傾き狭義降順に記録したリスト
 
public:
	Convex_hull_trick_monotonous(bool min_flag = true) : n(0), min_flag(min_flag) {
		// verify : https://atcoder.jp/contests/dp/tasks/dp_z
	}
 
	// 直線 y = a x + b を追加する．
	void insert(T a, T b) {
		// verify : https://atcoder.jp/contests/dp/tasks/dp_z
 
		if (!min_flag) { a *= -1; b *= -1; }
 
		while (n >= 2) {
			const auto& [a1, b1] = lines[n - 2];
			const auto& [a2, b2] = lines[n - 1];
 
			// y = a2 x + b2 が必要な直線なら消去をここまでにする．
			if ((a1 - a2) * (b - b2) > (a2 - a) * (b2 - b1)) break;
 
			lines.pop_back();
			n--;
		}
		lines.emplace_back(a, b);
		n++;
	}
 
	// a x + b の最小値[最大値] を返す．
	T get(T x) {
		// verify : https://atcoder.jp/contests/dp/tasks/dp_z
 
		while (n >= 2) {
			const auto& [a1, b1] = lines[0];
			const auto& [a2, b2] = lines[1];
 
			if (a1 * x + b1 < a2 * x + b2) break;
			lines.pop_front();
			n--;
		}
 
		T val(INFL);
		if (!lines.empty()) {
			const auto& [a, b] = lines[0];
			val = a * x + b;
		}
		if (!min_flag) val *= -1;
		return val;
	}
};
