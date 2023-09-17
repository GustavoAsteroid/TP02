#include <stdio.h>
#include <string.h>
#include <locale.h>

void trocar(char *arr[], int i, int j) {
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int particionar(char *arr[], int baixo, int alto, int *trocas, int *comparacoes) {
    char *pivot = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        (*comparacoes)++;
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            (*trocas)++;
            trocar(arr, i, j);
        }
    }
    (*trocas)++;
    trocar(arr, i + 1, alto);
    return (i + 1);
}

void quickSort(char *arr[], int baixo, int alto, int *trocas, int *comparacoes) {
    if (baixo < alto) {
        int pivo = particionar(arr, baixo, alto, trocas, comparacoes);
        quickSort(arr, baixo, pivo - 1, trocas, comparacoes);
        quickSort(arr, pivo + 1, alto, trocas, comparacoes);
    }
}

int main() {
	setlocale(LC_ALL,"");
	
    char *arr[20] = {
        "maca", "banana", "pera", "uva", "laranja", "abacaxi", "limão", "manga", "abacate", "kiwi",
        "cereja", "morango", "pêssego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"
    };

    int trocas = 0, comparacoes = 0;
    int tamanho = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, tamanho - 1, &trocas, &comparacoes);

    printf("Vetor ordenado:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s\n", arr[i]);
    }
    
    FILE *arquivo = fopen("saida.txt", "w");
	if (arquivo == NULL) {
    printf("Erro ao criar o arquivo de saída.\n");
    return 1;
}

	fprintf(arquivo, "Vetor ordenado:\n");
	for (int i = 0; i < tamanho; i++) {
    fprintf(arquivo, "%s\n", arr[i]);
}

	fclose(arquivo);

    char *mediana;
    if (tamanho % 2 == 0) {
        int meio1 = tamanho / 2;
        int meio2 = meio1 - 1;
        mediana = malloc(strlen(arr[meio1]) + strlen(arr[meio2]) + 2);
        strcpy(mediana, arr[meio1]);
        strcat(mediana, " ");
        strcat(mediana, arr[meio2]);
    } else {
        mediana = arr[tamanho / 2];
    }
    printf("\nMediana: %s\n", mediana);

    printf("Número de trocas: %d\n", trocas);
    printf("Número de comparações: %d\n", comparacoes);

    return 0;
}
