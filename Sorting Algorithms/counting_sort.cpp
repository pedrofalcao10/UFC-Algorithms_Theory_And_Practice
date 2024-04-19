// Function to perform Counting Sort on an array of doubles
void CountingSort(double* A, int N, int K) {
    int i, j;
    double* B = new double[N]; // Temporary array B to hold the sorted output
    int* C = new int[K+1];     // Temporary array C to store the count of each key

    // Initialize count array C to 0
    for (i = 0; i <= K; i++) C[i] = 0;

    // Count each element in A and increment the corresponding index in C
    for (j = 0; j < N; j++) C[(int)A[j]]++;

    // Modify C such that each element at each index stores the sum of previous counts
    // This modification makes C contain actual positions of elements in array B
    for (i = 1; i <= K; i++) C[i] = C[i] + C[i - 1];

    // Build the output array B by placing elements in their correct position
    // and decreasing the count by one
    for (j = N - 1; j >= 0; j--) {
        B[--C[(int)A[j]]] = A[j]; // Place element A[j] at its correct position in B
    }

    // Copy the sorted elements back to array A
    for (j = 0; j < N; j++) A[j] = B[j];

    // Free up memory allocated for temporary arrays B and C
    delete[] B;
    delete[] C;
}
