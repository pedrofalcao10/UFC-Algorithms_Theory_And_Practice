#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
using namespace std;

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

int main() {
    vector<char> item = {'a', 'b', 'c', 'd'};
    vector<double> values = {50,140,60,60}; // Value of items
    vector<double> weights = {5,20,10,12}; // Weight of items
    double max_weight = 30; // Maximum weight the bag can hold
    vector<double> x; // Amount of each item in the knapsack

    double max_value = Knapsack_fractional(item, values, weights, max_weight, x);

    // Output the maximum value and the contents of the knapsack
    cout << "Maximum value achievable: " << max_value << endl;
    cout << "Items and amounts taken:" << endl;
    for (int i = 0; i < item.size(); i++) 
        cout << "Item " << item[i] << ": " << x[i] << " kg" << endl;

    return 0;
}