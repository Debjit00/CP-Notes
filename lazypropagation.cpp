// Author: Debjit Saha

#include <bits/stdc++.h>
using namespace std;
#define fastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define lld long double
// #define ll long long
#define endl '\n'
#define tab '\t'
#define all(a) a.begin(), a.end()
#define vi vector<int>
#define vp vector<pair<int, int>>
#define vvi vector<vector<int>>
#define vs vector<string>
#define vb vector<bool>
#define mii map<int, int>
#define rep(n) for(int i=0;i<n;i++)
#define REP(i, n) for(int i=0;i<n;i++)
#define trev(x) for(auto it=x.begin(); it!=x.end(); it++)
#define yes(check) cout << (check ? "YES\n" : "NO\n")
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) a*b/gcd(a,b)
const int mod=1e9+7;

int digit = 4, safe = 100, rndm;
set<string> ss, start;
string guess="";
void build() {
    for(int i=1; i<=pow(10, digit); i++) {
        string s, temp=to_string(i);if(temp.size()<digit) rep(digit-temp.size()) s+='0';
        s += temp; temp = s; sort(all(temp));
        ss.insert(s); rep(digit-1) if(temp[i]==temp[i+1]) {ss.erase(s); break;}}}

bool ok(string s, string key) {
    rep(digit) {
        if(key[i]<'A' and key[i]!=s[i]) return 0;
        else if(key[i]>='A' and (s.find((char)(key[i]-'A'+'0'))) < digit) return 0;
    }
    return 1;
}

void build2(string s, string num, int p, int d, int f, vs &poss, set<char> notTaken) {
    if(p==digit) {
        if(!d and !f) {
            rep(digit) if(s[i]=='X') {
                s[i] = 'A'-'0'+*notTaken.begin();
                notTaken.erase(notTaken.begin());
            }
            poss.push_back(s);
        }
        return;
    }
    if(d) {
        rep(digit) {
            if(i==p or s[i]!='X') continue;
            char c = s[i];
            s[i] = num[p];
            notTaken.erase(num[p]);
            build2(s, num, p+1, d-1, f, poss, notTaken);
            s[i] = c;
            notTaken.insert(num[p]);
        }
    }
    if(f and s[p]=='X') {
        char c = s[p];
        s[p] = num[p];
        notTaken.erase(num[p]);
        build2(s, num, p+1, d, f-1, poss, notTaken);
        s[p] = c;
        notTaken.insert(num[p]);
    }
    build2(s, num, p+1, d, f, poss, notTaken);
}

int value(string s, int d, int f, bool modify) {
    vs poss; 
    set<char> imp; 
    string X; rep(digit) X+="X";
    set<char> st; for(auto c: s) st.insert(c);
    build2(X, s, 0, d, f, poss, st);

    if(poss.size() and poss[0]==X)
        rep(digit) imp.insert(s[i]);

    int cnt = 0;
    vector<set<string>::iterator> itrs;
    trev(ss) {
        string str = *it;
        if(d+f<digit and str==s) {
            cnt++;
            if(modify) itrs.push_back(it); continue;
        }
        int check = 0;
        if(imp.size()) {
            rep(digit) if(imp.find(str[i]) != imp.end()) {
            check++; break;}if(check) {cnt++;if(modify) itrs.push_back(it); continue;}
        }
        for(auto key: poss) if(ok(str, key)) {check++; break;}
        if(!check) {cnt++; if(modify) itrs.push_back(it);}
    }
    if(modify) for(auto it: itrs) ss.erase(it);
    return cnt;
}

void calc() {
    string s="", num; getline(cin, s);
    while(s.size()) {
        int d=0, f=0;
        s = s.substr(3, s.size()-3);
        num = s.substr(0, 4);
        if(s[5] == 'n') ;
        else if(s[6] == 'f') f = s[5] - '0';
        else {
            d = s[5] - '0';
            if (s.size() == 10) f = s[8] - '0';
        }
        // cout << num << " " << d << " " << f << endl;
        value(num, d, f, 1);
        s = "";
        getline(cin, s);
    }
}

void calc2() {
    string num=""; cin >> num;
    while(num.size()) {
        int d, f;
        cin >> d >> f;
        value(num, d, f, 1);
        
        num = "";
        cin >> num;
    }
}

