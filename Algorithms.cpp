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
