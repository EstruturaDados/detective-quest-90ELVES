#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------
// 1. ESTRUTURA DE DADOS
// -----------------------------------------------------------------------------

// Struct para representar cada sala/cômodo da mansão (Nó da Árvore Binária)
typedef struct Sala {
    char nome[50];          // Nome da sala (ex: Hall de Entrada, Biblioteca)
    struct Sala *esquerda;  // Ponteiro para o caminho à esquerda
    struct Sala *direita;   // Ponteiro para o caminho à direita
} Sala;

// -----------------------------------------------------------------------------
// PROTÓTIPOS DAS FUNÇÕES
// -----------------------------------------------------------------------------
Sala* criarSala(const char *nome);
void explorarSalas(Sala *inicio);
void liberarMemoria(Sala *raiz);
void limparBuffer(void);

// -----------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL (Montagem da Árvore e Início do Jogo)
// -----------------------------------------------------------------------------
int main() {
    /*
        Montagem manual do Mapa da Mansão (Estrutura da Árvore Binária):

                                [Hall de Entrada]
                                 /             \
                       [Biblioteca]           [Sítio do Jardim]
                        /        \             /           \
               [Sótão]   [Cozinha]   [Porão]    [Estufa]
    */

    // Criando a raiz da mansão
    Sala *hall = criarSala("Hall de Entrada");

    // Ramo da Esquerda
    hall->esquerda = criarSala("Biblioteca");
    hall->esquerda->esquerda = criarSala("Sótão Antigo");
    hall->esquerda->direita = criarSala("Cozinha Abandonada");

    // Ramo da Direita
    hall->direita = criarSala("Jardim de Inverno");
    hall->direita->esquerda = criarSala("Porão Secreto");
    hall->direita->direita = criarSala("Estufa de Plantas");

    printf("==================================================\n");
    printf("         DETECTIVE QUEST - MANSÃO ENIGMA          \n");
    printf("==================================================\n");
    printf("Bem-vindo, detetive! Explore a mansão para investigar os cômodos.\n\n");

    // Inicia a navegação interativa
    explorarSalas(hall);

    // Liberando a memória alocada dinamicamente
    liberarMemoria(hall);

    return 0;
}

// -----------------------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// -----------------------------------------------------------------------------

/**
 * Aloca dinamicamente uma nova sala no mapa da mansão.
 * @param nome Nome do cômodo a ser criado.
 * @return Ponteiro para a nova Sala criada.
 */
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*) malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("[ERRO] Falha ao alocar memória para a sala: %s\n", nome);
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/**
 * Controla a navegação interativa do jogador pela árvore binária da mansão.
 * @param atual Ponteiro para a sala onde o jogador se encontra.
 */
void explorarSalas(Sala *atual) {
    char opcao;

    while (atual != NULL) {
        printf("--------------------------------------------------\n");
        printf("Você está em: [%s]\n", atual->nome);

        // Caso base da exploração: Chegou a um nó-folha (fim do caminho)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n[FIM DO CAMINHO] Este cômodo não possui mais saídas.\n");
            printf("Investigação concluída neste setor da mansão!\n");
            break;
        }

        // Exibe as opções de caminhos disponíveis
        printf("\nCaminhos disponíveis:\n");
        if (atual->esquerda != NULL) {
            printf("  (e) Ir para a Esquerda: %s\n", atual->esquerda->nome);
        } else {
            printf("  (e) Caminho à esquerda bloqueado/inexistente.\n");
        }

        if (atual->direita != NULL) {
            printf("  (d) Ir para a Direita: %s\n", atual->direita->nome);
        } else {
            printf("  (d) Caminho à direita bloqueado/inexistente.\n");
        }

        printf("  (s) Sair da exploração\n");
        printf("\nEscolha sua ação (e/d/s): ");

        scanf(" %c", &opcao);
        limparBuffer();

        if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\n[AVISO] Não há caminho para a esquerda a partir daqui!\n");
            }
        } else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\n[AVISO] Não há caminho para a direita a partir daqui!\n");
            }
        } else if (opcao == 's' || opcao == 'S') {
            printf("\nExploração interrompida pelo detetive.\n");
            break;
        } else {
            printf("\n[OPÇÃO INVÁLIDA] Digite 'e' para esquerda, 'd' para direita ou 's' para sair.\n");
        }
    }
}

/**
 * Função recursiva (Pós-Ordem) para desalocar com segurança a memória de todas as salas.
 * @param raiz Ponteiro para a sala inicial.
 */
void liberarMemoria(Sala *raiz) {
    if (raiz != NULL) {
        liberarMemoria(raiz->esquerda);
        liberarMemoria(raiz->direita);
        free(raiz);
    }
}

/**
 * Utilitário para limpar o buffer do teclado após o scanf.
 */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}