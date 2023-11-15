// GRID DFS
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

// GRID BFS
void bfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis) {
    int n=grid.size();
    int m=grid[0].size();
    queue<pair<int, int>> q;
    
    int drow[] = {-1, 1, 0, 0};
    int dcol[] = {0, 0, -1, 1};
    while(!q.empty()) {
        int r=q.front().first;
        int c=q.front().second;
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
