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
    vi z(n);
    int left, right, k;
    left = right = 0;
    for (int i = 1; i < n; ++i) {
        if (i > right) {
            left = right = i;
            while (right<n && str[right-left] == str[right])
                right++;
            z[i] = right-left;
            right--;
        }
        else {
            k = i-left;
            if (z[k] < right-i+1)
                z[i] = z[k];
            else {
                left = i;
                while (right<n && str[right-left] == str[right])
                    right++;
                z[i] = right-left;
                right--;
            }
        }
    }
    return z;
}
