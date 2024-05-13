#include <iostream>
using namespace std;

unsigned int MCM(int* p, int N, int**& R) {
    int** m = new int*[N]; for (int i = 0; i < N; i++) m[i] = new int[N];
    if (R == NULL) {R = new int*[N]; for (int i = 0; i < N; i++) R[i] = new int[N];}

    for (int i = 0; i < N; i++) m[i][i] = 0;

    for (int l = 2; l <= N; l++) {
        for (int i = 0; i < N-l+1; i++) {
            int j = i+l-1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    R[i][j] = k;
                }
            }
        }
    }

    print_matrix(m, N);
    cout << "\n";

    int r = m[0][N-1];

    for (int i = 0; i < N; i++) delete[] m[i];
    delete[] m;

    return r;
}

void print_parent(int i, int j, int** R) {
    if (i == j) {cout << i+1; return;}

    cout << "(";
    print_parent(i, R[i][j], R);
    cout << "*";
    print_parent(R[i][j]+1, j, R);
    cout << ")";
}

void print_matrix(int** m, int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++) cout << "- ";
        for (j = i; j < N; j++) cout << m[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    int** R = NULL;

    // 1st book example
    int N1 = 3;
    int p1[4] = {10, 100, 5, 50};
    int result1 = MCM(p1, N1, R);
    cout << "Number of scalar multiplications = " << result1 << "\n\n";

    print_parent(0, N1-1, R);
    cout << "\n\n\n\n";
    if (R != NULL) {for (int i = 0; i < N1; i++) delete[] R[i]; delete[] R; R = NULL;}

    // 2nd book example
    int N2 = 6;
    int p2[7] = {30, 35, 15, 5, 10, 20, 25};
    int result2 = MCM(p2, N2, R);
    cout << "Number of scalar multiplications = " << result2 << "\n\n";

    print_parent(0, N2-1, R);
    cout << "\n\n\n\n";
    if (R != NULL) {for (int i = 0; i < N2; i++) delete[] R[i]; delete[] R; R = NULL;}

    return 0;
}