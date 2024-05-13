#include <iostream>
using namespace std;

// MCM function calculates the minimum number of scalar multiplications needed to multiply a sequence of matrices.
// p: array of dimensions of matrices such that dimension of ith matrix is p[i-1] x p[i]
// N: total number of matrices
// R: matrix to store the index of the matrix split that minimizes the number of multiplications

unsigned int MCM(int* p, int N, int**& R) {
    // Initialize the matrix m to store the minimum multiplication costs
    int** m = new int*[N]; for (int i = 0; i < N; i++) {m[i] = new int[N];}

    // If R is null, initialize it
    if (R == NULL) {R = new int*[N]; for (int i = 0; i < N; i++) {R[i] = new int[N];}}

    // Set diagonal of m to 0 as multiplying one matrix costs nothing
    for (int i = 0; i < N; i++) {m[i][i] = 0;}

    // l is the chain length
    for (int l = 2; l <= N; l++) {
        for (int i = 0; i < N-l+1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX; // Initialize to a large value
            for (int k = i; k < j; k++) {
                // Calculate cost of multiplying matrices from i to j with split at k
                int q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
                if (q < m[i][j]) {
                    m[i][j] = q; // Store the minimum cost
                    R[i][j] = k; // Store the split point
                }
            }
        }
    }

    // Print the cost matrix
    print_matrix(m, N);
    cout << "\n";

    int r = m[0][N-1]; // Minimum cost for the full matrix chain

    // Clean up memory used by m
    for (int i = 0; i < N; i++) {delete[] m[i];} delete[] m;

    return r; // Return the minimum cost
}

// Recursive function to print the optimal parenthesization of matrix multiplication
void print_parent(int i, int j, int** R) {
    if (i == j) {
        cout << i+1; // Base case: single matrix
        return;
    }

    cout << "(";
    print_parent(i, R[i][j], R); // Print left side of multiplication
    cout << "*";
    print_parent(R[i][j]+1, j, R); // Print right side of multiplication
    cout << ")";
}

// Helper function to print a matrix
void print_matrix(int** m, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) cout << "- ";
        for (int j = i; j < N; j++) cout << m[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    int** R = NULL; // Pointer to store the split indices matrix

    // Example 1: 3 matrices of dimensions 10x100, 100x5, 5x50
    int N1 = 3;
    int p1[4] = {10, 100, 5, 50}; // Array of dimensions
    int result1 = MCM(p1, N1, R); // Compute MCM
    cout << "Number of scalar multiplications = " << result1 << "\n\n";

    print_parent(0, N1-1, R); // Print optimal parenthesization
    cout << "\n\n\n\n";
    // Clean up memory used by R
    if (R != NULL) {for (int i = 0; i < N1; i++) delete[] R[i]; delete[] R; R = NULL;}

    // Repeat for another example with 6 matrices
    int N2 = 6;
    int p2[7] = {30, 35, 15, 5, 10, 20, 25};
    int result2 = MCM(p2, N2, R);
    cout << "Number of scalar multiplications = " << result2 << "\n\n";
    
    print_parent(0, N2-1, R);
    cout << "\n\n\n\n";
    // Clean up memory used by R
    if (R != NULL) {for (int i = 0; i < N2; i++) delete[] R[i]; delete[] R; R = NULL;}
}