#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Para lidar com strings
#define tam 15 // Número máximo de processos

struct Processo {
    char nome[50]; // Nome do processo
    int chegada;   // Tempo de chegada
    int tempo_uso; // Tempo de uso do CPU
};

int NumProcesso;
int quantum; // Número de vezes que será executado o processo

struct Processo processos[tam]; // Fila de processos

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
    int i, j;
    for (i = 0; i < NumProcesso; i++) {
        printf("\nDigite o nome do processo %d: ", i + 1);
        scanf("%s", processos[i].nome);

        // Verifica se o nome do processo já existe
        for (j = 0; j < i; j++) {
            if (strcmp(processos[i].nome, processos[j].nome) == 0) {
                printf("Esse nome ja existe, insira um valido\n");
                i--;
                break;
            }
        }

        printf("Digite o tempo de uso do CPU do processo %s: ", processos[i].nome);
        scanf("%d", &processos[i].tempo_uso);

        // Verifica se o tempo de uso é menor que 0
        if (processos[i].tempo_uso < 0) {
            printf("Tempo de uso nao pode ser menor que 0, insira um valor valido.\n");
            i--;
            continue;
        }

        printf("Digite o tempo de chegada do processo %s: ", processos[i].nome);
        scanf("%d", &processos[i].chegada);

        // Verifica se o tempo de chegada é menor que 0
        if (processos[i].chegada < 0) {
            printf("Tempo de chegada nao pode ser menor que 0, insira um valor valido.\n");
            i--;
        }
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
    // Verifica se o número de quantum é menor que 0
    if (quantum < 0) {
        printf("O numero de quantum não pode ser menor que 0. Insira um valor valido.\n");
        return 1; // Encerra o programa com um código de erro
    }

    printf("\nDigite o numero de processos: ");
    scanf("%d", &NumProcesso);
    // Verifica se o número de processos é menor que 0
    if (NumProcesso < 0) {
        printf("O numero de processos nao pode ser menor que 0. Insira um valor valido.\n");
        return 1; // Encerra o programa com um código de erro
    }

    entrada_processos();
    fila();
    printf("\n\n:::::::::::: FIM :::::::::::::\n");
    return 0;
}
