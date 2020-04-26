// Tested: NKLEAVES
// Tested: http://codeforces.com/contest/678/problem/F
struct Line {
    int A, B;
    Line(int _A, int _B): A(_A), B(_B) {};
    int cal(int x) {return A * x + B;}
};
// status: find min_value with monotoic slope.
// find max -> flip all with tag
// not monotoic slope -> Tenary search
// !!! INIT before use. Use with #define int long long
const int INF = 2e18;
struct ConvexHullTrick {
    vector<Line> f; bool inc;
    bool bad(int l1, int l2, int l3) {
        if (inc)
            // flip
            return (f[l3].B - f[l1].B) * (f[l1].A - f[l2].A) > (f[l1].A - f[l3].A) * (f[l2].B - f[l1].B);
        // flip
        return (f[l3].B - f[l1].B) * (f[l1].A - f[l2].A) < (f[l1].A - f[l3].A) * (f[l2].B - f[l1].B);
    }
    void init(bool _inc) {inc = _inc; f = vector<Line>();}
    void add(Line nxt) {
        // flip
        if (!f.empty() && f.back().A == nxt.A && f.back().B >= nxt.B)
            f.pop_back();
        f.push_back(nxt);
        while (f.size() > 2 && bad(f.size() - 3, f.size() - 2, f.size() - 1))
            f.erase(f.end() - 2);
    }
    int iter = 0;
    int query(int x) {
        assert(!f.empty());
        // !!! NO TENARY SEARCH
        iter = min(iter, (int)f.size() - 1);
        while (iter != f.size() - 1 && f[iter].cal(x) >= f[iter + 1].cal(x)) iter++; // flip
        return f[iter].cal(x);

        /// !!! TENARY SEARCH
        int l = 0, r = (int)(f.size()) - 1;
        while (r - l > 2) {
            int mid1 = (l * 2 + r) / 3; int mid2 = (l + 2 * r) / 3;
            int val1 = f[mid1].cal(x); int val2 = f[mid2].cal(x);
            if (val1 == val2)l = mid1, r = mid2;
            else if (val1 > val2)l = mid1; // flip
            else r = mid2;
        }
        int ret = INF; // flip
        for (int i = l; i <= r; i++)ret = min(ret, f[i].cal(x)); // flip
        return ret;
    }
} CV;
