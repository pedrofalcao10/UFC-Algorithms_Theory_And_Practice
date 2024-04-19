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
            i--; // Move to the previous element
        }

        // Insert 'carta' in its correct position in the sorted portion
        vetor[i+1] = carta;
    }
}
