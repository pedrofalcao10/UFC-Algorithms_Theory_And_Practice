void InsertionSort(int* vetor, int p, int r){
    int i, j, carta;

    // Outer loop: Start from the second element in the specified range (index p + 1)
    for(j = p+1; j <= r; j++){
        carta = vetor[j]; // 'carta' holds the current element to be sorted into the sorted portion
        
        // Start comparing 'carta' with elements in the sorted portion, moving from right to left
        i = j-1; // Initialize i to point to the last element of the sorted portion

        // Inner loop: Keep moving elements one position to the right until the correct position for 'carta' is found
        while((i >= p) && (vetor[i] > carta)){
            vetor[i+1] = vetor[i]; // Shift elements to the right
            i--;                   // Move to the previous element
        }

        // Insert 'carta' in its correct position in the sorted portion
        vetor[i+1] = carta;
    }
}

// Function to swap two integers using pass-by-reference
void swap(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}

// Function to reorder elements in an array around a pivot value
int Partitioning(int* vetor, int start, int end, int pivot) {
    int j, i = start - 1; // Initialize i to one less than the start index

    // First loop: move elements less than the pivot to the left part of the array
    for (j = start; j < end; j++) {
        if (vetor[j] < pivot) {       // If current element is less than the pivot
            i++;                      // Increment i to point to the next position
            swap(vetor[i], vetor[j]); // Swap to position the smaller element on the left side
        } 
        else if (vetor[j] == pivot) {   // If current element is the pivot
            swap(vetor[j], vetor[end]); // Swap the pivot with the last element
            break;                      // Exit the loop as the pivot is moved to the end
        }
    }

    // Second loop: move elements equal to or less than the pivot next to the smaller elements
    for (j = j; j < end; j++) {       // Continue from where the first loop left off
        if (vetor[j] <= pivot) {      // If the current element is less than or equal to the pivot
            i++;                      // Increment i
            swap(vetor[i], vetor[j]); // Swap to continue positioning smaller or equal elements on the left
        }
    }

    // Finally, swap the pivot into its correct position right after all smaller or equal elements
    swap(vetor[i+1], vetor[end]);

    return i + 1; // Return the position of the pivot after partitioning
}

// Function to select the k-th smallest element from a subarray A[start...end]
int Selection(int* A, int start, int end, int k) {
    int i, N = end - start + 1; // Calculate the number of elements in the subarray

    // If the subarray is small (less than 10 elements), use insertion sort and return the k-th element
    if (N < 10) {
        if (k > N) k = N; // Adjust k if it's greater than the number of elements
        InsertionSort(A, start, end); // Sort the small subarray
        return A[start + k - 1]; // Return the k-th smallest element
    }

    // Divide the array into subarrays of 5 elements each and find the median of each subarray
    int len_M = N / 5; // Calculate how many groups of 5 can be made
    int* M = new int[len_M]; // Array to hold the medians of each group

    for (i = 0; i < len_M; i++) {
        InsertionSort(A, start + 5 * i, start + 5 * i + 4); // Sort each group of 5
        M[i] = A[start + 5 * i + 2];                        // Pick the median (middle element) of each sorted group
    }

    // Recursively find the median of the medians to use as a good pivot
    int pivo = Selection(M, 0, len_M - 1, len_M / 2); 
    delete[] M; // Free the memory used for storing medians

    // Partition the array around the median of medians
    int q = Partitioning(A, start, end, pivo);
    i = q - start + 1; // Calculate the rank of the pivot in the sorted order

    
    if (k == i) return A[q];                       // If the pivot's rank matches k, return the pivot
    if (k < i) return Selection(A, start, q - 1, k); // If k is less than the rank of the pivot, recursively search in the left subarray
    
    return Selection(A, q + 1, end, k - i);          // Otherwise, search in the right subarray

}
