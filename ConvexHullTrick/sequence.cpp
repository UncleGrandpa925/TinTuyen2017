/*input
6 2
4 6 3 0 1 4 6
*/
#include <bits/stdc++.h>
using namespace std;
#define sp ' '
#define endl '\n'
#define fi first
#define se second
#define mp make_pair
#define N 100005
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
#define ll long long
vector<ll> A, B, C;
 
bool bad(int l1, int l2, int l3) {
	return (B[l3] - B[l1]) * (A[l1] - A[l2]) < (A[l1] - A[l3]) * (B[l2] - B[l1]) ;
}
void add(ll x, ll y, int z) {
	if (!A.empty()) {
		if (A.back() == x && B.back() == y) {
			C[A.size() - 1] = z;
			return;
		}
	}
	A.push_back(x);
	B.push_back(y);
	C.push_back(z);
	while (A.size() > 2 && bad(A.size() - 3, A.size() - 2, A.size() - 1)) {
		A.erase(A.begin() + A.size() - 2);
		B.erase(B.begin() + B.size() - 2);
		C.erase(C.begin() + C.size() - 2);
	}
}
 
int curit = 0;
pair<ll, int> query(int x) {
	if (A.empty()) return mp(0, 0);
	curit = min(curit, (int)A.size() - 1);
	while (curit != A.size() - 1 && A[curit] * 1LL * x + B[curit] <= A[curit + 1] * 1LL * x + B[curit + 1]) curit++;
	return mp(A[curit] * 1LL * x + B[curit], C[curit]);
}
 
int n, m;
int a[N];
ll sum[N];
ll dp[N][2];
int par[N][205];
vector<int> order;
 
signed main() {
#ifdef UncleGrandpa
	freopen("1test.inp", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; i++) dp[i][0] = 0;
	for (int p = 1; p <= m; p++) {
		int c = p & 1;
		for (int i = 0; i < N; i++) dp[i][c] = 0;
		A.clear(); B.clear(); C.clear();
		for (int i = 1; i <= n; i++) {
			pair<ll, int> rec = query(sum[i]);
			dp[i][c] = rec.fi;
			par[i][p] = rec.se;
			// if (i == 3 && p == 2) {
			// 	cout << A.size() << endl;
			// 	for (int i = 0; i < A.size(); i++) cout << A[i] << sp << B[i] << sp << C[i] << endl;
			// 	cout << rec.se << endl;
			// }
			add(sum[i], dp[i][c ^ 1] - sum[i]*sum[i], i);
		}
	}
	printf("%lld\n", dp[n][m & 1]);
	pair<int, int> cur = mp(n, m);
	while (cur.se >= 1) {
		order.push_back(par[cur.fi][cur.se]);
		cur.fi = par[cur.fi][cur.se]; cur.se--;
	}
	reverse(order.begin(), order.end());
	for (int i = 0; i < order.size(); i++) printf("%d ", order[i]);
	// // cout << 1.0 * clock() / CLOCKS_PER_SEC << endl;
}
