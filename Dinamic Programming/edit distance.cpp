#include <iostream>

using namespace std;

int EditDistance(string X, string Y, char** &R) {
    int m = X.size(), n = Y.size();
    int** ED = new int*[m+1];         for (int i = 0; i <= m; i++) ED[i] = new int[n+1];
    if(R == NULL){R = new char*[m+1]; for (int i = 0; i <= m; i++) R[i] = new char[n+1];}

    for (int j = 0; j <= n; j++) {ED[0][j] = j; R[0][j] = '2';}
    for (int i = 0; i <= m; i++) {ED[i][0] = i; R[i][0] = '3';}

    for (int i = 1; i <= m; i++) {
        for (int j = 1; i <= n; j++) {
            int dif;
            X[i-1] == Y[j-1] ? dif = 0 : dif = 1;

            int a = ED[i-1][j-1] + dif;
            int b = ED[i][j-1] + 1;
            int c = ED[i-1][j] + 1;

            if       ((a < b) && (a < c)) {
                ED[i][j] = a;  R[i][j] = '1';
            }
            else if  ((b < a) && (b < c)) {
                ED[i][j] = b;  R[i][j] = '2';
            }
            else if  ((c < a) && (c < b)) {
                ED[i][j] = c;  R[i][j] = '3';
            }
            else if ((a == b) && (a < c)) {
                ED[i][j] = a;  R[i][j] = '4';
            }
            else if ((a == c) && (a < b)) {
                ED[i][j] = a;  R[i][j] = '5';
            }
            else if ((b == c) && (b < a)) {
                ED[i][j] = b;  R[i][j] = '6';
            }
            else {//if   ((a==b)&&(b==c)) {
                ED[i][j] = a;  R[i][j] = '7';
            }
        }
    }

    int ed = ED[m][n];

    for (int i = 0; i <= m; i++) delete[] ED[i];
    delete[] ED;
    
    return ed;
}