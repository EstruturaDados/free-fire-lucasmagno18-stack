#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// Estrutura do componente para a torre de resgate
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade; // 1-10 (1 = mais importante)
} Componente;

// Variáveis globais
Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;
int comparacoes = 0;
int trocas = 0;

// Componente chave para ativação da torre
const char COMPONENTE_CHAVE[] = "chip central";

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\n⏎ Pressione Enter para continuar...");
    limparBuffer();
}

// ========== FUNÇÕES DE ENTRADA DE DADOS ==========

void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("❌ Limite máximo de %d componentes atingido!\n", MAX_COMPONENTES);
        return;
    }
    
    printf("\n🔧 NOVO COMPONENTE DA TORRE\n");
    printf("===========================\n");
    
    printf("Nome do componente: ");
    fgets(componentes[totalComponentes].nome, TAM_NOME, stdin);
    componentes[totalComponentes].nome[strcspn(componentes[totalComponentes].nome, "\n")] = '\0';
    
    printf("Tipo (controle, suporte, propulsao, energia): ");
    fgets(componentes[totalComponentes].tipo, TAM_TIPO, stdin);
    componentes[totalComponentes].tipo[strcspn(componentes[totalComponentes].tipo, "\n")] = '\0';
    
    printf("Prioridade (1-10, onde 1 é mais importante): ");
    scanf("%d", &componentes[totalComponentes].prioridade);
    limparBuffer();
    
    // Validação da prioridade
    if (componentes[totalComponentes].prioridade < 1) {
        componentes[totalComponentes].prioridade = 1;
    } else if (componentes[totalComponentes].prioridade > 10) {
        componentes[totalComponentes].prioridade = 10;
    }
    
    totalComponentes++;
    printf("✅ Componente cadastrado! Total: %d/%d\n", totalComponentes, MAX_COMPONENTES);
}

void cadastrarComponentesExemplo() {
    // Componentes pré-definidos para testes
    Componente exemplos[] = {
        {"chip central", "controle", 1},
        {"gerador principal", "energia", 2},
        {"propulsor vertical", "propulsao", 3},
        {"estabilizador", "suporte", 4},
        {"bateria reserva", "energia", 5},
        {"painel controle", "controle", 2},
        {"base metalica", "suporte", 6},
        {"tubo combustivel", "propulsao", 3}
    };
    
    int totalExemplos = sizeof(exemplos) / sizeof(exemplos[0]);
    
    for (int i = 0; i < totalExemplos && totalComponentes < MAX_COMPONENTES; i++) {
        componentes[totalComponentes] = exemplos[i];
        totalComponentes++;
    }
    
    printf("✅ %d componentes de exemplo adicionados!\n", totalExemplos);
}

// ========== ALGORITMOS DE ORDENAÇÃO ==========

void bubbleSortPorNome() {
    if (totalComponentes < 2) {
        printf("ℹ️  Poucos componentes para ordenar\n");
        return;
    }
    
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    // Bubble Sort - compara elementos adjacentes
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os elementos
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n🔄 BUBBLE SORT (por nome) - RESULTADO:\n");
    printf("Comparações: %d | Trocas: %d | Tempo: %.3f ms\n", comparacoes, trocas, tempo);
}

void insertionSortPorTipo() {
    if (totalComponentes < 2) {
        printf("ℹ️  Poucos componentes para ordenar\n");
        return;
    }
    
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    // Insertion Sort - insere cada elemento na posição correta
    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n🔄 INSERTION SORT (por tipo) - RESULTADO:\n");
    printf("Comparações: %d | Trocas: %d | Tempo: %.3f ms\n", comparacoes, trocas, tempo);
}

