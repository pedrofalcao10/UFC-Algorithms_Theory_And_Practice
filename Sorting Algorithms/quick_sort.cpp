#include <cmath>
#include <ctime>

// Function to swap two integers using pass-by-reference
void swap(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}

// Function to partition the array using the last element as the pivot
int Particioning_original(int* vetor, int start, int end) {
    int pivo = vetor[end]; // Choose the last element as the pivot
    int i = start - 1; // Initialize i to one less than the start index

    // Loop to re-arrange the array elements based on the pivot
    for (int j = start; j < end; j++) {
        if (vetor[j] <= pivo) { // If current element is less than or equal to pivot
            i++; // Move the boundary of smaller element
            swap(vetor[i], vetor[j]); // Swap to place the smaller element before the pivot
        }
    }

    swap(vetor[i+1], vetor[end]); // Place the pivot after the last smaller element

    return i+1; // Return the position of the pivot
}

// Function to choose a random pivot and partition the array
int Particione_random(int* vetor, int start, int end) {
    srand(time(NULL)); // Seed the random number generator

    int pos_pivot = start + rand() % (end - start + 1); // Choose a random pivot index
    
    swap(vetor[pos_pivot], vetor[end]); // Swap the pivot with the last element
    
    return Particioning_original(vetor, start, end); // Partition using the original partitioning function
}

// Recursive QuickSort function
void QuickSort(int* vetor, int start, int end) {
    if (start >= end) return; // Base case: if the range has less than two elements, return

    int pivot = Particioning_original(vetor, start, end); // Partition the array and get pivot index

    QuickSort(vetor, start, pivot - 1); // Recursively apply QuickSort to the left subarray
    QuickSort(vetor, pivot + 1, end); // Recursively apply QuickSort to the right subarray
}
