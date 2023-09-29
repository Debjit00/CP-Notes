int bs(vector<int> &a, int s, int e, int x) {
    while(s<=e) {
        int m=(s+e)/2;

        if (x==a[m]) return m;
        else if (x<a[m]) e=m-1;
        else s=m+1;
    }

    return -1;
}

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
