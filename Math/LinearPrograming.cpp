#include <bits/stdc++.h>
using namespace std;

/*
 * This is a simplex solver. Given m x n matrix A, m-vector b, n-vector c,
 * finds n-vector x such that Ax <= b (component-wise)
 * maximizing <c, x>
 * where <x, y> is the dot product of x and y.
 */
typedef long double T;
typedef vector<T> ROW;
typedef vector<ROW> MATRIX;
#define EPS 1e-9

inline int sign(T x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(T x, T y) {return sign(x - y);}
struct LPSolver {
    int m, n;
    vector<int> B, N;
    MATRIX D;
    LPSolver(const MATRIX &A, const ROW &b, const ROW &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, ROW(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void Pivot(int r, int s) {
        for (int i = 0; i < m + 2; i++) if (i != r) {
            for (int j = 0; j < n + 2; j++) if (j != s) {
                D[i][j] -= D[r][j] * D[i][s] / D[r][s];
            }
        }
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] /= D[r][s];
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] /= -D[r][s];
        D[r][s] = 1.0 / D[r][s];
        swap(B[r], N[s]);
    }
    int Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (1) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
            }
            if (sign(D[x][s]) >= 0) return 1;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (sign(D[i][s]) <= 0) continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] || D[i][n + 1] / D[i][s] == D[r][n + 1] / D[r][s] && B[i] < B[r]) r = i;
            }
            if (r == -1) return 0;
            Pivot(r, s);
        }
    }
    T Solve(ROW& x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (sign(D[r][n + 1]) < 0) {
            Pivot(r, n);
            if (!Simplex(1) || sign(D[m + 1][n + 1]) < 0) return -numeric_limits<T>::infinity();
            for (int i = 0; i < m; i++) if (B[i] == -1) {
                    int s = -1;
                    for (int j = 0; j <= n; j++) {
                        if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
                    }
                    Pivot(i, s);
                }
        }
        if (!Simplex(2)) return numeric_limits<T>::infinity();
        x = ROW(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};

int main() {
    int m = 4, n = 3;
    T _A[m][n] = {
        {6, -1, 0},
        {-1, -5, 0},
        {1, 5, 1},
        {-1, -5, -1}
    };
    T _b[m] = {10, -4, 5, -3};
    T _c[n] = {1, -1, 0};
    MATRIX A(m);
    ROW b(_b, _b + m);
    ROW c(_c, _c + n);
    for (int i = 0; i < m; i++) A[i] = ROW(_A[i], _A[i] + n);
    LPSolver solver(A, b, c);
    ROW x;
    T value = solver.Solve(x);
    cout << "Value: " << value << "\n";
    cout << "Solution:";
    for (size_t i = 0; i < x.size(); i++) cout << " " << x[i];
    cout << "\n";
    return 0;
}
