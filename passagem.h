#ifndef PASSAGEM_H
#define PASSAGEM_H

typedef struct Passagem {
    char saida[100];
    char destino[100];
    float preco;
    int vagas;
    struct Passagem *proximo; 
} Passagem;

void salvarPassagens(Passagem *head);
Passagem* carregarPassagens();
void cadastrarPassagem(Passagem **head);
void listarPassagens(Passagem *head);
void editarPassagem(Passagem *head);
void excluirPassagem(Passagem **head);

#endif