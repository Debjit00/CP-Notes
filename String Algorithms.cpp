vi buildLPS(string str) {
    int n = str.size();
    vi lps(n);
    int len = 0, i = 1;
    while (i < n) {
        if (str[i] == str[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else if (len != 0) len = lps[len - 1];
        else {
            lps[i] = 0;
            i++;
        }
    }
    return lps;
}

vi buildZ(string str) {
    int n = str.size();
    vi Z(n);
    int L, R, k;
    L = R = 0;
    for (int i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;
            while (R<n && str[R-L] == str[R])
                R++;
            Z[i] = R-L;
            R--;
        }
        else {
            k = i-L;
            if (Z[k] < R-i+1)
                Z[i] = Z[k];
            else {
                L = i;
                while (R<n && str[R-L] == str[R])
                    R++;
                Z[i] = R-L;
                R--;
            }
        }
    }
    return Z;
}
