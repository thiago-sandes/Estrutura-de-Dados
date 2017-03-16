#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAXTAM  10
#define DADOS_NATUREZA  100000 //100 mil
#define N_EXPERIMENTOS  20
#define N_REP 10 //para cada experimento

void sort (int *vet, int size) {
    int i , j , value;
    
    int gap = 1;
    while(gap < size) {
        gap = 3*gap+1;
    }
    
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap;
            }
            vet [j + gap] = value;
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j, k, n, TAMANHO, tempo, ini, fim, FATOR;
    //time_t segundos01, segundos02;
    struct timespec start, end;
    
    srand(time(NULL));
    
    char url[]="data.txt";
    FILE *arq;
    arq = fopen(url, "w");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        return -1;
    }
    printf("\n\nArquivo criado.");
    
    /* Gera uma permutacao aleatoria de chaves entre 1 e DADOS_NATUREZA e acumula em vetor */
    int vetor[DADOS_NATUREZA];
    int vetorordenado[DADOS_NATUREZA];
    for(i = 0; i < DADOS_NATUREZA; i++)
        vetor[i] = i + 1;
    for(i = 0; i < DADOS_NATUREZA; i++)
    {
        k =  (int) ((float)DADOS_NATUREZA * rand()/(RAND_MAX + 1.0));
        j =  (int) ((float)DADOS_NATUREZA * rand()/(RAND_MAX + 1.0));
        n = vetor[k];
        vetor[k] = vetor[j];
        vetor[j] = n;
        vetorordenado[j] = vetor[j];
    }
    
    /* Testando corretude do algoritmo de ordenacao apenas com os 10 primeiros elementos */
    printf("\n\nAntes: ");
    for(i = 0; i < 10; i++)
        printf("%d,",vetorordenado[i]);
    printf("...");
    sort(vetorordenado,10);
    bubblesort(vetorordenado,10);
    printf("\nDepois: ");
    for(i = 0; i < 10; i++)
        printf("%d,",vetorordenado[i]);
    printf("...");
    
    /* Num experimentos */
    printf("\n\nExecutando experimentos...");
    FATOR = DADOS_NATUREZA / N_EXPERIMENTOS;
    for(i = 1; i <= N_EXPERIMENTOS; i++) 
    {
        TAMANHO = i*FATOR;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for(j = 0; j < N_REP; j++)
            sort(vetorordenado,TAMANHO);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        // unsigned int (alternativa)
        unsigned long long delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
        fprintf(arq,"%d\t%llu\n",TAMANHO,delta_us);
    }
    printf("\n Finalizado!\n\n");
    fclose(arq);
    return(0);
}


