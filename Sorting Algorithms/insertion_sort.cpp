void InsertionSort(int* vetor, int p, int r){
    int i, j, carta;

    for(j = p+1; j <= r; j++){
        carta = vetor[j];
        i = j-1;

        while((i >= p) && (vetor[i] > carta)){
            vetor[i+1] = vetor[i];
            i--;
        }

        vetor[i+1] = carta;
    }
}