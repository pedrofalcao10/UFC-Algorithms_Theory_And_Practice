#include <iostream>

using namespace std;

int EditDistance(string X, string Y, char** &R) {
    int m = X.size(), n = Y.size();
    
    // Create edit distance matrix
    int** ED = new int*[m+1];
    for (int i = 0; i <= m; i++) ED[i] = new int[n+1];

    // Create and initialize R if it's NULL
    if(R == NULL){
        R = new char*[m+1];
        for (int i = 0; i <= m; i++) R[i] = new char[n+1];
    }

    // Initialize base cases
    for (int j = 0; j <= n; j++) {ED[0][j] = j; R[0][j] = '2';}
    for (int i = 0; i <= m; i++) {ED[i][0] = i; R[i][0] = '3';}

    // Compute distances
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int dif = X[i-1] == Y[j-1] ? 0 : 1;

            int a = ED[i-1][j-1] + dif; // Substitution cost
            int b = ED[i][j-1] + 1;     // Insertion cost
            int c = ED[i-1][j] + 1;     // Deletion cost

            // Choose minimum cost and record operation
            if       ((a < b) && (a < c)) {ED[i][j] = a; R[i][j] = '1';} // 1 (diagonal == substitute)
            else if  ((b < a) && (b < c)) {ED[i][j] = b; R[i][j] = '2';} // 2 (left == insert)
            else if  ((c < a) && (c < b)) {ED[i][j] = c; R[i][j] = '3';} // 3 (up == remove)
            else if ((a == b) && (a < c)) {ED[i][j] = a; R[i][j] = '4';} // 4 (1 or 2)
            else if ((a == c) && (a < b)) {ED[i][j] = a; R[i][j] = '5';} // 5 (1 or 3)
            else if ((b == c) && (b < a)) {ED[i][j] = b; R[i][j] = '6';} // 6 (2 or 3)
            else                          {ED[i][j] = a; R[i][j] = '7';} // 7 (1 or 2 or 3)
        }      //if ((a == b) && (b == c))
    }

    int ed = ED[m][n]; // Final edit distance

    // Clean up memory
    for (int i = 0; i <= m; i++) delete[] ED[i];
    delete[] ED;
    
    return ed;
}

void print_ED_op(int i, int j, char** R, string X, string Y, string op1, string op2) {
    if ((i==0)&&(j==0)) {
        cout << op1 << "\n";
        cout << op2 << "\n\n";
        return;
    }

    if      (R[i][j] == '1') {N
        print_ED_op(i-1, j-1, R, X, Y, string(1,X[i-1])+op1, string(1,Y[j-1])+op2);
        return;
    }
    else if (R[i][j] == '2') {
        print_ED_op(i, j-1, R, X, Y, "_"+op1, string(1,Y[j-1])+op2);
        return;
    }
    else if (R[i][j] == '3') {
        print_ED_op(i-1, j, R, X, Y, string(1,X[i-1])+op1, "_"+op2);
        return;
    }
    else if (R[i][j] == '4') {
        print_ED_op(i-1, j-1, R, X, Y, string(1,X[i-1])+op1, string(1,Y[j-1])+op2);
        print_ED_op(i, j-1, R, X, Y, "_"+op1, string(1,Y[j-1])+op2);
        return;
    }
    else if (R[i][j] == '5') {
        print_ED_op(i-1, j-1, R, X, Y, string(1,X[i-1])+op1, string(1,Y[j-1])+op2);
        print_ED_op(i-1, j, R, X, Y, string(1,X[i-1])+op1, "_"+op2);
        return;
    }
    else if (R[i][j] == '6') {
        print_ED_op(i, j-1, R, X, Y, "_"+op1, string(1,Y[j-1])+op2);
        print_ED_op(i-1, j, R, X, Y, string(1,X[i-1])+op1, "_"+op2);
        return;
    }
    else if (R[i][j] == '7') {
        print_ED_op(i-1, j-1, R, X, Y, string(1,X[i-1])+op1, string(1,Y[j-1])+op2);
        print_ED_op(i, j-1, R, X, Y, "_"+op1, string(1,Y[j-1])+op2);
        print_ED_op(i-1, j, R, X, Y, string(1,X[i-1])+op1, "_"+op2);
        return;
    }
}

void print_matrix_char(string X, string Y, char** R) {
    int m = X.size(), n = Y.size();

    cout << "  " << Y << "\n ";
    for (int j = 0; j <= n; j++) cout << " ";
    cout << "\n";
    for (int i = 1; i<=  m; i++) {
        cout << X[i-1] << " ";
        for (int j = 1; j <= n; j++) cout << R[i][j];
        cout << "\n";
    }
}

void print_matrix_int(string X, string Y, int** R) {
    int m = X.size(), n = Y.size();

    cout << "   " << Y << "\n  ";
    for (int j = 0; j <= n; j++) cout << R[0][j];
    cout << "\n";
    for (int i = 1; i <= m; i++) {
        cout << X[i-1] << " ";
        for (int j = 0; j <= n; j++) cout << R[i][j];
        cout << "\n";
    }
    cout << "\n\n";
}

int main() {
    string X = "SNOWY";
    string Y = "SUNNY";
    //string X = "ALGORITMO";
    //string Y = "SALGADO";
    int m = X.size(), n = Y.size();

    cout << "\n---------------------------------------------\n";
    cout << "X = " << X << "\n";
    cout << "Y = " << Y << "\n\n";

    char** R = NULL;
    int ed = EditDistance(X, Y, R);
    cout << "Edit Distance = " << ed << "\n\n";


    cout << "\n---------------------------------------------\n";
    cout << "Todas as solucoes otimas:\n\n";
    string op1, op2;
    print_ED_op(m, n, R, X, Y, op1, op2);


    cout << "\n---------------------------------------------\n";
    cout << "Matriz de Operacoes de Edicao:\n\n";
    print_matrix_char(X, Y, R);

    cout << "\n\n";
    cout << "LEGENDA:\n";
    cout << "1 (diagonal == substitute)\n";
    cout << "2 (left == insert)\n";
    cout << "3 (up == remove)\n";
    cout << "4 (1 or 2)\n";
    cout << "5 (1 or 3)\n";
    cout << "6 (2 or 3)\n";
    cout << "7 (1 or 2 or 3)\n";
    cout << "\n---------------------------------------------\n\n";

    if (R != NULL) {
        for (int i = 0; i <= m; i++) delete[] R[i];
        delete[] R;
    }

    return 0;
}