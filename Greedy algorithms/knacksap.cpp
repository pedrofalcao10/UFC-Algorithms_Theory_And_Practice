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

// Function to maximize the knapsack value
double Knapsack_fractional(const vector<char>& items, const vector<double>& values, const vector<double>& weights, double max_weight, vector<double>& x) {
    int n = items.size();
    vector<pair<double, int>> ratios; // Store ratios and their indices

    // Calculate and store the value/weight ratios of items
    for (int i = 0; i < n; i++) {
        ratios.emplace_back(values[i] / weights[i], i);
    }

    // Sort items based on value-to-weight ratio in descending order
    sort(ratios.rbegin(), ratios.rend());

    double max_value = 0; // Maximum value that can be attained
    x.assign(n, 0); // Initialize the amount of each item taken in the knapsack

    // Fill the knapsack to maximize the value while not exceeding the max weight
    for (auto& ratio : ratios) {
        int idx = ratio.second; // Index of the item in the original arrays
        if (weights[idx] <= max_weight) {
            x[idx] = weights[idx]; // Take the whole item
            max_value += values[idx];
            max_weight -= weights[idx];
        } else {
            x[idx] = max_weight; // Take only a part of the item if necessary
            max_value += values[idx] * (max_weight / weights[idx]);
            max_weight = 0;
            break; // The bag is full
        }
    }

    return max_value;
}

// Function to maximize the knapsack value for the 0/1 knapsack problem
double Knapsack_01(const vector<char>& items, const vector<double>& values, const vector<double>& weights, double max_weight, vector<int>& x) {
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
    // Corrected map declaration with std::pair as value type
    // Map {item, {value, weight}}
    map<char, pair<double, double>> my_items = {
        {'A', {50.0, 5}},
        {'B', {140.0, 20}},
        {'C', {60.0, 10}},
        {'D', {60.0, 10}}
    };

    // Extracting keys, values, and weights into vectors
    vector<char> items;
    vector<double> values;
    vector<double> weights;

    for (const auto& item : my_items) {
        items.push_back(item.first);
        values.push_back(item.second.first);
        weights.push_back(item.second.second);
    }

    double max_weight = 30; // Maximum weight the bag can hold
    vector<double> x_frac; // Amount of each item in the knapsack

    double max_value_frac = Knapsack_fractional(items, values, weights, max_weight, x_frac);

    // Output the results
    cout << "Maximum value in knapsack: " << max_value_frac << endl;
    cout << "Amounts of each item taken:" << endl;
    for (size_t i = 0; i < items.size(); i++) {
        cout << "Item " << items[i] << ": " << x_frac[i] << " units" << endl;
    }

    return 0;
}