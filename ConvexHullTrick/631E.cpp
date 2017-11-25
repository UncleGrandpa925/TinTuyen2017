/*input
4
87 213 141 1

*/
#include <bits/stdc++.h>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair

#define N 200005
#define bit(x,y) ((x>>y)&1LL)
#define na(x) (#x) << ":" << x
ostream& operator << (ostream &os, vector<int>&x) {
	for (int i = 0; i < x.size(); i++) os << x[i] << sp;
	return os;
}
ostream& operator << (ostream &os, pair<int, int> x) {
	cout << x.fi << sp << x.se << sp;
	return os;
}
ostream& operator << (ostream &os, vector<pair<int, int> >&x) {
	for (int i = 0; i < x.size(); i++) os << x[i] << endl;
	return os;
}
#define int long long
struct ConvexHullTrick {
	vector<int> A, B;
	bool increasing_slope, need_tenary;
	int curit;
	bool bad(int l1, int l2, int l3) {
		if (increasing_slope)
			return (B[l3] - B[l1]) * (A[l1] - A[l2]) < (A[l1] - A[l3]) * (B[l2] - B[l1]);
		return (B[l3] - B[l1]) * (A[l1] - A[l2]) > (A[l1] - A[l3]) * (B[l2] - B[l1]);
	}
	void init(bool _increasing_slope, bool _need_tenary) {
		increasing_slope = _increasing_slope; need_tenary = _need_tenary;
		A.clear(); B.clear(); curit = 0;
	}
	void add(int x, int y) {
		if (!A.empty()) {
			if (A.back() == x && B.back() <= y) A.pop_back(), B.pop_back(), curit--;
		}
		A.push_back(x);
		B.push_back(y);
		while (A.size() > 2 && bad(A.size() - 3, A.size() - 2, A.size() - 1)) {
			A.erase(A.end() - 2);
			B.erase(B.end() - 2);
			curit--;
		}
	}
	int query(int x) {
		if (!need_tenary) {
			if (curit < 0) curit = 0;
			while (curit != A.size() - 1 && A[curit] * 1LL * x + B[curit] <= A[curit + 1] * 1LL * x + B[curit + 1]) curit++;
			return A[curit] * 1LL * x + B[curit];
		}
		int l = 0, r = (int)(A.size()) - 1;
		while (r - l > 2) {
			int mid1 = (l * 2 + r) / 3; int mid2 = (l + 2 * r) / 3;
			int val1 = A[mid1] * x + B[mid1]; int val2 = A[mid2] * x + B[mid2];
			if (val1 == val2)
				l = mid1, r = mid2;
			else if (val1 < val2)l = mid1;
			else r = mid2;
		}
		int ret = -1e18;
		for (int i = l; i <= r; i++)
			ret = max(ret, A[i] * x + B[i]);
		return ret;
	}
} cv;

int n;
int a[N];
int simpleSum[N];
int complexSum[N];

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		simpleSum[i] = simpleSum[i - 1] + a[i];
		complexSum[i] = complexSum[i - 1] + a[i] * i;
	}
	cv.init(0, 1);
	int ans = complexSum[n];
	for (int j = n; j >= 1; j--) {
		ans = max(ans, complexSum[n] + simpleSum[j] - a[j] * j + cv.query(a[j]));
		cv.add(j, -simpleSum[j]);
	}
	cv.init(1, 1);
	for (int j = 1; j <= n; j++) {
		ans = max(ans, complexSum[n] + simpleSum[j - 1] - a[j] * j + cv.query(a[j]));
		cv.add(j, -simpleSum[j - 1]);
	}
	cout << ans << endl;
}
