#ifndef USUARIO_H
#define USUARIO_H

typedef struct Usuario {
    char email[100];
    char senha[100];
    int isAdmin;
    struct Usuario *proximo; 
} Usuario;

void salvarUsuarios(Usuario *head);
Usuario* carregarUsuarios();
void cadastrar(Usuario **head);
void login(Usuario *head, int *indice, char *email);
void listarUsuarios(Usuario *head, int indiceUsuarioLogado);
void editar(Usuario *head);
void excluir(Usuario **head);

#endif 