pair<int, int> find(string num, string guess) {
    int d=0, f=0; set<char> s;
    rep(digit) {s.insert(num[i]); if(num[i]==guess[i]) f++, d--;}
    for(auto c: guess) if(s.find(c) != s.end()) d++;
    return {d, f};}

void prob(string s) {
    cout << "PROBABILITY: " << s << endl;
    map<pair<int, int>, int> mpp;
    trev(ss) mpp[find(*it, s)]++; vvi res;
    trev(mpp) res.push_back({it->second, it->first.first, it->first.second});
    sort(all(res)); reverse(all(res)); for(auto v: res) {cout << v[1] << "d " << v[2] << "f = ";
    cout << fixed << setprecision(1) << v[0]*100.0/ss.size() << "%\t\t";
    cout << "Remaining " << v[0] << endl;}
    cout << "Size = " << ss.size() << "\n";
}

bool repeat(string n) {
    for(int i=1; i<4; i++)
        for(int j=0; j<i; j++)
            if (n[i] == n[j]) return true;
    return false;
}

vs findBestMoves() {
    int sz=ss.size(); int minDamage=1e8;
    vs res;
    map<pair<int, int>, int> mpp;
    if(ss.size()) 
        safe = 5040 * 2400 / ss.size();
    else return res;
    bool exist = false;
    trev(start) {
        string num = *it;
        if(digit == 4 and ss.size() > 1e3 and stoi(*it) > 2300)
            return res;
        if (digit==5 and safe--<=0) return res;
        mpp = {};
        int damage = 0;

        for(auto i=ss.begin(); i!=ss.end() and damage<=minDamage; i++)
            damage += 2*(++mpp[find(*i, num)])-1;
        if(damage < minDamage) {
            res={num};
            exist = (bool)(ss.find(num) != ss.end());
            minDamage = damage;
        }
        else if(minDamage == damage) {
            bool numExist = ss.find(num) != ss.end();
            if (!exist && numExist) {
                res = {num};
                exist = 1;
            }
            else if (exist == numExist)
                res.push_back(num);
        }
    }
    return res;
}

vs best(int n) {
    vs v = findBestMoves(), res;
    int sz = v.size();
    if(sz < n) {
        cout << sz << " Best moves" << endl;
        return v;
    }
    cout << "10 Best moves out of " << sz << endl;
    while(n--) 
        res.push_back(v[abs(rand()*rand())%sz]);
    return res;
}

int game() {
    ss = start;
    string num = to_string(abs(rand()*rand()) % (9876-123+1) + 123);
    if (num.size() == 3) num = "0" + num;
    int t = 100;
    while(repeat(num) and t--) {
        num = to_string(abs(rand()*rand()) % (9876-123+1) + 123);
        if (num.size() == 3) num = "0" + num;
    }
    if(repeat(num)) return 6;
    int round = 1;

    string guess = "1234";
    pair<int, int> feed = find(guess, num);
    if(feed.second == 4) return 1;

    value(guess, feed.first, feed.second, 1);
    while(round++ < 10) {
        if(ss.size() == 2) return round + rand()%2;
        if (ss.size() == 1) return round;
        guess = best(1)[0];
        feed = find(guess, num);
        if(feed.second == 4) return round;
        value(guess, feed.first, feed.second, 1);
    }
    return round;
}

void fresh();

signed main() {
    srand((int)(time(0)));
    build(); start = ss;
    // calc();
    // calc2();
    fresh();


    cout << "Sample size = " << ss.size() << endl;
    if(ss.size() <= 15) {
        trev(ss) cout << *it << " ";
        cout << endl;
    }
    vs nextMove = best(10);
    for(auto s: nextMove) cout << s << " ";
    return 0;
}

void fresh() {
    value("123", 1, 0, 1);
    value("214", 1, 0, 1);
    value("561", 0, 1, 1);
    value("081", 1, 1, 1);
    // value("87103", 2, 1, 1);
    // value("20186", 2, 1, 1);
    // value("76139", 3, 0, 1);
    // value("27891", 3, 2, 1);
    prob("701");
}
