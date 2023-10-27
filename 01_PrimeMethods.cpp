Prime Methods:
bool isPrime(ll n) {
    if (n==2 || n==3) return true;
    if (n<2 || n%2==0 || n%3==0) return false;
    int factor=3;
    while (factor<=sqrt(n)+1) {
        if (n%factor==0) return false;
        factor++;
    }
    return true;
}

ll len=1e5;
vector<bool> prime(len+1, 1);
void primeSieve() {
    prime[0]=0, prime[1]=0;
    for (int p=2; p<sqrt(len); p++) {
        if (!prime[p]) continue;
        for (int i=p*p; i<len; i+=p) {
            if (prime[i]) prime[i]=false;
        }
    }
}
