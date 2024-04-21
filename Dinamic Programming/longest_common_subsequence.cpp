#include <iostream>
using namespace std;

// Function to return the maximum of two integers.
// Parameters:
//   m - first integer to compare
//   n - second integer to compare
int max(int m, int n) {
    // Return the larger of m or n
    return (m >= n) ? m : n;
}

// Recursive function to compute the length of the Longest Common Subsequence (LCS)
// between substrings of `x` and `y` up to indices `i` and `j`.
// Parameters:
//   x - the first string
//   y - the second string
//   i - current index in string `x`
//   j - current index in string `y`
int LCS_rec(string x, string y, int i, int j){
    // Base case: if either index reaches 0, the LCS is 0 because one substring is empty.
    if ((i == 0) || (j == 0)) return 0;

    // If characters at current indices match, include this character in the LCS and
    // move to the next character in both strings.
    if (x[i] == y[j]) return LCS_rec(x, y, i - 1, j - 1) + 1;
    else {
        // If characters do not match, find the LCS by either excluding the character from `x`
        // or `y` and return the maximum length obtained.
        return max(LCS_rec(x, y, i - 1, j), LCS_rec(x, y, i, j - 1));
    }
}

// Initializes the memoization table for LCS calculation.
// Parameters:
//   x - the first string
//   y - the second string
//   lcs - reference to a pointer of pointers to store LCS values
void LCS_memo(string x, string y, int** &lcs) {
    int m = x.size(), n = y.size();

    // Allocate memory for LCS table if not already allocated
    if (lcs == NULL) {
        lcs = new int*[m+1];
        for (int i = 0; i <= m; i++) {
            lcs[i] = new int[n+1];
        }
    }

    // Initialize the first row and first column of LCS table to zero
    for (int i = 0; i <= m; i++) lcs[i][0] = 0;
    for (int j = 0; j <= n; j++) lcs[0][j] = 0;
    
    // Initialize the rest of the LCS table to -1 to denote uncomputed values
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            lcs[i][j] = -1;
}

// Recursive memoized LCS calculation function.
// Parameters:
//   x - the first string
//   y - the second string
//   i - current index in string `x`
//   j - current index in string `y`
//   lcs - memoization table
int LCS_rec_memo(string x, string y, int i, int j, int**& lcs) {
    // Return the memoized result if it has already been computed
    if (lcs[i][j] >= 0) return lcs[i][j];

    // If characters match, store the result of 1 + LCS of previous indices in both strings
    if (x[i] == y[j])
        lcs[i][j] = LCS_rec_memo(x, y, i - 1, j - 1, lcs) + 1;
    else // If characters do not match, compute the max LCS by excluding one character at a time
        lcs[i][j] = max(LCS_rec_memo(x, y, i - 1, j, lcs), LCS_rec_memo(x, y, i, j - 1, lcs));

    return lcs[i][j];
}


// Function to compute the Longest Common Subsequence (LCS) using dynamic programming (DP).
// This is a bottom-up, non-recursive approach.
// Parameters:
//   x - the first string
//   y - the second string
int LCS_DP(string x, string y) {
    int m = x.size(), n = y.size();

    // Create a 2D array to store lengths of longest common subsequence.
    int** lcs = new int*[m+1];
    for (int i = 0; i <= m; i++) {
        lcs[i] = new int[n+1];
    }

    // Initializing the first row and first column to 0 because LCS with an empty string is 0.
    for (int i = 0; i <= m; i++) lcs[i][0] = 0;
    for (int j = 0; j <= n; j++) lcs[0][j] = 0;

    // Fill the rest of the lcs array
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i] == y[j]) {
                // If characters match, add 1 to the result from the diagonally previous cell
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                // If not, take the maximum from the left or top cell
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        }
    }

    // The bottom-right cell contains the length of LCS for x and y
    int result = lcs[m][n];

    // Clean up memory
    for (int i = 0; i <= m; i++) {
        delete[] lcs[i];
    }
    delete[] lcs;

    return result;
}


