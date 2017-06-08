#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIM 100000

long int POWERS = 0;

void maxHeapFy(int *C, int dad, int tam){
    int l = 2 * dad, r = (2 * dad)+ 1, largest;
    int aux;
    if(l <= tam && C[l] > C[dad]){
        largest = l;
    }
    else{
        largest = dad;
    }
    if(r <= tam && C[r] > C[largest]){
        largest = r;
    }
    if(largest != dad){
        aux = C[dad];
        C[dad] = C[largest];
        C[largest] = aux;
        POWERS += 2;
        maxHeapFy(C, largest, tam);
    }
}

void buildMaxHeap(int *C, int tam){
    int i;
    for(i = tam/2; i >= 0; i--){
        maxHeapFy(C, i, tam);
    }
}

void heapSort(int *C, int tam){
    int aux, i;
    buildMaxHeap(C, tam);
    for(i = tam; i >=0; i--){
        aux = C[0];
        C[0] = C[i];
        C[i] = aux;
        POWERS += 2;
        maxHeapFy(C, 0, i-1);
    }
}

void lerValores(char *url, int *C, int tam){
    FILE *arq;
    int i = 0;
	arq = fopen(url, "r");
	if(arq == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		while( (fscanf(arq,"%d\n", &C[i]))!=EOF ){
            i++;
            if(i == tam)
                break;
		}
	}
	fclose(arq);
}

void imprimir(int *C, int tam){
    int i;
    printf("\n-------------------\n");
    printf("Valores:\n");
    printf("-------------------\n");
    for(i=0;i < tam;i++)
        printf("%d\n",C[i]);
    printf("-------------------\n\n");
}

int main(int argc, char *argv[]){
    int tam = atoi(argv[1]);
    char* url = argv[2];
	if(tam > LIM || tam <= 2 || argc != 3){
        printf("Erro, parametros invalidos\n");
        exit(1);
	}
	int *C;
	C = (int*) malloc(sizeof(int)* tam);
	if(C == NULL){
        printf("Erro, nao foi possivel criar vetor");
        exit(1);
	}
	lerValores(url,C,tam);
	clock_t tempo;
	tempo = clock();
    heapSort(C,tam);
    float temp = (clock() - tempo) / (double)CLOCKS_PER_SEC;
    imprimir(C,tam);
    printf("Tempo:%f\n",temp);
    free(C);
	exit(1);
}
