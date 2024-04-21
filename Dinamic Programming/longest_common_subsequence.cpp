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
    int m = x.size(), n = y.size();

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

unsigned int LCS(string x, string y, char** &R) {
    int m = x.size(), n = y.size();

    int** lcs = new int*[m+1];
    for (int i = 0; i <= m; i++) lcs[i] = new int[n+1];

    if(R == NULL){
        R = new char*[m+1];
        for(int i = 0; i <= m; i++) R[i] = new char[n+1];
    }

    for (int i = 0; i <= m; i++) lcs[i][0] = 0;
    for (int j = 0; j <= n; j++) lcs[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i-1] == y[j-1]) // (diagonal)
            {
                lcs[i][j] = lcs[i-1][j-1] + 1;
                R[i][j] = '\\';
            }
            else if (lcs[i-1][j] == lcs[i][j-1]) // (up or left)
            {
                lcs[i][j] = lcs[i-1][j];
                R[i][j] = '+';
            }
            else if (lcs[i-1][j] < lcs[i][j-1]) // (left)
            {
                lcs[i][j] = lcs[i][j-1];
                R[i][j] = '-';
            }
            else // (up)
            {
                lcs[i][j] = lcs[i-1][j];
                R[i][j] = '|';
            }
        }
    }

    int r = lcs[m][n];
    for (int i = 0; i <= m; i++) delete[] lcs[i];
    delete[] lcs;

    return r;
}

void print_LCS(int i, int j, string x, char** R, string lcs) {
    if ((i==0)||(j==0)) {
        cout << lcs << "\n";
        return;
    }

    if (R[i][j]=='\\') 
    {
        lcs = string(1,x[i-1]) + lcs;
        print_LCS(i-1,j-1, x, R, lcs);
    }
    else if (R[i][j]=='+')
    {
        print_LCS(i-1,j, x, R, lcs);
        print_LCS(i,j-1, x, R, lcs);
    }
    else if (R[i][j]=='-')
    {
        print_LCS(i,j-1, x, R, lcs);
    }
    else
    {
        print_LCS(i-1,j, x, R, lcs);
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