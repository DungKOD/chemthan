#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: build O(NlogN), query O(1)
*/
template<class T, class cmp = less<T> > struct RMQ {
    int n;
    vector<T> a;
    vector<vector<T> > f;

    T best(T a, T b) {
        if (cmp()(a, b)) return a;
        return b;
    }
    void init(int n) {
        this->n = n;
        int p = 1; while ((1 << p) < n) p++;
        a.resize(n), f.resize(p + 1);
        for (int i = 0; i < (int) f.size(); i++) {
            f[i].resize(n);
        }
    }
    void upd(int u, T x) {
        a[u] = x;
    }
    void build() {
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int l = 0, k; (k = 1 << l) < n; l++) {
            for (int i = 0; i + k < n; i++) {
                f[l + 1][i] = best(f[l][i], f[l][i + k]);
            }
        }
    }
    T query(int a, int b) {
        int l = a == b ? 0 : __lg(b - a);
        return best(f[l][a], f[l][b - (1 << l) + 1]);
    }
};
RMQ<int> rmq;

int main() {
    srand(time(NULL));
    for (int it = 0; it < 2; it++) {
        rmq.init(rand() % 100000 + 1);
        for (int i = 0; i < rmq.n; i++) {
            rmq.upd(i, rand());
        }
        rmq.build();
        for (int test = 0; test < 1000; test++) {
            int l = rand() % rmq.n, r = rand() % rmq.n;
            if (l > r) swap(l, r);
            int res = (int) 1e9;
            for (int i = l; i <= r; i++) {
                res = min(res, rmq.a[i]);
            }
            assert(rmq.query(l, r) == res);
        }
    }
    cout << "Correct!\n";
    return 0;
}
