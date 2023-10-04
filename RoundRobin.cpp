#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#define tam 15 // Número máximo de processos

struct Processo {
    char nome[50]; 
    int chegada;   
    int tempo_uso; 
};

int NumProcesso;
int quantum; 

struct Processo processos[tam]; 

// Função de comparação para ordenar os processos com base no tempo de chegada e tempo de uso
int comparar_processos(const void *a, const void *b) {
    struct Processo *processoA = (struct Processo *)a;
    struct Processo *processoB = (struct Processo *)b;

    if (processoA->chegada > processoB->chegada) {
        return processoA->chegada < processoB->chegada;
    }

    return processoA->tempo_uso > processoB->tempo_uso;
}

void entrada_processos() {
    int i;
    for (i = 0; i < NumProcesso; i++) {
        printf("\nDigite o nome do processo %d: ", i + 1);
        scanf("%s", processos[i].nome);
        printf("Digite o tempo de uso do CPU do processo %s: ", processos[i].nome);
        scanf("%d", &processos[i].tempo_uso);
        printf("Digite o tempo de chegada do processo %s: ", processos[i].nome);
        scanf("%d", &processos[i].chegada);
    }

    // Ordena os processos com base no tempo de chegada e tempo de uso
    qsort(processos, NumProcesso, sizeof(struct Processo), comparar_processos);
}

void fila() {
    int tempo_atual = 0;
    int contadorFila = NumProcesso;
    int processo_atual = 0; // Índice do próximo processo a ser executado

    while (contadorFila != 0) {
        if (processos[processo_atual].tempo_uso > 0 && processos[processo_atual].chegada <= tempo_atual) {
            printf("\n\nExecutando processo %s", processos[processo_atual].nome);
            printf("\nTempo restante de CPU: %d", processos[processo_atual].tempo_uso);

            int exec_time = (processos[processo_atual].tempo_uso < quantum) ? processos[processo_atual].tempo_uso : quantum;
            processos[processo_atual].tempo_uso -= exec_time;
            tempo_atual += exec_time;

            printf("\nConsumiu %d tempos", exec_time);

            if (processos[processo_atual].tempo_uso <= 0) {
                printf("\n%s terminou a execucao.", processos[processo_atual].nome);
                contadorFila--;
            } else {
                printf("\n%s ainda precisa de %d tempos de CPU para terminar.", processos[processo_atual].nome, processos[processo_atual].tempo_uso);
            }
        }

        processo_atual++;

        // Se todos os processos foram executados, reinicie a fila
        if (processo_atual >= NumProcesso) {
            processo_atual = 0;
        }
    }
}

int main() {
    printf(":::::::::::: INICIO ::::::::::::");
    printf("\nDigite o numero de (quantum): ");
    scanf("%d", &quantum);
    printf("\nDigite o numero de processos: ");
    scanf("%d", &NumProcesso);
    entrada_processos();
    fila();
    printf("\n\n:::::::::::: FIM :::::::::::::\n");
    return 0;
}
