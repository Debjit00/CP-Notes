#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define loop(n) for(int i=0; i<n; i++)
#define rloop(n) for(int i=n-1; i>=0; i--)

int solve() {
    int n, pos=0, neg=0, ans=0;
    cin >> n;
    loop(n) {
        cin >> ans;
        if (ans==1) pos++;
        else neg++;
    }

    ans=neg%2;
    if (neg-neg%2>n/2) ans += neg-neg%2-n/2+n/2%2;

    return ans;
}

int main() {
    int t;
    cin >> t;

    while(t--) cout << solve() << endl;
    return 0;
}
// https://codeforces.com/problemset/problem/1834/A
