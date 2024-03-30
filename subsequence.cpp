#include <bits/stdc++.h>
using namespace std;

int LIS(vi &a) {
	vi dp;
	for(auto i: a) {
		auto it = upper_bound(all(dp), i);
		if(it==dp.end()) dp.push_back(i);
		else *it = i;
	}
	return dp.size();
}

void print(vector<int> &v) {
	if (v.size()==0) {
		cout << "{}" << endl;
		return;
	}
	cout << '{' << v[0];
	for (int i=1; i<v.size(); i++) cout << ", " << v[i]; cout << '}' << endl;
}

void power(int i, vector<int> &v, vector<int> &list) {
	if (i==v.size()) {
		print(list);
		return;
	}
	power(i+1, v, list);
	list.push_back(v[i]);
	power(i+1, v, list);
	list.pop_back();
}

void subSum(int i, int sum, int target, vector<int> &v, vector<int> &list) {
	if (sum==target) {
		print(list);
		return;
	}
	if (i==v.size()) return;

	sum+=v[i];
	list.push_back(v[i]);
	subSum(i+1, sum, target, v, list);
	list.pop_back();
	sum-=v[i];
	subSum(i+1, sum, target, v, list);
}

int subSumCnt(int i, int sum, int target, vector<int> &v) {
	if (sum==target) return 1;
	if (i==v.size()) return 0;

	int take = subSumCnt(i+1, sum+v[i], target, v);
	int notTake = subSumCnt(i+1, sum, target, v);

	return take+notTake;
}

int main() {
	vector<int> v = {1, 2, 3, 4, 5, 6}, list;
	for (int i=0; i<=21; i++) {
		cout << i << "-> ";
		// subSum(0, 0, i, v, list);
		cout << subSumCnt(0, 0, i, v);
		cout << endl;
	}
	return 0;
}
