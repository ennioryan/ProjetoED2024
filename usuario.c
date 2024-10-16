#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

void salvarUsuarios(Usuario *head) {
    FILE *file = fopen("usuarios.txt", "w");
    if (file) {
        Usuario *atual = head;
        while (atual) {
            fprintf(file, "%s\n%s\n%d\n", atual->email, atual->senha, atual->isAdmin);
            atual = atual->proximo;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

Usuario* carregarUsuarios() {
    FILE *file = fopen("usuarios.txt", "r");
    Usuario *head = NULL, *tail = NULL;
    if (file) {
        while (!feof(file)) {
            Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
            if (fgets(novo->email, sizeof(novo->email), file)) {
                novo->email[strcspn(novo->email, "\n")] = '\0';
                fgets(novo->senha, sizeof(novo->senha), file);
                novo->senha[strcspn(novo->senha, "\n")] = '\0';
                fscanf(file, "%d\n", &novo->isAdmin);
                novo->proximo = NULL;

                if (!head) {
                    head = novo;
                    tail = novo;
                } else {
                    tail->proximo = novo;
                    tail = novo;
                }
            } else {
                free(novo);
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
    return head;
}

void cadastrar(Usuario **head) {
    Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
    char email[100];
    printf("Digite o e-mail: ");
    fflush(stdin);
    scanf(" %[^\n]", email);

    Usuario *atual = *head;
    while (atual) {
        if (strcmp(atual->email, email) == 0) {
            printf("E-mail já cadastrado. Tente novamente.\n");
            free(novo);
            return;
        }
        atual = atual->proximo;
    }

    strcpy(novo->email, email);
    printf("Digite a senha: ");
    fflush(stdin);
    scanf(" %[^\n]", novo->senha);
    printf("É administrador? (1-Sim / 0-Não): ");
    scanf("%d", &novo->isAdmin);

    novo->proximo = *head;
    *head = novo;

    salvarUsuarios(*head);
    printf("Usuário cadastrado com sucesso!\n");
}

void login(Usuario *head, int *indice, char *email) {
    char senha[100];
    printf("Digite o e-mail: ");
    fflush(stdin);
    scanf(" %[^\n]", email);
    printf("Digite a senha: ");
    fflush(stdin);
    scanf(" %[^\n]", senha);

    Usuario *atual = head;
    *indice = -1;
    int i = 0;
    while (atual) {
        if (strcmp(atual->email, email) == 0 && strcmp(atual->senha, senha) == 0) {
            *indice = i;
            printf("Login bem-sucedido! Bem-vindo, %s.\n", atual->email);
            return;
        }
        atual = atual->proximo;
        i++;
    }
    printf("E-mail ou senha inválidos.\n");
}

void listarUsuarios(Usuario *head, int indiceUsuarioLogado) {
    Usuario *atual = head;
    while (atual) {
        printf("Usuário: %s, Administrador: %d\n", atual->email, atual->isAdmin);
        atual = atual->proximo;
    }
}

void editar(Usuario *head) {
    char email[100];
    printf("Digite o e-mail do usuário a ser editado: ");
    fflush(stdin);
    scanf(" %[^\n]", email);

    Usuario *atual = head;
    while (atual) {
        if (strcmp(atual->email, email) == 0) {
            printf("Novo e-mail (deixe em branco para não alterar): ");
            char novoEmail[100];
            fflush(stdin);
            scanf(" %[^\n]", novoEmail);
            if (strlen(novoEmail) > 0) {
                strcpy(atual->email, novoEmail);
            }

            printf("Nova senha (deixe em branco para não alterar): ");
            char novaSenha[100];
            fflush(stdin);
            scanf(" %[^\n]", novaSenha);
            if (strlen(novaSenha) > 0) {
                strcpy(atual->senha, novaSenha);
            }

            printf("Novo status de administrador (1-Sim / 0-Não, deixe em branco para não alterar): ");
            int novoAdmin;
            if (scanf("%d", &novoAdmin) == 1) {
                atual->isAdmin = novoAdmin;
            }

            salvarUsuarios(head);
            printf("Usuário editado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Usuário não encontrado.\n");
}

void excluir(Usuario **head) {
    char email[100];
    printf("Digite o e-mail do usuário a ser excluído: ");
    fflush(stdin);
    scanf(" %[^\n]", email);

    Usuario *atual = *head;
    Usuario *anterior = NULL;

    while (atual) {
        if (strcmp(atual->email, email) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                *head = atual->proximo;
            }
            free(atual);
            salvarUsuarios(*head);
            printf("Usuário excluído com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Usuário não encontrado.\n");
}