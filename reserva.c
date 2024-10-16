#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"

void salvarReservas(Reserva *head) {
    FILE *file = fopen("reservas.txt", "w");
    if (file) {
        Reserva *atual = head;
        while (atual) {
            fprintf(file, "%s\n%s\n%s\n", atual->email, atual->saida, atual->destino);
            atual = atual->proximo;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

Reserva* carregarReservas() {
    FILE *file = fopen("reservas.txt", "r");
    Reserva *head = NULL, *tail = NULL;
    if (file) {
        while (!feof(file)) {
            Reserva *nova = (Reserva *)malloc(sizeof(Reserva));
            if (fgets(nova->email, sizeof(nova->email), file)) {
                nova->email[strcspn(nova->email, "\n")] = '\0';
                fgets(nova->saida, sizeof(nova->saida), file);
                nova->saida[strcspn(nova->saida, "\n")] = '\0';
                fgets(nova->destino, sizeof(nova->destino), file);
                nova->destino[strcspn(nova->destino, "\n")] = '\0';
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

void reservar(Reserva **head, const char *email, const char *saida, const char *destino) {
    Reserva *nova = (Reserva *)malloc(sizeof(Reserva));
    strcpy(nova->email, email);
    strcpy(nova->saida, saida);
    strcpy(nova->destino, destino);
    nova->proximo = *head;
    *head = nova;

    salvarReservas(*head);
    printf("Reserva feita com sucesso!\n");
}

void listarReservas(Reserva *head, const char *email) {
    Reserva *atual = head;
    printf("Reservas para %s:\n", email);
    while (atual) {
        if (strcmp(atual->email, email) == 0) {
            printf("Saída: %s, Destino: %s\n", atual->saida, atual->destino);
        }
        atual = atual->proximo;
    }
}

void excluirReserva(Reserva **head, const char *email) {
    Reserva *atual = *head;
    Reserva *anterior = NULL;

    while (atual) {
        if (strcmp(atual->email, email) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                *head = atual->proximo;
            }
            free(atual);
            salvarReservas(*head);
            printf("Reserva excluída com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Reserva não encontrada.\n");
}