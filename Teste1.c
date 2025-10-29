#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para representar um Território
typedef struct {
    char nome[30];             // Nome do Território
    char cor_exercito[10];     // Cor do Exército dominante
    int num_tropas;            // Número de Tropas no território
} Territorio;

// Constante para o número de territórios
#define NUM_TERRITORIOS 5

/**
 * @brief Exibe o estado atual do mapa, listando todos os territórios cadastrados.
 *
 * @param mapa O vetor estático de Territorios.
 * @param tamanho O número de territórios no vetor.
 */
void exibir_mapa(Territorio mapa[], int tamanho) {
    printf("\n============================================\n");
    printf("         ESTADO ATUAL DO MAPA DE RISCO\n");
    printf("============================================\n");

    printf("| %-20s | %-15s | %-10s |\n", "Território", "Exército", "Tropas");
    printf("|----------------------|-----------------|------------|\n");

    for (int i = 0; i < tamanho; i++) {
        // Exibe os dados de forma organizada
        printf("| %-20s | %-15s | %-10d |\n",
               mapa[i].nome,
               mapa[i].cor_exercito,
               mapa[i].num_tropas);
    }
    printf("============================================\n");
}

/**
 * @brief Função principal do programa.
 */
int main() {
    // 1. Usar um vetor estático de 5 elementos para armazenar os territórios.
    Territorio mapa[NUM_TERRITORIOS];
    
    printf("--- Cadastro Inicial dos %d Territórios ---\n\n", NUM_TERRITORIOS);

    // Loop para cadastrar os dados de cada um dos 5 territórios
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Território #%d ---\n", i + 1);

        // --- Leitura do Nome ---
        printf("Digite o Nome do Território (máx 49 caracteres): ");
        // Uso de fgets para ler a linha inteira, incluindo espaços
        // e evitar problemas de buffer.
        // A função fgets lê até (tamanho - 1) ou um '\n'.
        if (fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin) != NULL) {
            // Remove o '\n' lido por fgets, se ele estiver presente
            mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        }
        
        // --- Leitura da Cor do Exército ---
        printf("Digite a Cor do Exército dominante (máx 19 caracteres): ");
        if (fgets(mapa[i].cor_exercito, sizeof(mapa[i].cor_exercito), stdin) != NULL) {
            // Remove o '\n' lido por fgets
            mapa[i].cor_exercito[strcspn(mapa[i].cor_exercito, "\n")] = '\0';
        }

        // --- Leitura do Número de Tropas ---
        printf("Digite o Número de Tropas: ");
        // Uso de scanf para ler um inteiro.
        // O espaço antes de "%d" é para consumir qualquer whitespace pendente,
        // o que é uma boa prática após usar fgets ou antes de outro scanf.
        if (scanf(" %d", &mapa[i].num_tropas) != 1) {
             printf("Erro na leitura do número de tropas. Encerrando.\n");
             return 1; // Sair com erro
        }
        
        // Limpa o buffer de entrada. Necessário após scanf para ler o
        // caractere de nova linha antes do próximo fgets.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { } 
        
        printf("\n");
    }

    // 4. Exibir o estado atual do mapa.
    exibir_mapa(mapa, NUM_TERRITORIOS);

    return 0;

}
