#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passagem.h"

void salvarPassagens(Passagem *head) {
    FILE *file = fopen("passagens.txt", "w");
    if (file) {
        Passagem *atual = head;
        while (atual) {
            fprintf(file, "%s\n%s\n%.2f\n%d\n", atual->saida, atual->destino, atual->preco, atual->vagas);
            atual = atual->proximo;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

Passagem* carregarPassagens() {
    FILE *file = fopen("passagens.txt", "r");
    Passagem *head = NULL, *tail = NULL;
    if (file) {
        while (!feof(file)) {
            Passagem *nova = (Passagem *)malloc(sizeof(Passagem));
            if (fgets(nova->saida, sizeof(nova->saida), file)) {
                nova->saida[strcspn(nova->saida, "\n")] = '\0';
                fgets(nova->destino, sizeof(nova->destino), file);
                nova->destino[strcspn(nova->destino, "\n")] = '\0';
                fscanf(file, "%f\n%d\n", &nova->preco, &nova->vagas);
                nova->proximo = NULL;

                if (!head) {
                    head = nova;
                    tail = nova;
                } else {
                    tail->proximo = nova;
                    tail = nova;
                }
            } else {
                free(nova);
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
    return head;
}

void cadastrarPassagem(Passagem **head) {
    Passagem *nova = (Passagem *)malloc(sizeof(Passagem));
    printf("Digite o local de saída: ");
    fflush(stdin);
    scanf(" %[^\n]", nova->saida);
    printf("Digite o destino: ");
    fflush(stdin);
    scanf(" %[^\n]", nova->destino);
    printf("Digite o preço: ");
    scanf("%f", &nova->preco);
    printf("Digite a quantidade de vagas: ");
    scanf("%d", &nova->vagas);

    nova->proximo = *head;
    *head = nova;

    salvarPassagens(*head);
    printf("Passagem cadastrada com sucesso!\n");
}

void listarPassagens(Passagem *head) {
    Passagem *atual = head;
    while (atual) {
        printf("Saída: %s, Destino: %s, Preço: %.2f, Vagas: %d\n", atual->saida, atual->destino, atual->preco, atual->vagas);
        atual = atual->proximo;
    }
}

void editarPassagem(Passagem *head) {
    char saida[100];
    printf("Digite o local de saída da passagem a ser editada: ");
    fflush(stdin);
    scanf(" %[^\n]", saida);

    Passagem *atual = head;
    while (atual) {
        if (strcmp(atual->saida, saida) == 0) {
            printf("Novo destino (deixe em branco para não alterar): ");
            char novoDestino[100];
            fflush(stdin);
            scanf(" %[^\n]", novoDestino);
            if (strlen(novoDestino) > 0) {
                strcpy(atual->destino, novoDestino);
            }

            printf("Novo preço (deixe em branco para não alterar): ");
            float novoPreco;
            if (scanf("%f", &novoPreco) == 1) {
                atual->preco = novoPreco;
            }

            printf("Novas vagas (deixe em branco para não alterar): ");
            int novasVagas;
            if (scanf("%d", &novasVagas) == 1) {
                atual->vagas = novasVagas;
            }

            salvarPassagens(head);
            printf("Passagem editada com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Passagem não encontrada.\n");
}

void excluirPassagem(Passagem **head) {
    char saida[100];
    printf("Digite o local de saída da passagem a ser excluída: ");
    fflush(stdin);
    scanf(" %[^\n]", saida);

    Passagem *atual = *head;
    Passagem *anterior = NULL;

    while (atual) {
        if (strcmp(atual->saida, saida) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                *head = atual->proximo;
            }
            free(atual);
            salvarPassagens(*head);
            printf("Passagem excluída com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Passagem não encontrada.\n");
}