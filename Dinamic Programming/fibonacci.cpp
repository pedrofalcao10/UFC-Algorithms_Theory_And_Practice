#include <iostream>
#include <chrono>

int fibonacci_rec(int n) { //Bad algorithm, solve subproblems too many times
    if (n <= 2) return 1;
    else return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

// This function recursively calculates the Fibonacci number using memoization.
// It checks if the Fibonacci number for a given index `n` is already computed and stored.
// Parameters:
//   vetor - an array used to store the Fibonacci numbers already calculated to avoid redundant calculations.
//   n - the index of the Fibonacci number to compute.
int lookup_fib(int *vetor, int n){ 
    // Check if the Fibonacci number for index `n` is already computed.
    if (vetor[n] >= 0) return vetor[n];  // If yes, return the stored number.
    
    if (n <= 1) vetor[n] = n;
    else vetor[n] = lookup_fib(vetor, n - 1) + lookup_fib(vetor, n - 2);

    return vetor[n];
}

// This function initializes the memoization array and triggers the computation of the Fibonacci number.
// Parameters:
//   vetor - an array to be used for storing previously computed Fibonacci numbers to ensure
//           each number is only computed once.
//   n - the index of the Fibonacci number to compute.
int memoized_fib(int *vetor, int n){
    // Initialize the memoization array with -1 to indicate that no Fibonacci numbers have been computed.
    for (int i = 0; i < n + 1; i++) {
        vetor[i] = -1;
    }

    return lookup_fib(vetor, n);
}


int main() {
    int n = 38;  // Example: Compute the 30th Fibonacci number

    // start timing
    auto start_rec = std::chrono::high_resolution_clock::now();

    // Function call
    int result_rec = fibonacci_rec(n);

    // End timing
    auto stop_rec = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration_rec = std::chrono::duration_cast<std::chrono::milliseconds>(stop_rec - start_rec);
    
    std::cout << "Fibonacci(" << n << ") is " << result_rec << std::endl;
    std::cout << "Time taken by fibonacci_rec: " << duration_rec.count() << " milliseconds" << std::endl;
    
    int vetor[n+1];

    auto start_memoized = std::chrono::high_resolution_clock::now();
    int result_memoized = memoized_fib(vetor, n);
    auto stop_memoized  = std::chrono::high_resolution_clock::now();
    auto duration_memoized = std::chrono::duration_cast<std::chrono::milliseconds>(stop_memoized - start_memoized);
    
    std::cout << "Fibonacci(" << n << ") is " << result_memoized << std::endl;
    std::cout << "Time taken by fibonacci_memo: " << duration_memoized.count() << " milliseconds" << std::endl;

    return 0;
}
