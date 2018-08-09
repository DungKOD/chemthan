#include <bits/stdc++.h>
using namespace std;

/*
* Complexity: O(N^3)
*/
typedef double T;
#define EPS 1e-9
typedef vector<T> ROW;
typedef vector<ROW> MATRIX;

inline int sign(T x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(T x, T y) {return sign(x - y);}
T MatrixDeterminant(MATRIX a, ROW& r) {
    int i, j, k, n = a.size(), m = a[0].size();
    T res = 1;
    for (i = 0; i < n; i++) {
        if (!sign(a[i][i])) {
            for (j = i + 1; j < n; j++) {
                if (sign(a[j][i])) {
                    for (k = 0; k < m; k++) a[i][k] += a[j][k];
                    break;
                }
            }
            if (j == n) return 0;
        }
        T tmp = a[i][i];
        for (k = 0; k < m; k++) a[i][k] /= tmp;
        res *= tmp;
        for (j = 0; j < n; j++) {
            if (j == i) continue;
            tmp = a[j][i];
            for (k = 0; k < m; k++) a[j][k] -= a[i][k] * tmp;
        }
    }
    r.clear();
    for (int i = 0; i < n; i++) {
        r.push_back(a[i][n]);
    }
    return res;
}

int main() {
    srand(time(NULL));
    int n = 5;
    MATRIX a(n, ROW(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            a[i][j] = rand() % 10;
        }
    }
    ROW r;
    T det = MatrixDeterminant(a, r);
    for (int i = 0; i < n; i++) {
        T t = 0;
        for (int j = 0; j < n; j++) {
            t += a[i][j] * r[j];
        }
        if (sign(t - a[i][n])) {
            cout << "Wrong!\n";
            return 0;
        }
    }
    cout << fixed << setprecision(9) << "Determinant: " << det << "\n";;
    cout << "Solution: ";
    for (int i = 0; i < n; i++) {
        cout << r[i] << " ";
    }
    cout << "\n";
    return 0;
}
