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
