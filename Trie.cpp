template<const int BIT = 26>
struct Trie {
    struct Node {
        int nxt[BIT];
        int end, cnt;
        Node(){
            for(int x = 0; x < BIT; x++) nxt[x] = -1;
            end = 0;
            cnt = 0;
        }
    };
    vector<Node> trie;
    int sz;
    Trie() {
        trie.push_back(Node());
        sz = 0;
    }
    
    void insert(vector<int> &word) {
        int cur = 0;
        sz ++;
        for(auto &x : word) {
            if(trie[cur].nxt[x] == -1) {
                trie.push_back(Node());
                trie[cur].nxt[x] = trie.size() - 1;
            }
            cur = trie[cur].nxt[x];
            trie[cur].cnt ++;
        }
        trie[cur].end ++;
    }
    
    void rem(vector<int> &word) {
        int cur = 0;
        sz --;
        for(auto &x : word) {
            assert(~trie[cur].nxt[x]);
            cur = trie[cur].nxt[x];
            assert(trie[cur].cnt);
            trie[cur].cnt --;
        }
        assert(trie[cur].end);
        trie[cur].end --;
    }

    bool search(vector<int> &word) {
        int cur = 0;
        for(auto &x : word) {
            if(~trie[cur].nxt[x] and trie[trie[cur].nxt[x]].cnt){
                cur = trie[cur].nxt[x];
            }else return false;
        }
        return trie[cur].end;
    }
    
    int max_xor(vector<int> &word) {
        if(!sz) return -1;
        int cur = 0;
        int ans = 0;
        int p = 1 << (int)word.size() - 1;
        for(auto &x : word) {
            if(~trie[cur].nxt[x ^ 1] and trie[trie[cur].nxt[x ^ 1]].cnt) {
                cur = trie[cur].nxt[x ^ 1];
                ans |= p;
            }else {
                cur = trie[cur].nxt[x];
            }
            p >>= 1;
        }
        return ans;
    }
};
