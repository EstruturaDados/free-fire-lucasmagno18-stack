#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_JOGADORES 100
#define TAM_NOME 50

typedef struct {
    char nome[TAM_NOME];
    int pontuacao;
    int posicao;
} Jogador;

// Estrutura para lista encadeada
typedef struct No {
    Jogador jogador;
    struct No* proximo;
} No;

// Variáveis globais
Jogador rankingVetor[MAX_JOGADORES];
No* rankingLista = NULL;
int totalJogadores = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\nPressione Enter para continuar....");
    limparBuffer();
}

// =========== FUNÇÕES BÁSICAS ===========

void cadastrarJogador() {
    if (totalJogadores >= MAX_JOGADORES) {
        printf("Limite máximo de jogadores atingido!\n");
        return;
    }
    
    printf("\n--- NOVO JOGADOR ---\n");
    
    printf("Nome: ");
    fgets(rankingVetor[totalJogadores].nome, TAM_NOME, stdin);
    rankingVetor[totalJogadores].nome[strcspn(rankingVetor[totalJogadores].nome, "\n")] = '\0';
    
    printf("Pontuação: ");
    scanf("%d", &rankingVetor[totalJogadores].pontuacao);
    limparBuffer();
    
    totalJogadores++;
    printf("Jogador cadastrado com sucesso!\n");
}

void ordenarRanking() {
    // Ordenação simples por pontuação (decrescente)
    for (int i = 0; i < totalJogadores - 1; i++) {
        for (int j = i + 1; j < totalJogadores; j++) {
            if (rankingVetor[i].pontuacao < rankingVetor[j].pontuacao) {
                Jogador temp = rankingVetor[i];
                rankingVetor[i] = rankingVetor[j];
                rankingVetor[j] = temp;
            }
        }
    }
    
    // Atualizar posições
    for (int i = 0; i < totalJogadores; i++) {
        rankingVetor[i].posicao = i + 1;
    }
}

void mostrarRanking() {
    ordenarRanking();
    
    printf("\n🏆 RANKING OFICIAL 🏆\n");
    printf("=====================\n");
    
    if (totalJogadores == 0) {
        printf("Nenhum jogador cadastrado ainda.\n");
        return;
    }
    
    for (int i = 0; i < totalJogadores; i++) {
        char medalha[10] = "";
        if (i == 0) strcpy(medalha, "🥇");
        else if (i == 1) strcpy(medalha, "🥈");
        else if (i == 2) strcpy(medalha, "🥉");
        
        printf("%s %d. %s - %d pontos\n", 
               medalha, rankingVetor[i].posicao, 
               rankingVetor[i].nome, rankingVetor[i].pontuacao);
    }
}

