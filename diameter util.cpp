auto dist = [&] (int s, int n, vector<vector<int>> &adj) {
    vector<int> d(n, -1);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto &v : adj[u]) {
            if(d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d;
};
auto diameter = [&] (int n, vector<vector<int>> &adj) {
    auto d1 = dist(0, n, adj);
    int dia1 = max_element(d1.begin(), d1.end()) - d1.begin();
    auto d2 = dist(dia1, n, adj);
    return *max_element(d2.begin(), d2.end()) + 1;
};
