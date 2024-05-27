#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
#include <map>
#include <utility> // for std::pair
using namespace std;
using std::map;
using std::pair;
using std::cout;
using std::endl;

// Function to maximize the knapsack value for the 0/1 knapsack problem
double Knapsack_01(const vector<double>& items, const vector<double>& values, const vector<double>& weights, double max_weight, vector<int>& x) {
    int n = items.size();
    vector<vector<double>> dp(n + 1, vector<double>(static_cast<int>(max_weight) + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int w = 0; w <= max_weight; w++) dp[0][w] = 0;
    
    // Build table dp[][] in bottom-up manner
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= max_weight; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - static_cast<int>(weights[i - 1])] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Store the result of Knapsack
    double max_value = dp[n][static_cast<int>(max_weight)];

    // Track the items included in the knapsack
    int w = max_weight;
    x.assign(n, 0);
    for (int i = n; i > 0 && max_value > 0; --i) {
        if (max_value == dp[i - 1][w]) {
            continue; // This item is not included
        } else {
            x[i - 1] = 1; // This item is included
            max_value -= values[i - 1];
            w -= static_cast<int>(weights[i - 1]);
        }
    }

    return dp[n][static_cast<int>(max_weight)];
}

int main() {
    vector<double> a = {1, 2, 4, 8, 16, 32};

    double T = 37; // Required sum
    vector<int> x_01; // Amount (0/1) of each item in the knapsack

    double max_value_01 = Knapsack_01(a, a, a, T, x_01);

    // Output the results
    cout << "Maximum value in binary knapsack: " << max_value_01 << endl;
    cout << "Items included in the knapsack:" << endl;
    for (size_t i = 0; i < a.size(); i++) {
        if (x_01[i] == 1) {
            cout << "Item " << a[i] << ": included" << endl;
        }   
    }

    return 0;
}