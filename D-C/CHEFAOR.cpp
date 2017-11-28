/*input
4
3 2
1 2 2
4 3
1 2 3 4
2 2
1 2
11 4
66 152 7 89 42 28 222 69 10 54 99
*/
#include <bits/stdc++.h>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define N 5005
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
struct data {
	int l, r, L, R;
	data(int _l, int _r, int _L, int _R): l(_l), r(_r), L(_L), R(_R) {};
};
#define ll long long
int n, m;
vector<int> a;
ll dp[2][N];
stack<data> q;
int rmq[N][20];
int lg2[N];
 
void prep() {
	for (int i = 1; i <= n; i++) rmq[i][0] = a[i];
	for (int k = 1; k <= 20; k++) {
		for (int i = 1; i + (1 << k) - 1 <= n; i++) rmq[i][k] = rmq[i][k - 1] | rmq[i + (1 << (k - 1))][k - 1];
	}
}
 
void cal(int l, int r, int L, int R, const int c) {
	int mid = (l + r) / 2;
	int pos = -1;
	int x = min(mid, R);
	for (int i = L; i <= x; i++) {
		int val = (rmq[i][lg2[mid - i + 1]] | rmq[mid - (1 << lg2[mid - i + 1]) + 1][lg2[mid - i + 1]]);
		if (dp[c ^ 1][i - 1] + val > dp[c][mid]) {
			dp[c][mid] = dp[c ^ 1][i - 1] + val;
			pos = i;
		}
	}
	if (l <= mid - 1) cal(l, mid - 1, L, pos, c);
	if (mid + 1 <= r) cal(mid + 1, r, pos, R, c);
}
 
signed main() {
#ifdef in1code
	freopen("1test.inp", "r", stdin);
#endif
	for (int i = 1; i <= N - 5; i++) lg2[i] = log2(i);
	int T; scanf("%d", &T);
	while (T--) {
		a.clear(); for (int i = 0; i <= n; i++) dp[0][i] = dp[1][i] = 0;
		scanf("%d %d", &n, &m);
		a.push_back(-1e9);
		for (int i = 0; i < n; i++) {
			int t; cin >> t;
			a.push_back(t);
		}
		prep();
		for (int i = 1; i <= m; i++) {
			for (int j = 0; j <= n; j++) dp[i & 1][j] = 0;
			cal(1, n, 1, n, i & 1);
		}
		printf("%lld\n", dp[m & 1][n]);
	}
} 
