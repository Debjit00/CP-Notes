// GRID DFS
void dfs(int r, int c, vector<vector<char>> &mat, vector<vector<int>>  &vis) {    
    int drow[] = {1, -1, 0, 0};
    int dcol[] = {0, 0, -1, 1};
    for(int i=0; i<4; i++) {
        int nrow=r+drow[i];
        int ncol=c+dcol[i];
        
        if(nrow<0 || ncol<0 || nrow==mat.size() || ncol==mat[0].size()) continue;
        else if(mat[nrow][ncol] == 'O' && !vis[nrow][ncol]) {
            
        }
    }
}

// GRID BFS
void bfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis) {
    int n=grid.size();
    int m=grid[0].size();
    queue<pair<pair<int, int>, int>> q;
    
    int drow[] = {-1, 1, 0, 0};
    int dcol[] = {0, 0, -1, 1};
    while(!q.empty()) {
        int r=q.front().first.first;
        int c=q.front().first.second;
        int d=q.front().second+1;
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
