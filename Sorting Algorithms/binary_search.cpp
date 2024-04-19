// Function to perform binary search on a SORTED array
int BinarySearch(int* vetor, int elemento, int start, int end){
    // Continue searching while the subrange has not been reduced to zero
    while(start <= end){
        int pivot = (start + end) / 2; // Calculate the middle index of the current subrange

        if (vetor[pivot] < elemento) start = pivot + 1; else // If the target is greater than the middle element, search in the right half
        if (vetor[pivot] > elemento)   end = pivot - 1; else // If the target is less than the middle element, search in the left half
        if (vetor[pivot] == elemento) return pivot;          // If the middle element is the target, return its index
    }

    return -1; // If the target is not found, return -1
}

// Recursive binary search function
int BinarySearchRec(int* vetor, int elemento, int start, int end) {
    // Base case: if the start index exceeds the end index, the element is not found
    if (start > end) return -1;

    // Calculate the middle index of the current segment
    int pivot = (start + end) / 2;

    // If the target element is less than the element at the middle index,
    // recursively search in the left sub-array
    if (elemento < vetor[pivot]) return BinarySearchRec(vetor, elemento, start, pivot - 1);

    // If the target element is greater than the element at the middle index,
    // recursively search in the right sub-array
    if (elemento > vetor[pivot]) return BinarySearchRec(vetor, elemento, pivot + 1, end);

    // If the element at the middle index is equal to the target element, return the index
    return pivot;
}