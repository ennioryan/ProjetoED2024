#ifndef RESERVA_H
#define RESERVA_H

typedef struct Reserva {
    char email[100];
    char saida[100];
    char destino[100];
    struct Reserva *proximo; 
} Reserva;

void salvarReservas(Reserva *head);
Reserva* carregarReservas();
void reservar(Reserva **head, const char *email, const char *saida, const char *destino);
void listarReservas(Reserva *head, const char *email);
void excluirReserva(Reserva **head, const char *email);

#endif 