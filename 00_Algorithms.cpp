// POWER
ll power(ll a, ll b, ll m) {
    ll res=1;
    while(b>0) {
        if (b%2) res = (res*a)%m;
        a = (a*a)%m;
        b/=2;
    }
    return res;
}

ll modInverse(ll num, ll m) {
    return power(num, m-2, m);
}

//***********************************************X***********************************************//
// SEGMENT TREE
struct Node{
	ll mini;
	ll cnt;
	Node(ll m=LLONG_MAX, ll c=0) {
		mini = m;
		cnt = c;
	}
};
Node merge(Node a, Node b) {
	if(a.mini == b.mini)
		return Node(a.mini, a.cnt + b.cnt);
	else if (a.mini < b.mini)
		return a;
	else 
		return b;
}
void build(ll index, ll start, ll end, vll &a, vector<Node> &seg) {
    if (end == start) {
        seg[index] = Node(a[start], 1ll);
        return;
    }
    ll mid = (start + end)/2;
    build(2*index, start, mid, a, seg);
    build(2*index+1, mid+1, end, a, seg);
    seg[index] = merge(seg[2*index], seg[2*index+1]);
}
void update(ll index, ll start, ll end, ll pos, ll val, vll &a, vector<Node> &seg) {
	if(pos<start || pos>end) return;
	if(start == end) {
		seg[index] = Node(val, 1);
		a[pos] = val;
		return;
	}
	ll mid = (start + end) / 2;
	update(2*index, start, mid, pos, val, a, seg);
	update(2*index+1, mid+1, end, pos, val, a, seg);
    seg[index] = merge(seg[2*index], seg[2*index+1]);
}
Node query(ll index, ll start, ll end , ll l, ll r, vll &a, vector<Node> &seg) {
    if (start>=l && end<=r) return seg[index];
    if (end<l || start>r) return Node(); //-------------------------IMP
    ll mid = (start + end)/2;
    Node left = query(2*index, start, mid, l, r, a, seg);
    Node right = query(2*index+1, mid+1, end, l, r, a, seg);
    return merge(left, right);
}
// Initialize, Build, Update, Query
ll n = 1e5; vll a(n);
vector<Node> seg(4*n);
build(1, 0, n-1, a, seg);
update(1, 0, n-1, l, r, a, seg);
query(0, 0, n, l, r, a, seg); // Returns Node
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
