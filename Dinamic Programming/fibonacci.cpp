#include <iostream>
#include <chrono>

int fibonacci_rec(int n) { //Bad algorithm, solve subproblems too many times
    if (n <= 2) return 1;
    else return fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
}

int main() {
    int n = 30;  // Example: Compute the 30th Fibonacci number

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    // Function call
    int result = fibonacci_rec(n);

    // End timing
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Fibonacci(" << n << ") is " << result << std::endl;
    std::cout << "Time taken by fibonacci_rec: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
