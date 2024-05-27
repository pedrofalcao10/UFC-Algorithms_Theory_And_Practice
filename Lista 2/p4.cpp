#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

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
    string x = "ACGTGTCAAAATCG";
    string y = x;
    
    reverse(y.begin(), y.end());

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