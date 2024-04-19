// Function to swap two integers using pass-by-reference
void swap(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}

// Helper function to maintain the max heap property
void maxHeapify(int* vetor, int i, int p, int r){
    int m = i;  // Start with the current index as the largest
    int left = p + 2*(i-p) + 1;  // Calculate the left child index
    int right = p + 2*(i-p) + 2;  // Calculate the right child index

    // If the left child exists and is greater than current element, update largest
    if((left <= r) && (vetor[left] > vetor[i])) m = left;

    // If the right child exists and is greater than current largest element, update largest
    if((right <= r) && (vetor[right] > vetor[m])) m = right;

    // If the largest is not the current element, swap and continue heapifying
    if(m != i) {
        swap(vetor[i], vetor[m]);
        maxHeapify(vetor, m, p, r);
    }
}

// Function to perform heap sort
void HeapSort_max(int* vetor, int p, int r){
    int i;

    // Build a max heap from the array or sub-array
    for(i = (r+p-1)/2; i >= p; i--)
        maxHeapify(vetor, i, p, r);

    // Extract elements one by one from the heap
    for(i = r; i > p; i--){
        swap(vetor[p], vetor[i]);  // Move current root to end
        r--;  // Reduce the heap size by one
        maxHeapify(vetor, p, p, r);  // Heapify the reduced heap
    }
}

// Function to maintain the min-heap property
void min_heapify(int* vetor, int i, int start, int end) {
    int m = i; // Initialize m to the current node
    int left = 2*i - end - 1; // Calculate left child index (incorrectly calculated)
    int right = left - 1; // Calculate right child index (incorrectly calculated)

    // Check if left child is within bounds and smaller than current node
    if ((left >= start) && (vetor[left] < vetor[i])) m = left;
    // Check if right child is within bounds and smaller than the new minimum
    if ((right >= start) && (vetor[right] < vetor[m])) m = right;

    // If the smallest value is not the current node, swap and heapify down
    if (m != i) {
        swap(vetor[i], vetor[m]);
        min_heapify(vetor, m, start, end); // Recursively adjust downstream nodes
    }
}

void HeapSort_min(int* vetor, int start, int end) {
    // Build the heap from the bottom up
    for (int i = (end - start) / 2 + start; i >= start; i--) {
        min_heapify(vetor, i, start, end);
    }

    // One by one extract an element from heap
    for (int i = end; i > start; i--) {
        swap(vetor[start], vetor[i]); // Move current root to end
        min_heapify(vetor, start, start, i - 1); // call max heapify on the reduced heap
    }
}