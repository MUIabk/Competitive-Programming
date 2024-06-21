template<typename Node>
struct treedp {
    int n;
    vector<Node>dp,ans;
    treedp(int _n){
        n=_n+1;
        dp.assign(n,Node());
        ans.assign(n,Node());
    }
    void init(int u,int p,vector<vector<int>>&adj){
        for(auto &v:adj[u]){
            if(v==p)continue;
            init(v,u,adj);
            dp[u].merge(dp[v]);
        }
    }
    void propagate(int u,int p,vector<vector<int>>&adj){
        ans[u]=dp[u];
        for(auto &v:adj[u]){
            if(v==p)continue;
            dp[u].split(dp[v]);
            dp[v].merge(dp[u]);
            propagate(v,u,adj);
            dp[v].split(dp[u]);
            dp[u].merge(dp[v]);
        }
    }
    vector<Node> rooted(int root,vector<vector<int>>&adj){
        init(root,root,adj);
        return dp;
    }
    vector<Node> reroot(int root,vector<vector<int>>&adj){
        rooted(root,adj);
        propagate(root,root,adj);
        return ans;
    }
};
struct Node{
    int take,ntake;
    Node(){
        take=1;
        ntake=0;
    }
    void merge(const Node &c){
        take+=c.ntake;
        ntake+=max(c.take,c.ntake);
    }
    void split(const Node &c) {
        take-=c.ntake;
        ntake-=max(c.take,c.ntake);
    }
};

//initially return Maximum Independent Set dp
