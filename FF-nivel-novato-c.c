#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// Estrutura para representar cada item da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Variável global para controlar quantos itens temos
int totalItens = 0;
Item mochila[MAX_ITENS];

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Mostra todos os itens da mochila
void mostrarInventario() {
    printf("\n=== MOCHILA ===\n");
    
    if (totalItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }
    
    for (int i = 0; i < totalItens; i++) {
        printf("%d. %s | Tipo: %s | Quantidade: %d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("Total de itens: %d/10\n", totalItens);
}

// Adiciona um novo item à mochila
void adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Remova alguns itens antes de adicionar novos.\n");
        return;
    }
    
    printf("\n--- Novo Item ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, TAM_NOME, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';
    
    printf("Tipo (arma, municao, cura, ferramenta): ");
    fgets(mochila[totalItens].tipo, TAM_TIPO, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();
    
    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

// Remove um item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("Não há itens para remover!\n");
        return;
    }
    
    char nomeBusca[TAM_NOME];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int encontrado = -1;
    
    // Procura o item
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado == -1) {
        printf("Item não encontrado na mochila!\n");
        return;
    }
    
    // Mostra o item que será removido
    printf("Removendo: %s (%s) - Quantidade: %d\n", 
           mochila[encontrado].nome, mochila[encontrado].tipo, mochila[encontrado].quantidade);
    
    // Move os itens posteriores uma posição para frente
    for (int i = encontrado; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    totalItens--;
    printf("Item removido com sucesso!\n");
}

// Busca um item específico
void buscarItem() {
    if (totalItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }
    
    char nomeBusca[TAM_NOME];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int encontrou = 0;
    
    for (int i = 0; i < totalItens; i++) {
        if (strstr(mochila[i].nome, nomeBusca) != NULL) {
            printf("✓ Encontrado: %s | Tipo: %s | Quantidade: %d\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhum item encontrado com esse nome.\n");
    }
}

// Menu principal
void mostrarMenu() {
    printf("\n🎒 SISTEMA DE INVENTÁRIO - SOBREVIVÊNCIA 🎒\n");
    printf("1. Mostrar mochila\n");
    printf("2. Adicionar item\n");
    printf("3. Remover item\n");
    printf("4. Buscar item\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    printf("Bem-vindo ao sistema de gerenciamento de inventário!\n");
    printf("Organize seus recursos para sobreviver...\n");
    
    int opcao;
    
    do {
        mostrarMenu();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                mostrarInventario();
                break;
            case 2:
                adicionarItem();
                break;
            case 3:
                removerItem();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo... Boa sorte na sobrevivência!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        
    } while (opcao != 5);
    
    return 0;
}