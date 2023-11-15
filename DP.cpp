// DP Subset Sum
bool isPossible(int n, int k, vector<int> &arr) {
	vector<vector<bool>> dp(n, vector<bool> (k+1));
	for(int i=0; i<n; i++) dp[i][0] = 1;
	if (k >= arr[0]) dp[0][arr[0]] = 1;
	for (int i=1; i<n; i++) {
	    for (int target=1; target <= k; target++) {
		if (target >= arr[i]) 
		    dp[i][target] = dp[i-1][target] | dp[i-1][target-arr[i]];
		else dp[i][target] = dp[i-1][target];
	    }
	}
	return dp[n-1][k];
}

int totalSubsequences(int n, int k, vector<int> &arr) {
	vector<vector<int>> dp(n, vector<int> (k+1));
    for(int i=0; i<n; i++) dp[i][0] = 1;
    if (arr[0] <= k) dp[0][arr[0]] += 1;
    for (int i=1; i<n; i++) {
        for (int target=0; target <= k; target++) {
            if (target >= arr[i]) 
                dp[i][target] = (dp[i-1][target] + dp[i-1][target-arr[i]]) % mod;
            else dp[i][target] = dp[i-1][target];
        }
    }
    return dp[n-1][k];
}