// Function to compute the Longest Common Subsequence (LCS) of two strings x and y,
// and to record the decision path in matrix R.
// Parameters:
//   x - the first string
//   y - the second string
//   R - a reference to a pointer of pointers that will store the decision path
unsigned int LCS(string x, string y, char** &R) {
    int m = x.size(), n = y.size();

    // Create and initialize the LCS table
    int** lcs = new int*[m+1];
    for (int i = 0; i <= m; i++) {
        lcs[i] = new int[n+1];
    }

    // Allocate memory for R if it has not been already allocated
    if (R == NULL) {
        R = new char*[m+1];
        for (int i = 0; i <= m; i++) {
            R[i] = new char[n+1];
        }
    }

    // Initialize the boundaries of the LCS table
    for (int i = 0; i <= m; i++) lcs[i][0] = 0;
    for (int j = 0; j <= n; j++) lcs[0][j] = 0;

    // Fill in the LCS values and record directions in R
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i-1] == y[j-1])
            {
                lcs[i][j] = lcs[i-1][j-1] + 1;
                R[i][j] = '\\'; // Diagonal, indicates a match
            }
            else if (lcs[i-1][j] == lcs[i][j-1])
            {
                lcs[i][j] = lcs[i-1][j];
                R[i][j] = '+'; // Up or left
            }
            else if (lcs[i-1][j] < lcs[i][j-1]) 
            {
                lcs[i][j] = lcs[i][j-1];
                R[i][j] = '-'; // Left, skip character in y
            }
            else // (up)
            {
                lcs[i][j] = lcs[i-1][j];
                R[i][j] = '|'; // Up, skip character in x
            }
        }
    }

    // Extract the result and clean up memory
    int result = lcs[m][n];
    for (int i = 0; i <= m; i++) {
        delete[] lcs[i]; // Free each row of lcs
    }
    delete[] lcs; // Free the array of pointers

    return result;
}

void print_LCS(int i, int j, string x, char** R, string lcs) {
    if ((i==0)||(j==0)) {
        cout << lcs << "\n";
        return;
    }

    if (R[i][j]=='\\') 
    {
        lcs = string(1,x[i-1]) + lcs;
        print_LCS(i-1, j-1, x, R, lcs);
    }
    else if (R[i][j]=='+')
    {
        print_LCS(i-1, j, x, R, lcs);
        print_LCS(i, j-1, x, R, lcs);
    }
    else if (R[i][j]=='-')
    {
        print_LCS(i, j-1, x, R, lcs);
    }
    else
    {
        print_LCS(i-1, j, x, R, lcs);
    }
}

void print_matrix(string x, string y, char** R) {
    int m = x.size(), n = y.size();

    cout << "  " << y << "\n ";

    for (int j = 0; j <= n; j++) cout << " ";

    cout << "\n";

    for (int i = 1; i <= m; i++) {
        cout << x[i-1] << " ";
        for (int j = 1; j <= n; j++) cout << R[i][j];
        cout << "\n";
    }
}

int main() {
    string x = "ABCBDAB";
    string y = "BDCABA";
    cout << "Entrance X = " << x << "\n";
    cout << "Entrance Y = " << y << "\n\n";

    char** R = NULL;
    cout << "Length of LCS = " << LCS(x, y, R);
    cout << "\n\n";

    string lcs;
    cout << "All possible LCS's :\n";
    print_LCS(x.size(), y.size(), x, R, lcs);
    cout << "\n\n\n";

    print_matrix(x,y,R);
    if (R != NULL) {
        for (int i = 0; i <= x.size(); i++) delete[] R[i];
        delete[] R;
    }

    cout << "\n";
    cout << "Simbol \\ (diagonal)\n";
    cout << "Simbol | (up)\n";
    cout << "Simbol - (left)\n";
    cout << "Simbol + (up or left)\n\n";
    return 0;
}