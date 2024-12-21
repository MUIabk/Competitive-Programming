vector<int> kmp(const string& s) {
	vector<int> p(sz(s));
	for(int i = 1; i < sz(s); i ++) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> match(const string& s, const string& pat) {
	vector<int> p = kmp(pat + '\0' + s), res;
	for(int i = sz(p) - sz(s); i < sz(p); i ++) 
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

vector<vector<int>>aut;

void compute_automaton(string s){
    s += '#';
    vector<int> pi = kmp(s);
    int n = s.size();
    for(int i = 0 ; i < n ;i++ ){
        for(int j = 0 ; j < 26 ; j ++ ){
            if(i > 0 && s[i]!='a'+j){
                aut[i][j] = aut[pi[i-1]][j];
            }else{
                aut[i][j] = i + ('a'+j == s[i]);
            }
        }
    }
}
