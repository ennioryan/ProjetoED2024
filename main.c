#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "passagem.h"
#include "reserva.h"

int main() {
    Usuario *usuarios = carregarUsuarios();
    Passagem *passagens = carregarPassagens();
    Reserva *reservas = carregarReservas();
    
    int opcao, indiceUsuarioLogado = -1;
    char email[100];

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Login\n");
        printf("3. Listar Usuários\n");
        printf("4. Editar Usuário\n");
        printf("5. Excluir Usuário\n");
        printf("6. Cadastrar Passagem\n");
        printf("7. Listar Passagens\n");
        printf("8. Editar Passagem\n");
        printf("9. Excluir Passagem\n");
        printf("10. Reservar Passagem\n");
        printf("11. Listar Reservas\n");
        printf("12. Excluir Reserva\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(&usuarios);
                break;
            case 2:
                login(usuarios, &indiceUsuarioLogado, email);
                break;
            case 3:
                listarUsuarios(usuarios, indiceUsuarioLogado);
                break;
            case 4:
                editar(usuarios);
                break;
            case 5:
                excluir(&usuarios);
                break;
            case 6:
                cadastrarPassagem(&passagens);
                break;
            case 7:
                listarPassagens(passagens);
                break;
            case 8:
                editarPassagem(passagens);
                break;
            case 9:
                excluirPassagem(&passagens);
                break;
            case 10:
                if (indiceUsuarioLogado >= 0) {
                    char saida[100], destino[100];
                    printf("Digite a saída: ");
                    fflush(stdin);
                    scanf(" %[^\n]", saida);
                    printf("Digite o destino: ");
                    fflush(stdin);
                    scanf(" %[^\n]", destino);
                    reservar(&reservas, email, saida, destino);
                } else {
                    printf("Faça login para reservar uma passagem.\n");
                }
                break;
            case 11:
                if (indiceUsuarioLogado >= 0) {
                    listarReservas(reservas, email);
                } else {
                    printf("Faça login para listar suas reservas.\n");
                }
                break;
            case 12:
                if (indiceUsuarioLogado >= 0) {
                    excluirReserva(&reservas, email);
                } else {
                    printf("Faça login para excluir uma reserva.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Libere a memória antes de sair
    while (usuarios) {
        Usuario *temp = usuarios;
        usuarios = usuarios->proximo;
        free(temp);
    }
    while (passagens) {
        Passagem *temp = passagens;
        passagens = passagens->proximo;
        free(temp);
    }
    while (reservas) {
        Reserva *temp = reservas;
        reservas = reservas->proximo;
        free(temp);
    }

    return 0;
}