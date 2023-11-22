vector<vector<ll>> multiply(vector<vector<ll>> &A, vector<vector<ll>> &B){
    vector<vector<ll>> res(A.size(), vector<ll>(B[0].size(),0));
    if(A[0].size()==B.size()){
        const int N=A[0].size();
        for(int i=0; i<A.size(); i++) {
            for(int j=0; j<B[0].size(); j++) {
                for(int k=0; k<A[0].size(); k++) {
                    res[i][j] += (A[i][k]*B[k][j]) % mod;
                }
            }
        }
    }
    return res;
}

vector<vector<ll>> pwr(vector<vector<ll>> &A, ll N) {
    int n = A.size();
    vector<vector<ll>> res (n , vector<ll> (n));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n; j++) {
            if(i == j) res[i][j] = 1;
        }
    }
    while(N) {
        if(N % 2) res = multiply(res, A);
        A = multiply(A, A);
        N /= 2;
    }
    return res;
}
