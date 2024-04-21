#include <iostream>
using namespace std;

int max(int m, int n) {return (m >= n) ? m : n;}

int LCS_rec(int *x, int *y, int i, int j){
    if ((i == 0) || (j == 0)) return 0;

    if (x[i] == y[j]) return LCS_rec(x, y, i - 1, j - 1);
    else return max(LCS_rec(x, y, i - 1, j), LCS_rec(x, y, i, j - 1));
}