struct SCC{
    int n;
    vector<vector<int>> g, gr; 
    vector<int> topo, comp ; 
    vector<bool> vis; 
    SCC(int _n) {
        n = _n ; 
        g.resize(n+1) ; gr.resize(n+1) ; 
        comp = vector<int>(n+1, -1); vis.resize(n+1) ; 
    }
    void addEdge(int u, int v) {
        g[u].push_back(v) ; 
        gr[v].push_back(u) ; 
    }
    void dfs1(int node) {
        vis[node] = 1 ;
        for(auto i : g[node]) if(!vis[i]) dfs1(i) ; 
        topo.push_back(node) ;  
    }
    void dfs2(int node, int c) {
        comp[node] = c ;
        for(auto i : gr[node]) if(comp[i] == -1) dfs2(i, c) ; 
    }
    void scc(){
        for(int i=0;i<n;i++)if(!vis[i])dfs1(i);
        int comps=0;for(int i=n-1;i>=0;i--)if(comp[topo[i]]==-1)dfs2(topo[i],comps++);
        set<int>components[comps];
        for(int i=0;i<n;i++)components[comp[i]].insert(i);
    }
};
