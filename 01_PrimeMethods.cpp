Prime Methods:
bool isPrime(int n) {
    if (n==2 || n==3) return true;
    if (n<2 || n%2==0 || n%3==0) return false;
    int factor=3;
    while (factor<=sqrt(n)+1) {
        if (n%factor==0) return false;
        factor++;
    }
    return true;
}

int len=1e5;
vector<bool> prime(len+1, 1);
void build() {
    prime[0]=0, prime[1]=0;
    for (int primeFactors=2; primeFactors<sqrt(len); primeFactors++) {
        if (!prime[p]) continue;
        for (int i=p*p; i<=len; i+=p) {
            if (prime[i]) prime[i]=false;
        }
    }
}

// Prime factors
int len = 1e5;
vector<int> spf(len + 1, 1);
void sieve() {
    spf[0] = 0;
    for (int i = 2; i <= len; i++)
    if (spf[i] == 1)
    for (int j = i; j <= len; j += i)
    if (spf[j]== 1) spf[j] = i;
}
void helper(vector<int> &v, int n, int i, vector<int> &res) {
    if(i == v.size()) {
        res.push_back(n);
        return;
    }
    int val = n * v[i], j = i+1;
    while(j<v.size() && v[j-1] == v[j]) j++, val *= v[i];
    helper(v, n, i+1, res);
    helper(v, val, j, res);
}
vector<int> factors(int x) {
    vector<int> primeFactors, res;
    while (x != 1) {
        primeFactors.push_back(spf[x]);
        x = x / spf[x];
    }
    helper(primeFactors, 1, 0, res);
    return res;
}
