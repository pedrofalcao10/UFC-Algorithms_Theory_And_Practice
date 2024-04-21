#include <iostream>
using namespace std;

int max(int m, int n) {return (m >= n) ? m : n;}

int LCS_rec(string x, string y, int i, int j){
    if ((i == 0) || (j == 0)) return 0;

    if (x[i] == y[j]) return LCS_rec(x, y, i - 1, j - 1) + 1;
    else return max(LCS_rec(x, y, i - 1, j), LCS_rec(x, y, i, j - 1));
}

int LCS_memo(string x, string y, int** &lcs) {
    int i, j, m = x.size(), n = y.size();

    if(lcs == NULL){
        lcs = new int*[m+1];
        for(int i = 0; i <= m; i++) lcs[i] = new int[n+1];
    }

    for (int i = 0; i <= m; i++) lcs[i][0] = 0;
    for (int j = 0; j <= n; j++) lcs[0][j] = 0;
    
    for (int i = 1; i <= m; i++) 
        for (int j = 1; j <= n; j++)
            lcs[i][j] = -1;
}

int LCS_rec_memo(string x, string y, int i, int j, int**& lcs) {
    if (lcs[i][j] >= 0) return lcs[i][j];

    if (x[i] == y[j]) lcs[i][j] = LCS_rec_memo(x, y, i - 1, j - 1, lcs) + 1;
    else return max(LCS_rec_memo(x, y, i - 1, j, lcs), LCS_rec_memo(x, y, i, j - 1, lcs));

    return lcs[i][j];
}

int LCS_DP(string x, string y) { // Bottom-up, non recursive
    int i, j, m = x.size(), n = y.size();

    int** lcs = new int*[m+1];
    for(int i = 0; i <= m; i++) lcs[i] = new int[n+1];

    for (int i = 0; i <= m; i++) lcs[i][0] = 0;
    for (int j = 0; j <= n; j++) lcs[0][j] = 0;
    
    for (int i = 1; i <= m; i++) 
        for (int j = 1; j <= n; j++)
            if (x[i] == y[j]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else return max(lcs[i - 1][j], lcs[i][j - 1]);

    return lcs[m][n];
}