void removerJogador() {
    if (totalJogadores == 0) {
        printf("Não há jogadores para remover!\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\nDigite o nome do jogador a remover: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    int encontrado = -1;
    for (int i = 0; i < totalJogadores; i++) {
        if (strcmp(rankingVetor[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado == -1) {
        printf("Jogador não encontrado!\n");
        return;
    }
    
    // Remove deslocando os elementos
    for (int i = encontrado; i < totalJogadores - 1; i++) {
        rankingVetor[i] = rankingVetor[i + 1];
    }
    
    totalJogadores--;
    printf("Jogador removido com sucesso!\n");
}

// ========== ALGORITMOS DE BUSCA ==========

void buscaSequencial() {
    if (totalJogadores == 0) {
        printf("Não há jogadores cadastrados!\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("Digite o nome para busca sequencial: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    clock_t inicio = clock();
    int encontrados = 0;
    
    printf("\n🔍 BUSCA SEQUENCIAL:\n");
    for (int i = 0; i < totalJogadores; i++) {
        if (strstr(rankingVetor[i].nome, nome) != NULL) {
            printf("✓ %s - %d pontos (Posição: %d)\n", 
                   rankingVetor[i].nome, rankingVetor[i].pontuacao, rankingVetor[i].posicao);
            encontrados++;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("Tempo: %.4f ms | Encontrados: %d\n", tempo, encontrados);
}

int buscaBinariaRecursiva(int inicio, int fim, char* nome) {
    if (inicio > fim) return -1;
    
    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(rankingVetor[meio].nome, nome);
    
    if (comparacao == 0) return meio;
    if (comparacao < 0) return buscaBinariaRecursiva(meio + 1, fim, nome);
    return buscaBinariaRecursiva(inicio, meio - 1, nome);
}

void buscaBinariaIterativa() {
    if (totalJogadores == 0) {
        printf("Não há jogadores cadastrados!\n");
        return;
    }
    
    // Ordenar por nome para busca binária
    for (int i = 0; i < totalJogadores - 1; i++) {
        for (int j = i + 1; j < totalJogadores; j++) {
            if (strcmp(rankingVetor[i].nome, rankingVetor[j].nome) > 0) {
                Jogador temp = rankingVetor[i];
                rankingVetor[i] = rankingVetor[j];
                rankingVetor[j] = temp;
            }
        }
    }
    
    char nome[TAM_NOME];
    printf("Digite o nome exato para busca binária: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    clock_t inicio = clock();
    
    int esquerda = 0, direita = totalJogadores - 1;
    int encontrado = -1;
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int comparacao = strcmp(rankingVetor[meio].nome, nome);
        
        if (comparacao == 0) {
            encontrado = meio;
            break;
        }
        if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n🔍 BUSCA BINÁRIA ITERATIVA:\n");
    if (encontrado != -1) {
        printf("✓ %s - %d pontos\n", 
               rankingVetor[encontrado].nome, rankingVetor[encontrado].pontuacao);
    } else {
        printf("Jogador não encontrado.\n");
    }
    printf("Tempo: %.4f ms\n", tempo);
}

// ========== COMPARAÇÃO DE ESTRUTURAS ==========

void compararEstruturas() {
    printf("\n📊 COMPARAÇÃO DE ESTRUTURAS\n");
    printf("===========================\n");
    
    printf("VETOR:\n");
    printf("- Vantagens: Acesso rápido por índice, cache-friendly\n");
    printf("- Desvantagens: Tamanho fixo, inserção/remoção custosa\n");
    printf("- Uso ideal: Quando há muitas buscas e poucas modificações\n\n");
    
    printf("LISTA ENCADEADA:\n");
    printf("- Vantagens: Tamanho dinâmico, inserção/remoção eficiente\n");
    printf("- Desvantagens: Acesso sequencial, overhead de ponteiros\n");
    printf("- Uso ideal: Quando há muitas inserções/remoções\n");
}

void testeDesempenho() {
    if (totalJogadores < 3) {
        printf("Cadastre pelo menos 3 jogadores para o teste de desempenho.\n");
        return;
    }
    
    printf("\n⚡ TESTE DE DESEMPENHO\n");
    printf("=====================\n");
    
    // Teste busca sequencial
    clock_t inicioSeq = clock();
    for (int i = 0; i < 1000; i++) {
        // Busca fictícia para teste
        for (int j = 0; j < totalJogadores; j++) {
            if (strlen(rankingVetor[j].nome) > 0) {
                // Simula operação de busca
            }
        }
    }
    clock_t fimSeq = clock();
    
    // Teste busca binária
    clock_t inicioBin = clock();
    for (int i = 0; i < 1000; i++) {
        int esq = 0, dir = totalJogadores - 1;
        while (esq <= dir) {
            int meio = (esq + dir) / 2;
            esq = meio + 1; // Simulação simplificada
        }
    }
    clock_t fimBin = clock();
    
    double tempoSeq = ((double)(fimSeq - inicioSeq)) / CLOCKS_PER_SEC * 1000;
    double tempoBin = ((double)(fimBin - inicioBin)) / CLOCKS_PER_SEC * 1000;
    
    printf("Busca Sequencial (1000 iterações): %.2f ms\n", tempoSeq);
    printf("Busca Binária (1000 iterações): %.2f ms\n", tempoBin);
    printf("Diferença: %.2f ms\n", tempoSeq - tempoBin);
    
    if (tempoBin < tempoSeq) {
        printf("✅ Busca binária foi mais rápida!\n");
    } else {
        printf("⚠️  Busca sequencial foi mais rápida (poucos dados)\n");
    }
}

void menuPrincipal() {
    printf("\n🎮 SISTEMA DE RANKING - CAMPEONATO ONLINE 🎮\n");
    printf("1. Cadastrar jogador\n");
    printf("2. Ver ranking\n");
    printf("3. Remover jogador\n");
    printf("4. Busca sequencial (por nome)\n");
    printf("5. Busca binária iterativa\n");
    printf("6. Comparar estruturas\n");
    printf("7. Teste de desempenho\n");
    printf("8. Sair\n");
    printf("Escolha: ");
}

int main() {
    printf("Bem-vindo ao Sistema de Gerenciamento de Ranking!\n");
    printf("Organize os melhores jogadores do campeonato...\n");
    
    int opcao;
    
    // Dados de exemplo
    strcpy(rankingVetor[0].nome, "Ana_Silva");
    rankingVetor[0].pontuacao = 2850;
    strcpy(rankingVetor[1].nome, "Bruno_Santos");
    rankingVetor[1].pontuacao = 3120;
    strcpy(rankingVetor[2].nome, "Carlos_Oliveira");
    rankingVetor[2].pontuacao = 2980;
    totalJogadores = 3;
    ordenarRanking();
    
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: cadastrarJogador(); break;
            case 2: mostrarRanking(); break;
            case 3: removerJogador(); break;
            case 4: buscaSequencial(); break;
            case 5: buscaBinariaIterativa(); break;
            case 6: compararEstruturas(); break;
            case 7: testeDesempenho(); break;
            case 8: printf("Encerrando sistema... Até a próxima!\n"); break;
            default: printf("Opção inválida!\n");
        }
        
        if (opcao != 8) pausar();
        
    } while (opcao != 8);
    
    return 0;
}