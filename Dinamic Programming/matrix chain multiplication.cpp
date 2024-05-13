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