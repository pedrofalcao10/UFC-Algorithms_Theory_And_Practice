#include <iostream>
#include <vector>
using namespace std;

// Function to determine the maximum revenue from cutting a rod of length N using price list p.
// p: prices of rods of different lengths
// N: length of the rod
// q: memoization for maximum revenues
// R: optimal size of the first piece to cut off for achieving max revenue at each length
int rods(vector<int>& p, int N, vector<int>& q, vector<int>& R) {
    q[0] = 0; // Base case: no revenue for a rod of length 0

    // Calculate the maximum revenue for rods of length 1 to N
    for (int j = 1; j <= N; j++) {
        q[j] = -INT_MAX; // Initialize as negative infinity to find the maximum
        for (int i = 1; i <= j; i++) {
            // Update the maximum revenue q[j] if cutting the rod into lengths i and j-i yields more revenue
            if (q[j] < p[i] + q[j-i]) {
                R[j] = i; // Record the length of the rod that gives this maximum revenue
                q[j] = p[i] + q[j-i]; // Update maximum revenue for length j
            }
        }
    }
    
    return q[N]; // Return the maximum revenue obtainable for a rod of length N
}

int main() {
    // Price list for rods of different lengths (index is length, value is price)
    vector<int> p = {0, 1, 5, 7, 9, 11, 14, 16, 19, 21};
    int N = p.size() - 1; // Length of the rod

    vector<int> q(N + 1, 0); // Vector to store the maximum revenue for each length
    vector<int> R(N + 1, 0); // Vector to store the optimal cut at each length
    int opt = rods(p, N, q, R); // Compute maximum revenues and cuts

    // Output maximum revenues for each possible length
    for (int k = 1; k <= N; k++) {
        cout << "Maximum profit for rod length " << k << " = " << q[k] << "\n";
    }

    cout << "\n";

    cout << "Maximum profit for the whole rod = " << opt << "\n";

    cout << "Cut sizes to be made:\n";
    // Output the sizes of cuts to be made for the whole rod
    int k = N;
    while (k > 0) {
        cout << R[k] << " ";
        k = k - R[k];
    }

    cout << "\n\n";

    // Another visualization of cut sizes in the format "size1 + size2 + ... = N"
    k = N;
    while (k > 0) {
        cout << R[k] << " ";
        k = k - R[k];
        if (k > 0) cout << "+ ";
    }
    cout << "= " << N << "\n";
    return 0;
}