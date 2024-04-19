#include <cmath> // Include the cmath library for mathematical functions

// Function to extract the d-th digit of a floating-point number
int digit(double value, int d) {
    double mult = pow(10, -d - 1); // Calculate 10 to the power of (-d-1)
    value *= mult; // Scale the number to right position the digit of interest
    int dig = 10 * (value - floor(value)); // Extract the digit
    return dig; // Return the digit
}

// Function to sort an array of floating-point numbers using Radix Sort
void RadixSort(double* A, int start, int end, int d1, int d2) { // d1 <= d2 represents the decimal places ...,2,1,0,-1,-2,...
    int i, j, d;

    int N = end - start + 1; // Number of elements to sort
    int K = 9; // Maximum digit value

    double* B = new double[N]; // Temporary array for sorting
    int* C = new int[K+1]; // Count array for digits

    // Loop over each digit from d1 to d2-1
    for (d = d1; d < d2; d++) {
        for (i = 0; i <= K; i++) C[i] = 0; // Initialize count array
        for (j = start; j <= end; j++) C[digit(A[j], d)]++; // Count each digit occurrence
        for (i = 1; i <= K; i++) C[i] = C[i] + C[i - 1]; // Compute cumulative count
        for (j = end; j >= start; j--) B[--C[digit(A[j], d)]] = A[j]; // Place elements in temporary array
        for (j = start; j <= end; j++) A[j] = B[j - start]; // Copy back to the original array
    }

    delete[] B; // Free the memory allocated for the temporary array
    delete[] C; // Free the memory allocated for the count array
}
