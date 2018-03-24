#define int long long
struct ConvexHullTrick {
	vector<int> A, B;
	bool increasing_slope, need_tenary;
	int curit;
	// this code was set to find maximum value with increasing (or decreasing) slope
	// if you want to find minimum value, follow the guide and modify the code
	// initiate before using
	bool bad(int l1, int l2, int l3) {
		if (increasing_slope)
			return (B[l3] - B[l1]) * (A[l1] - A[l2]) > (A[l1] - A[l3]) * (B[l2] - B[l1]);
		return (B[l3] - B[l1]) * (A[l1] - A[l2]) < (A[l1] - A[l3]) * (B[l2] - B[l1]);
	}
	// if increasing_slope is false, then the lines' slope must be decreasing and vice versa
	// need_tenary should be set to true if the query value is not icreasing (or decreasing), otherwise set no false
	void init(bool _increasing_slope, bool _need_tenary) {
		increasing_slope = _increasing_slope; need_tenary = _need_tenary;
		A.clear(); B.clear(); curit = 0;
	}
	void add(int x, int y) {
		if (!A.empty()) {
			if (A.back() == x && B.back() <= y) A.pop_back(), B.pop_back(), curit--; // change to ">=" if you want to find min
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
			// change to ">=" if you want to find min
			return A[curit] * 1LL * x + B[curit];
		}
		int l = 0, r = (int)(A.size()) - 1;
		while (r - l > 2) {
			int mid1 = (l * 2 + r) / 3; int mid2 = (l + 2 * r) / 3;
			int val1 = A[mid1] * x + B[mid1]; int val2 = A[mid2] * x + B[mid2];
			if (val1 == val2)
				l = mid1, r = mid2;
			else if (val1 < val2)l = mid1; // change to ">" if you want to find min
			else r = mid2;
		}
		int ret = -1e18; // change to "1e18" if you want to find min
		for (int i = l; i <= r; i++)
			ret = max(ret, A[i] * x + B[i]); // change to "min" if you want to find min
		return ret;
	}
} cv;
