#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

int function(int n) {
    if (n == 1 or n == 2 or n == 3 or n == 4) return 0;

    return function((n/2)) + function((n/2) + 1) + function((n/2) + 2) + n; 
}

int lookup_func(int *vector_memo, int n) {
    if (vector_memo[n] >= 0) return vector_memo[n]; // Return memoized result if available

    if (n <= 4) vector_memo[n] = 0; // Base case: directly memoize and return
    else vector_memo[n] = lookup_func(vector_memo, n/2) + lookup_func(vector_memo, n/2 + 1) + lookup_func(vector_memo, n/2 + 2) + n;
    
    return vector_memo[n];
}

int function_memo(int *vector_memo ,int n) {
    for (int i = 0; i < n; i++) vector_memo[i] = -1;

    return lookup_func(vector_memo, n);
}

int function_DP(int *vector_DP, int n){
    for (int i = 0; i < 5; i++) vector_DP[i] = 0;

    for (int i = 5; i < n; i++) vector_DP[i] = vector_DP[i/2] + vector_DP[i/2 + 1] + vector_DP[i/2 + 2] + i;

    return vector_DP[n];
}

int main() {
    int n = 6;

    auto start_rec1 = std::chrono::high_resolution_clock::now();
    int result_rec1 = function(n);
    auto stop_rec1 = std::chrono::high_resolution_clock::now();
    auto duration_rec1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop_rec1 - start_rec1);
    std::cout << "function(" << n << ") is " << result_rec1 << std::endl;
    std::cout << "Time taken by function: " << duration_rec1.count() << " milliseconds\n" << std::endl;

    int vetor_memo[n+1];
    auto start_rec2 = std::chrono::high_resolution_clock::now();
    int result_rec2 = function_memo(vetor_memo, n);
    auto stop_rec2 = std::chrono::high_resolution_clock::now();
    auto duration_rec2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop_rec2 - start_rec2);
    std::cout << "function_memo(" << n << ") is " << result_rec2 << std::endl;
    std::cout << "Time taken by function_memo: " << duration_rec2.count() << " milliseconds\n" << std::endl;

    int vetor_DP[n+1];
    auto start_rec3 = std::chrono::high_resolution_clock::now();
    int result_rec3 = function_DP(vetor_DP, n);
    auto stop_rec3 = std::chrono::high_resolution_clock::now();
    auto duration_rec3 = std::chrono::duration_cast<std::chrono::milliseconds>(stop_rec3 - start_rec3);
    std::cout << "function_DP(" << n << ") is " << result_rec3 << std::endl;
    std::cout << "Time taken by function_DP: " << duration_rec3.count() << " milliseconds\n" << std::endl;

}