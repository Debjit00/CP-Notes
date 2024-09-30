// Disjoint Set Union(DSU):
class UnionFind {
    private: vector<int> p, rank;
    public:
        UnionFind(int n) {
            rank.assign(n,0); p.assign(n,0);
            iota(p.begin(),p.end(),0);
        }
        int findSet(int i){ return (p[i] == i) ? i : p[i] = findSet(p[i]);}
        bool isSameSet(int i, int j){ return findSet(i) == findSet(j);}
        void unionSet(int i, int j) {
            if(!isSameSet(i,j)) {
                int x = findSet(i), y = findSet(j);
                if(rank[x] > rank[y]) p[y] = x;
                else {
                	p[x] = y;
                	if(rank[x] == rank[y]) rank[y]++;
                }
            }
        }
};

struct UnionFind {
    int n, set_size, *parent, *rank;
    UnionFind(){}
    UnionFind(int a) {
        n = set_size = a;
        parent = new int[n+1];
        rank = new int[n+1];
        for(int i=1; i<=n; i++) 
            parent[i]=i, rank[i]=1;
    }
    int find(int x) {
        if(x != parent[x]) return parent[x] = find(parent[x]);
        else return x;
    }
    void merge(int x, int y) {
        int xroot = find(x), yroot = find(y);
        if (xroot != yroot) {
            if(rank[xroot] >= rank[yroot]) {
                parent[yroot] = xroot;
                rank[xroot] += rank[yroot];
            }
            else {
                parent[xroot] = yroot;
                rank[yroot] += rank[xroot];
            }
            set_size -= 1;
        }
    }
    void reset() {
        set_size=n;for(int i=1;i<=n;i++)parent[i]=i,rank[i]=1;}
    int size() {return set_size;}
};

// Floyd Warshall's algorithms:
void floydWarshall(vvll &dist, int n) {
    for (int k=0; k < n; k++)
        for (int i=0; i < n; i++)
            for (int j=0; j < n; j++)
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] < 2e9 && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
}

// ADJACENCY GRID
void dfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>>  &vis) {
    int n=grid.size();
    int m=grid[0].size();
    vis[r][c] = 1;
    
    int drow[] = {1, -1, 0, 0};
    int dcol[] = {0, 0, -1, 1};
    for(int i=0; i<4; i++) {
        int nrow=r+drow[i];
        int ncol=c+dcol[i];
        
        if(nrow<0 || ncol<0 || nrow==n || ncol==m) continue;
        else if(grid[nrow][ncol] == 1 && !vis[nrow][ncol]) {
            
        }
    }
}

void bfs(int row, int col, vector<vector<int>> &grid, vector<vector<int>> &vis) {
    int n=grid.size();
    int m=grid[0].size();
    queue<pair<int, int>> q;
    q.push({row, col});
    
    int drow[] = {-1, 1, 0, 0};
    int dcol[] = {0, 0, -1, 1};
    while(!q.empty()) {
        int r=q.front().first;
        int c=q.front().second;
        vis[r][c] = 1;
        q.pop();
        
        for(int i=0; i<4; i++) {
            int nrow=r+drow[i];
            int ncol=c+dcol[i];
            
            if(nrow<0 || ncol<0 || nrow==n || ncol==m) continue;
            else if (grid[nrow][ncol] == 0 && !vis[nrow][ncol]) {
                
            }
        }
    }
}

// SCC (Strongly Connected Components | Kosaraju's Algorithm):
vvll SCC(vvll &adj) {
	int n = adj.size();
	vvll radj(n), res;
	vll vis(n), order;

	function<void(int)> dfs = [&](int node) {
		if(vis[node]) return;
		vis[node] = 1;

		for(auto i: adj[node]) {
			radj[i].push_back(node);
			dfs(i);
		}
		order.push_back(node);
	};

	for(int i=0; i<n; i++)
		dfs(i);

	reverse(all(order));

	vll strongComp;
	vis = vll(n, 0);
	function<void(ll)>dfs2 = [&](ll node) {
		if(vis[node]) return;
		vis[node] = 1;
		for(auto i: radj[node]) {
			dfs2(i);
		}
		strongComp.push_back(node);
	};

	for(int i=0; i<n; i++) {
		strongComp = vll(0);
		dfs2(i);
		if(strongComp.size()) res.push_back(strongComp);
	}

	sort(all(res), judge);
	return res;
}
//*************************************************************************************************************************************************************************
