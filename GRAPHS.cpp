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
    q.push(row, col);
    
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
//*************************************************************************************************************************************************************************

// ADJACENCY LIST
void bfs(int node, vector<int> adj[], vector<int> &vis) {
    queue<int> q;
    q.push(node);
    vis[node] = 1;
    
    while(!q.empty()) {
        node = q.front();
        q.pop();
        
        for(int it: adj[node]) {
            if(!vis[it]) {
                vis[it] = 1;
                q.push(it);
            }
        }
    }
    
}

void dfs(

