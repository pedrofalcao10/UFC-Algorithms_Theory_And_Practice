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

    int r = m[0][N-1];

    for (int i = 0; i < N; i++) delete[] m[i];
    delete[] m;

    return r;
}