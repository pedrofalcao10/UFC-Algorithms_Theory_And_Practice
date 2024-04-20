#include <iostream>
#include <chrono>

int fibonacci_rec(int n) { //Bad algorithm, solve subproblems too many times
    if (n <= 2) return 1;
    else return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

// This function recursively calculates the Fibonacci number using memoization.
// It checks if the Fibonacci number for a given index `n` is already computed and stored.
// Parameters:
//   vetor_memo - an array used to store the Fibonacci numbers already calculated to avoid redundant calculations.
//   n - the index of the Fibonacci number to compute.
int lookup_fib(int *vetor_memo, int n){ 
    // Check if the Fibonacci number for index `n` is already computed.
    if (vetor_memo[n] >= 0) return vetor_memo[n];  // If yes, return the stored number.
    
    if (n <= 1) vetor_memo[n] = n;
    else vetor_memo[n] = lookup_fib(vetor_memo, n - 1) + lookup_fib(vetor_memo, n - 2);

    return vetor_memo[n];
}

// This function initializes the memoization array and triggers the computation of the Fibonacci number.
// Parameters:
//   vetor_memo - an array to be used for storing previously computed Fibonacci numbers to ensure
//           each number is only computed once.
//   n - the index of the Fibonacci number to compute.
int memoized_fib(int *vetor_memo, int n){
    // Initialize the memoization array with -1 to indicate that no Fibonacci numbers have been computed.
    for (int i = 0; i < n + 1; i++) {
        vetor_memo[i] = -1;
    }

    return lookup_fib(vetor_memo, n);
}

int fibonacci_DP(int *vetor_DP, int n){
    vetor_DP[0] = 0;
    vetor_DP[1] = 1;

    for (int i = 2; i < n + 1; i++) vetor_DP[i] = vetor_DP[i - 1] + vetor_DP[i - 2];

    return vetor_DP[n];
}

int fibonacci(int n){
    if(n <= 0) return 0;

    int f_ant = 0, f_atual = 1;

    for (int i = 2; i < n + 1; i++){
        int f_prox = f_atual + f_ant;
        f_ant = f_atual;
        f_atual = f_prox;
    }

    return f_atual;
}


int main() {
    int n = 30;  // Example: Compute the 30th Fibonacci number

    // start timing
    auto start_rec = std::chrono::high_resolution_clock::now();

    // Function call
    int result_rec = fibonacci_rec(n);

    // End timing
    auto stop_rec = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration_rec = std::chrono::duration_cast<std::chrono::milliseconds>(stop_rec - start_rec);
    
    std::cout << "fibonacci_rec(" << n << ") is " << result_rec << std::endl;
    std::cout << "Time taken by fibonacci_rec: " << duration_rec.count() << " milliseconds\n" << std::endl;
    


    int vetor_memo[n+1];
    auto start_memoized = std::chrono::high_resolution_clock::now();
    int result_memoized = memoized_fib(vetor_memo, n);
    auto stop_memoized  = std::chrono::high_resolution_clock::now();
    auto duration_memoized = std::chrono::duration_cast<std::chrono::milliseconds>(stop_memoized - start_memoized);
    
    std::cout << "fibonacci_memo(" << n << ") is " << result_memoized << std::endl;
    std::cout << "Time taken by fibonacci_memo: " << duration_memoized.count() << " milliseconds\n" << std::endl;
    


    int vetor_DP[n+1];
    auto start_DP = std::chrono::high_resolution_clock::now();
    int result_DP = fibonacci_DP(vetor_DP, n);
    auto stop_DP  = std::chrono::high_resolution_clock::now();
    auto duration_DP = std::chrono::duration_cast<std::chrono::milliseconds>(stop_DP - start_DP);
    
    std::cout << "fibonacci_DP(" << n << ") is " << result_DP << std::endl;
    std::cout << "Time taken by fibonacci_DP: " << duration_DP.count() << " milliseconds\n" << std::endl;
    

    
    auto start = std::chrono::high_resolution_clock::now();
    int result = fibonacci(n);
    auto stop  = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << "fibonacci(" << n << ") is " << result << std::endl;
    std::cout << "Time taken by fibonacci: " << duration.count() << " milliseconds\n" << std::endl;

    return 0;
}
