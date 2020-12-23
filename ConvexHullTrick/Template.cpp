// updated 14/12/2020
// Tested: NKLEAVES
// Tested: http://codeforces.com/contest/678/problem/F
struct Line {
    int A, B;
    Line(int _A, int _B): A(_A), B(_B) {};
    int cal(int x) {return A * x + B;}
};

/**
 * find min_value with monotoic slope in O(1)
 * not monotoic slope -> use LineContainer.h
 * find max -> flip all with tag
 * Use with #define int long long
*/
class ConvexHullTrick {
    vector<Line> f; bool inc;
    int iter = 0;
    bool isBad(int l1, int l2, int l3) {
        auto comp = [ = ](int X, int Y) {
            return inc ? X > Y : X < Y; // flip both signs
        };
        return comp((f[l3].B - f[l1].B) * (f[l1].A - f[l2].A), (f[l1].A - f[l3].A) * (f[l2].B - f[l1].B));
    }

public:
    ConvexHullTrick(bool inc): inc(inc) {};
    ConvexHullTrick() = default;
    void add(Line nxt) {
        if (!f.empty() && f.back().A == nxt.A && f.back().B >= nxt.B) // flip
            f.pop_back();
        f.push_back(nxt);
        while (f.size() > 2 && isBad(f.size() - 3, f.size() - 2, f.size() - 1))
            f.erase(f.end() - 2);
    }
    int query(int x) {
        assert(!f.empty());
        iter = min(iter, (int)f.size() - 1);
        while (iter != f.size() - 1 && f[iter].cal(x) >= f[iter + 1].cal(x)) iter++; // flip
        return f[iter].cal(x);
    }
} CV;
