struct Lift{
    int n;
    vector<array<int32_t, 20>> lift;
    vector<int32_t> dpth;
    Lift(const vector<vector<int>> &adj,int N) {
        n = N;
        lift.resize(n+1);
        dpth.resize(n+1);
        fill(all(dpth), 0);
        for(int i = 1 ; i <= n ; i++)    lift[i].fill(0);
        dfs(1, 0, adj);
        for(int j = 1 ; j < 20 ; j++) {
            for(int i = 1 ; i <= n ; i++) {
                lift[i][j] = lift[lift[i][j-1]][j - 1];
            }
        }
    }
    void dfs(int i, int p, const vector<vector<int>> &adj) {
        lift[i][0] = p;
        for(auto &u: adj[i]) {
            if(u == p)  continue;
            dpth[u] = dpth[i] + 1;
            dfs(u, i, adj);
        }
    }
    int kthanc(int node, int d) {
        for(int i = 0 ; i < 20 ; i++) {
            if((d >> i) & 1) node = lift[node][i];
        }
        return node;
    }
    int lca(int x, int y) {
        if(dpth[x] > dpth[y])   swap(x, y);
        y = kthanc(y, dpth[y] - dpth[x]);
        if(x == y)  return x;
        for(int i = 19 ; i >= 0 ; i--) {
            if(lift[y][i] != lift[x][i])    x = lift[x][i], y = lift[y][i];
        }
        return lift[x][0];
    }
    int dist(int x, int y) {
        return dpth[x] + dpth[y] - 2 * dpth[lca(x, y)];
    }
};
