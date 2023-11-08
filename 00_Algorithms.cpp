// DFS
void dfs(int node, vector<vector<int>> &adjLs, vector<int> &vis) {
	vis[node] = 1;
	for(int it: adjLs[node]) {
		if (!vis[it]) {
			dfs(it, adjLs, vis);
		}
	}
}

// Adj Matrix to List
vector<vector<int>> adjLs(V);
for (int i=0; i<V; i++) {
	for (int j=0; j<V; j++) {
		if (adj[i][j] == 1 && i != j) {
			adjLs[i].push_back(j);
			adjLs[j].push_back(i);
		}
	}
}

// DP Subset Sum
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

// SEGMENT TREE
void build(int i, int low, int high, vector<int> &a, vector<int> &seg) {
    if (high == low) {
        seg[i] = a[low];
        return;
    }
    int mid = (low + high)/2;
    build(2*i+1, low, mid, a, seg);
    build(2*i+2, mid+1, high, a, seg);
    seg[i] = max(seg[2*i+1], seg[2*i+2]); //-------------------------------IMP
}
int query(int i, int low, int high , int l, int r, vector<int> &a, vector<int> &seg) {
    if (low>=l && high<=r) return seg[i];
    if (high<l || low>r) return INT_MIN; //-------------------------------IMP
    int mid = (low + high)/2;
    int left = query(2*i+1, low, mid, l, r, a, seg);
    int right = query(2*i+2, mid+1, high, l, r, a, seg);
    return max(left, right); //-------------------------------IMP
}
// INITIALIZE
int n = 1e5;
vector<int> a(n), seg(4*n);
build(0, 0, n-1, a, seg);
// QUERY
query(0, 0, n, l, r, a, seg);
//***********************************************X***********************************************//


// BINARY SEARCH
int bs(vector<int> &a, int s, int e, int x) {
    while(s<=e) {
        int m=(s+e)/2;

        if (x==a[m]) return m;
        else if (x<a[m]) e=m-1;
        else s=m+1;
    }

    return -1;
}

int pivot(vector<int>& arr) {
	int s=0, p=arr.size()-1;
	while(s<=p) {
		int m=(s-p)/2+p;
		if (arr[m]>=arr[0]) s=m+1;
		else p=m-1;
	}
	return p;
}
//***********************************************X***********************************************//



// ABS DIFFERENCE between num1 & num2
string stringDiffs(string num1, string num2) {
    int len1 = num1.length(), len2 = num2.length();
    if (len1 < len2 || (len1 == len2 && num1 < num2))
        swap(num1, num2), swap(len1, len2);

    string result = "";
    int carry = 0;
    for (int i=0; i<len1; i++) {
        int digit1 = num1[len1 - 1 - i] - '0';
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;
        int diff = digit1 - digit2 - carry;
        if (diff < 0) diff += 10, carry = 1;
        else carry = 0;

        result = to_string(diff) + result;
    }

    while (result.length() > 1 && result[0] == '0')
        result.erase(0, 1);

    return result;
}
//***********************************************X***********************************************//
