#include <cmath>

// Function to merge two halves of an array
void Merge(int* vetor, int start, int pivot, int end) {
    int inf = INT_MAX; // Use maximum integer as a sentinel value
    int N1 = pivot - start + 1; // Calculate length of the first half
    int N2 = end - pivot; // Calculate length of the second half

    int* left = new int [N1 + 1]; // Allocate memory for the left sub-array plus one for sentinel
    int* right = new int[N2 + 1]; // Allocate memory for the right sub-array plus one for sentinel

    // Copy the elements to the left sub-array
    for (int i = 0; i < N1; i++) left[i] = vetor[start + i];
    // Copy the elements to the right sub-array
    for (int j = 0; j < N2; j++) right[j] = vetor[pivot + j + 1];

    // Place sentinels at the end of each sub-array
    left[N1] = inf;
    right[N2] = inf;

    int i = 0, j = 0; // Initialize indices for sub-arrays

    // Merge the sub-arrays back into the original array
    for (int k = start; k <= end; k++) {
        if (left[i] <= right[j]) // If left element is smaller or equal,
            vetor[k] = left[i++]; // take left element
        else // Otherwise,
            vetor[k] = right[j++]; // take right element
    }
    
    delete[] left; // Free the memory allocated for left sub-array
    delete[] right; // Free the memory allocated for right sub-array
}

// Recursive function to perform merge sort
void MergeSort(int* vetor, int start, int end) {
    if (start >= end) return; // Base case: if the range has less than two elements, return
    int pivot = (start + end) / 2; // Calculate the middle point

    MergeSort(vetor, start, pivot); // Recursively sort the first half
    MergeSort(vetor, pivot + 1, end); // Recursively sort the second half

    Merge(vetor, start, pivot, end); // Merge the sorted halves
}
