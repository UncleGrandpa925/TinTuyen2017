/*input
4
100 1
15 15
20 5
1 100
*/
#include <bits/stdc++.h>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define int long long
#define N 50005
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
 
struct ConvexHullTrick {
	vector<int> A, B;
	bool increasing_slope, need_tenary;
	bool bad(int l1, int l2, int l3) {
		if (increasing_slope)
			return (B[l3] - B[l1]) * (A[l1] - A[l2]) < (A[l1] - A[l3]) * (B[l2] - B[l1]);
		return (B[l3] - B[l1]) * (A[l1] - A[l2]) > (A[l1] - A[l3]) * (B[l2] - B[l1]);
	}
	void init(bool _increasing_slope, bool _need_tenary) {
		increasing_slope = _increasing_slope; need_tenary = _need_tenary;
		A.clear(); B.clear();
	}
	void add(int x, int y) {
		if (!A.empty()) {
			if (A.back() == x && B.back() >= y) A.pop_back(), B.pop_back();
		}
		A.push_back(x);
		B.push_back(y);
		while (A.size() > 2 && bad(A.size() - 3, A.size() - 2, A.size() - 1)) {
			A.erase(A.end() - 2);
			B.erase(B.end() - 2);
		}
	}
	int curit = 0;
	int query(int x) {
		if (!need_tenary) {
			curit = min(curit, (int)A.size() - 1);
			while (curit != A.size() - 1 && A[curit] * 1LL * x + B[curit] >= A[curit + 1] * 1LL * x + B[curit + 1]) curit++;
			return A[curit] * 1LL * x + B[curit];
		}
		int l = 0, r = (int)(A.size()) - 1;
		while (r - l > 2) {
			int mid1 = (l * 2 + r) / 3; int mid2 = (l + 2 * r) / 3;
			int val1 = A[mid1] * x + B[mid1]; int val2 = A[mid2] * x + B[mid2];
			if (val1 == val2)
				l = mid1, r = mid2;
			else if (val1 > val2)l = mid1;
			else r = mid2;
		}
		int ret = 1e18;
		for (int i = l; i <= r; i++)
			ret = min(ret, A[i] * x + B[i]);
		return ret;
	}
} CV;
 
int n;
vector<pair<int, int> > a;
vector<pair<int, int> > b;
int dp[N];
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		a.push_back(mp(x, y));
	}
	sort(a.begin(), a.end());
	b.push_back(a.front());
	for (int i = 1; i < a.size(); i++) {
		while (!b.empty() && b.back().se <= a[i].se) b.pop_back();
		b.push_back(a[i]);
	}
	CV.init(1, 0);
	CV.add(b[0].se, 0);
	for (int i = 1; i <= b.size(); i++) {
		int W = b[i - 1].fi;
		dp[i] = CV.query(W);
		if (i != b.size()) {
			CV.add(b[i].se, dp[i]);
		}
	}
	cout << dp[b.size()] << endl;
} 
