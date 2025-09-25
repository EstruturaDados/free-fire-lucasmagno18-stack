#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 20
#define TAM_NOME 30
#define TAM_TIPO 20

// Estrutura base do item
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Contadores globais para comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ========== IMPLEMENTAÇÃO COM VETOR ==========

Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("❌ Mochila (vetor) cheia! Limite: %d itens\n", MAX_ITENS);
        return;
    }
    
    printf("\n📦 ADICIONAR ITEM - VETOR\n");
    printf("Nome: ");
    fgets(mochilaVetor[totalItensVetor].nome, TAM_NOME, stdin);
    mochilaVetor[totalItensVetor].nome[strcspn(mochilaVetor[totalItensVetor].nome, "\n")] = '\0';
    
    printf("Tipo (arma, municao, cura, ferramenta): ");
    fgets(mochilaVetor[totalItensVetor].tipo, TAM_TIPO, stdin);
    mochilaVetor[totalItensVetor].tipo[strcspn(mochilaVetor[totalItensVetor].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    limparBuffer();
    
    totalItensVetor++;
    printf("✅ Item adicionado ao vetor! Total: %d/%d\n", totalItensVetor, MAX_ITENS);
}

void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("❌ Mochila (vetor) vazia!\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n🗑️  REMOVER ITEM - VETOR\n");
    printf("Nome do item a remover: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    int posicao = -1;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("❌ Item não encontrado no vetor!\n");
        return;
    }
    
    // Remove deslocando os elementos
    for (int i = posicao; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    
    totalItensVetor--;
    printf("✅ Item removido do vetor! Total: %d/%d\n", totalItensVetor, MAX_ITENS);
}

void listarItensVetor() {
    printf("\n🎒 MOCHILA (VETOR) - %d itens\n", totalItensVetor);
    printf("================================\n");
    
    if (totalItensVetor == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d. %-15s | %-12s | Qtd: %d\n", 
               i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    if (totalItensVetor < 2) {
        printf("ℹ️  Poucos itens para ordenar\n");
        return;
    }
    
    // Bubble Sort por nome
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    printf("✅ Vetor ordenado por nome!\n");
}

int buscarSequencialVetor(char* nome) {
    comparacoesSequencial = 0;
    
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarBinariaVetor(char* nome) {
    comparacoesBinaria = 0;
    int esquerda = 0, direita = totalItensVetor - 1;
    
    while (esquerda <= direita) {
        comparacoesBinaria++;
        int meio = (esquerda + direita) / 2;
        int resultado = strcmp(mochilaVetor[meio].nome, nome);
        
        if (resultado == 0) return meio;
        if (resultado < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

// ========== IMPLEMENTAÇÃO COM LISTA ENCADEADA ==========

No* mochilaLista = NULL;
int totalItensLista = 0;

void inserirItemLista() {
    if (totalItensLista >= MAX_ITENS) {
        printf("❌ Mochila (lista) cheia! Limite: %d itens\n", MAX_ITENS);
        return;
    }
    
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("❌ Erro de memória!\n");
        return;
    }
    
    printf("\n📦 ADICIONAR ITEM - LISTA\n");
    printf("Nome: ");
    fgets(novoNo->dados.nome, TAM_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';
    
    printf("Tipo (arma, municao, cura, ferramenta): ");
    fgets(novoNo->dados.tipo, TAM_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limparBuffer();
    
    // Insere no início (mais eficiente)
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;
    totalItensLista++;
    
    printf("✅ Item adicionado à lista! Total: %d/%d\n", totalItensLista, MAX_ITENS);
}

void removerItemLista() {
    if (totalItensLista == 0) {
        printf("❌ Mochila (lista) vazia!\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n🗑️  REMOVER ITEM - LISTA\n");
    printf("Nome do item a remover: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    No* atual = mochilaLista;
    No* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                // Remove do início
                mochilaLista = atual->proximo;
            } else {
                // Remove do meio/fim
                anterior->proximo = atual->proximo;
            }
            
            free(atual);
            totalItensLista--;
            printf("✅ Item removido da lista! Total: %d/%d\n", totalItensLista, MAX_ITENS);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("❌ Item não encontrado na lista!\n");
}

void listarItensLista() {
    printf("\n🎒 MOCHILA (LISTA ENCADEADA) - %d itens\n", totalItensLista);
    printf("======================================\n");
    
    if (totalItensLista == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    No* atual = mochilaLista;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("%d. %-15s | %-12s | Qtd: %d\n", 
               posicao, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        posicao++;
    }
}

int buscarSequencialLista(char* nome) {
    comparacoesSequencial = 0;
    No* atual = mochilaLista;
    int posicao = 0;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return posicao;
        }
        atual = atual->proximo;
        posicao++;
    }
    return -1;
}

// ========== COMPARAÇÃO DE DESEMPENHO ==========

void testarBuscaSequencial() {
    if (totalItensVetor == 0) {
        printf("❌ Adicione itens ao vetor primeiro!\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n🔍 TESTE BUSCA SEQUENCIAL\n");
    printf("Nome para buscar: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    // Teste no vetor
    clock_t inicio = clock();
    int posVetor = buscarSequencialVetor(nome);
    clock_t fim = clock();
    double tempoVetor = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    // Teste na lista
    inicio = clock();
    int posLista = buscarSequencialLista(nome);
    fim = clock();
    double tempoLista = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n📊 RESULTADOS BUSCA SEQUENCIAL\n");
    printf("VETOR: %d comparações | %.4f ms | ", comparacoesSequencial, tempoVetor);
    printf(posVetor != -1 ? "Encontrado na posição %d\n" : "Não encontrado\n", posVetor + 1);
    
    printf("LISTA: %d comparações | %.4f ms | ", comparacoesSequencial, tempoLista);
    printf(posLista != -1 ? "Encontrado na posição %d\n" : "Não encontrado\n", posLista + 1);
}

void testarBuscaBinaria() {
    if (totalItensVetor == 0) {
        printf("❌ Adicione itens ao vetor primeiro!\n");
        return;
    }
    
    if (totalItensVetor < 2) {
        printf("ℹ️  Adicione mais itens para testar busca binária\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n🔍 TESTE BUSCA BINÁRIA (apenas vetor)\n");
    printf("Nome para buscar: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    // Ordena primeiro
    ordenarVetor();
    
    // Teste busca sequencial
    clock_t inicioSeq = clock();
    int posSeq = buscarSequencialVetor(nome);
    clock_t fimSeq = clock();
    double tempoSeq = ((double)(fimSeq - inicioSeq)) / CLOCKS_PER_SEC * 1000;
    
    // Teste busca binária
    clock_t inicioBin = clock();
    int posBin = buscarBinariaVetor(nome);
    clock_t fimBin = clock();
    double tempoBin = ((double)(fimBin - inicioBin)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n📊 COMPARAÇÃO BUSCA SEQUENCIAL vs BINÁRIA\n");
    printf("SEQUENCIAL: %d comparações | %.4f ms | ", comparacoesSequencial, tempoSeq);
    printf(posSeq != -1 ? "Encontrado\n" : "Não encontrado\n");
    
    printf("BINÁRIA:    %d comparações | %.4f ms | ", comparacoesBinaria, tempoBin);
    printf(posBin != -1 ? "Encontrado\n" : "Não encontrado\n");
    
    if (posBin != -1) {
        printf("🎯 Busca binária foi %dx mais eficiente!\n", 
               comparacoesSequencial / (comparacoesBinaria > 0 ? comparacoesBinaria : 1));
    }
}

void compararEstruturas() {
    printf("\n📈 ANÁLISE COMPARATIVA DAS ESTRUTURAS\n");
    printf("====================================\n");
    
    printf("\n🏆 VETOR (Lista Sequencial):\n");
    printf("✅ Vantagens:\n");
    printf("   - Acesso rápido por índice (O(1))\n");
    printf("   - Cache-friendly (dados contíguos)\n");
    printf("   - Busca binária possível após ordenação\n");
    printf("❌ Desvantagens:\n");
    printf("   - Tamanho fixo\n");
    printf("   - Inserção/remoção custosa (O(n))\n");
    printf("   - Redimensionamento complexo\n");
    
    printf("\n🏆 LISTA ENCADEADA:\n");
    printf("✅ Vantagens:\n");
    printf("   - Tamanho dinâmico\n");
    printf("   - Inserção/remoção eficiente (O(1) no início)\n");
    printf("   - Não precisa realocação\n");
    printf("❌ Desvantagens:\n");
    printf("   - Acesso sequencial (O(n))\n");
    printf("   - Overhead de memória (ponteiros)\n");
    printf("   - Não permite busca binária\n");
    
    printf("\n💡 RECOMENDAÇÃO:\n");
    printf("Use VETOR quando: Muitas buscas, poucas inserções/remoções\n");
    printf("Use LISTA quando: Muitas inserções/remoções, poucas buscas\n");
}

// ========== MENUS E INTERFACE ==========

void menuVetor() {
    int opcao;
    do {
        printf("\n🎒 SISTEMA DE MOCHILA - VETOR\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar por nome\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: printf("Voltando...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 5);
}

void menuLista() {
    int opcao;
    do {
        printf("\n🎒 SISTEMA DE MOCHILA - LISTA ENCADEADA\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: printf("Voltando...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while (opcao != 5);
}

void menuPrincipal() {
    printf("\n🚀 SISTEMA DE COMPARAÇÃO - VETOR vs LISTA ENCADEADA\n");
    printf("==================================================\n");
    printf("1. Trabalhar com VETOR\n");
    printf("2. Trabalhar com LISTA ENCADEADA\n");
    printf("3. Testar busca sequencial (ambas estruturas)\n");
    printf("4. Testar busca binária vs sequencial (vetor)\n");
    printf("5. Comparar estruturas (análise teórica)\n");
    printf("6. Sair\n");
    printf("Escolha: ");
}

int main() {
    printf("Bem-vindo ao Sistema de Comparação de Estruturas!\n");
    printf("Analise o desempenho de vetores vs listas encadeadas...\n");
    
    // Adiciona alguns itens de exemplo
    strcpy(mochilaVetor[0].nome, "Rifle");
    strcpy(mochilaVetor[0].tipo, "arma");
    mochilaVetor[0].quantidade = 1;
    totalItensVetor++;
    
    strcpy(mochilaVetor[1].nome, "Balas");
    strcpy(mochilaVetor[1].tipo, "municao");
    mochilaVetor[1].quantidade = 30;
    totalItensVetor++;
    
    strcpy(mochilaVetor[2].nome, "Kit Cura");
    strcpy(mochilaVetor[2].tipo, "cura");
    mochilaVetor[2].quantidade = 2;
    totalItensVetor++;
    
    int opcao;
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 3: testarBuscaSequencial(); break;
            case 4: testarBuscaBinaria(); break;
            case 5: compararEstruturas(); break;
            case 6: printf("Encerrando sistema...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
        
        if (opcao != 6) {
            printf("\nPressione Enter para continuar...");
            limparBuffer();
        }
        
    } while (opcao != 6);
    
    // Libera memória da lista
    No* atual = mochilaLista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    return 0;
}