void selectionSortPorPrioridade() {
    if (totalComponentes < 2) {
        printf("ℹ️  Poucos componentes para ordenar\n");
        return;
    }
    
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    // Selection Sort - seleciona o menor elemento a cada iteração
    for (int i = 0; i < totalComponentes - 1; i++) {
        int menor_idx = i;
        
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[menor_idx].prioridade) {
                menor_idx = j;
            }
        }
        
        if (menor_idx != i) {
            // Troca os elementos
            Componente temp = componentes[i];
            componentes[i] = componentes[menor_idx];
            componentes[menor_idx] = temp;
            trocas++;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("\n🔄 SELECTION SORT (por prioridade) - RESULTADO:\n");
    printf("Comparações: %d | Trocas: %d | Tempo: %.3f ms\n", comparacoes, trocas, tempo);
}

// ========== BUSCA BINÁRIA ==========

int buscaBinariaPorNome(char* nomeAlvo) {
    if (totalComponentes == 0) {
        printf("❌ Nenhum componente para buscar!\n");
        return -1;
    }
    
    // Verifica se o vetor está ordenado por nome
    int ordenado = 1;
    for (int i = 0; i < totalComponentes - 1; i++) {
        if (strcmp(componentes[i].nome, componentes[i + 1].nome) > 0) {
            ordenado = 0;
            break;
        }
    }
    
    if (!ordenado) {
        printf("⚠️  AVISO: Vetor não está ordenado por nome. Ordenando com Bubble Sort...\n");
        bubbleSortPorNome();
    }
    
    comparacoes = 0;
    clock_t inicio = clock();
    
    int esquerda = 0;
    int direita = totalComponentes - 1;
    
    while (esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(componentes[meio].nome, nomeAlvo);
        
        if (resultado == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            printf("🔍 BUSCA BINÁRIA: %d comparações | %.3f ms\n", comparacoes, tempo);
            return meio;
        }
        
        if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("🔍 BUSCA BINÁRIA: %d comparações | %.3f ms | Não encontrado\n", comparacoes, tempo);
    return -1;
}

// ========== VISUALIZAÇÃO E RELATÓRIOS ==========

void mostrarComponentes() {
    printf("\n🏗️  COMPONENTES DA TORRE - %d/%d\n", totalComponentes, MAX_COMPONENTES);
    printf("================================\n");
    
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    
    for (int i = 0; i < totalComponentes; i++) {
        char indicador[10] = "";
        if (strcmp(componentes[i].nome, COMPONENTE_CHAVE) == 0) {
            strcpy(indicador, "🔑");
        }
        
        printf("%s %2d. %-20s | %-12s | Prioridade: %d\n", 
               indicador, i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

void analisarDesempenho() {
    if (totalComponentes < 3) {
        printf("❌ Cadastre pelo menos 3 componentes para análise\n");
        return;
    }
    
    printf("\n📊 ANÁLISE DE DESEMPENHO DOS ALGORITMOS\n");
    printf("======================================\n");
    
    // Faz backup dos dados originais
    Componente backup[MAX_COMPONENTES];
    int backupTotal = totalComponentes;
    memcpy(backup, componentes, sizeof(componentes));
    
    // Testa cada algoritmo
    printf("\n1. BUBBLE SORT (Nome):\n");
    bubbleSortPorNome();
    
    // Restaura dados
    totalComponentes = backupTotal;
    memcpy(componentes, backup, sizeof(componentes));
    
    printf("\n2. INSERTION SORT (Tipo):\n");
    insertionSortPorTipo();
    
    // Restaura dados
    totalComponentes = backupTotal;
    memcpy(componentes, backup, sizeof(componentes));
    
    printf("\n3. SELECTION SORT (Prioridade):\n");
    selectionSortPorPrioridade();
    
    // Restaura dados originais
    totalComponentes = backupTotal;
    memcpy(componentes, backup, sizeof(componentes));
    
    printf("\n💡 CONCLUSÃO:\n");
    printf("• Bubble Sort: Simples mas lento para muitos dados\n");
    printf("• Insertion Sort: Eficiente para dados quase ordenados\n");
    printf("• Selection Sort: Poucas trocas, útil quando trocas são custosas\n");
}

void montagemFinal() {
    if (totalComponentes == 0) {
        printf("❌ Nenhum componente para montagem!\n");
        return;
    }
    
    printf("\n🚀 MONTAGEM FINAL DA TORRE DE RESGATE\n");
    printf("====================================\n");
    
    // Ordena por prioridade (mais importante primeiro)
    selectionSortPorPrioridade();
    
    printf("\n📋 SEQUÊNCIA DE MONTAGEM (por prioridade):\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("→ Passo %d: %s (%s) - Prioridade %d\n", 
               i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    
    // Verifica componente chave
    int posicaoChave = -1;
    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(componentes[i].nome, COMPONENTE_CHAVE) == 0) {
            posicaoChave = i;
            break;
        }
    }
    
    printf("\n🔑 VERIFICAÇÃO DO COMPONENTE-CHAVE:\n");
    if (posicaoChave != -1) {
        printf("✅ '%s' encontrado! Torre pode ser ativada.\n", COMPONENTE_CHAVE);
        printf("🎉 MISSÃO CUMPRIDA! A torre está pronta para o resgate!\n");
    } else {
        printf("❌ '%s' não encontrado! Torre não pode ser ativada.\n", COMPONENTE_CHAVE);
        printf("💡 Dica: Cadastre o componente '%s' para completar a missão.\n", COMPONENTE_CHAVE);
    }
}

// ========== MENUS E INTERFACE ==========

void menuOrdenacao() {
    int opcao;
    do {
        printf("\n🔄 MENU DE ORDENAÇÃO\n");
        printf("1. Bubble Sort (por nome)\n");
        printf("2. Insertion Sort (por tipo)\n");
        printf("3. Selection Sort (por prioridade)\n");
        printf("4. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: bubbleSortPorNome(); mostrarComponentes(); break;
            case 2: insertionSortPorTipo(); mostrarComponentes(); break;
            case 3: selectionSortPorPrioridade(); mostrarComponentes(); break;
            case 4: printf("Voltando...\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
        
        if (opcao != 4) pausar();
    } while (opcao != 4);
}

void menuBusca() {
    printf("\n🔍 MENU DE BUSCA\n");
    
    if (totalComponentes == 0) {
        printf("❌ Cadastre componentes primeiro!\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("Digite o nome do componente a buscar: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    int posicao = buscaBinariaPorNome(nome);
    
    if (posicao != -1) {
        printf("✅ Encontrado na posição %d:\n", posicao + 1);
        printf("   Nome: %s | Tipo: %s | Prioridade: %d\n", 
               componentes[posicao].nome, componentes[posicao].tipo, componentes[posicao].prioridade);
    } else {
        printf("❌ Componente '%s' não encontrado.\n", nome);
    }
}

void menuPrincipal() {
    printf("\n🏝️  SISTEMA DE MONTAÇÃO DA TORRE DE RESGATE\n");
    printf("==========================================\n");
    printf("🌋 Zona de perigo se fechando! Monte sua torre rapidamente!\n\n");
    printf("1. Cadastrar componente\n");
    printf("2. Usar componentes de exemplo\n");
    printf("3. Ver componentes\n");
    printf("4. Ordenar componentes\n");
    printf("5. Buscar componente (binária)\n");
    printf("6. Análise de desempenho\n");
    printf("7. Montagem final da torre\n");
    printf("8. Sair\n");
    printf("Escolha: ");
}

int main() {
    printf("🚁 MISSÃO DE RESGATE - ÚLTIMA SAFE ZONE\n");
    printf("=======================================\n");
    printf("Monte a torre de resgate antes que a zona de perigo se feche!\n");
    printf("Componente-chave necessário: '%s'\n", COMPONENTE_CHAVE);
    
    int opcao;
    
    do {
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: cadastrarComponente(); break;
            case 2: cadastrarComponentesExemplo(); break;
            case 3: mostrarComponentes(); break;
            case 4: menuOrdenacao(); break;
            case 5: menuBusca(); break;
            case 6: analisarDesempenho(); break;
            case 7: montagemFinal(); break;
            case 8: printf("🚀 Missão encerrada. Boa sorte!\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
        
        if (opcao != 8) pausar();
        
    } while (opcao != 8);
    
    return 0;
}