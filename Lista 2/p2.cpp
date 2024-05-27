#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    vector<int> S = {5, 15, -30, 10, -5, 40, 10, -60, 7};
    int n = S.size();

    vector<int> s(n);
    s[0] = S[0];

    for (int i = 1; i < n; i++) {
        s[i] = max(S[i], S[i] + s[i - 1]);
    }

    int max_sum = INT_MIN;
    int b = -1;

    for (int i = 0; i < n; i++) {
        if (max_sum < s[i]) {
            max_sum = s[i];
            b = i;
        }
    }

    int a = b;

    while (a > 0 && s[a] > S[a]) {
        a--;
    }

    cout << "begin of the subsequence (a): " << a << endl;
    cout << "end of the subsequence   (b): " << b << endl;
    cout << "Maximum subarray sum: " << max_sum << endl;

    return 0;
}
