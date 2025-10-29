#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// --- 1. Estrutura de Dados ---
#define NUM_TERRITORIOS 5
#define MAX_NOME 50

typedef struct {
    int id;
    char nome[MAX_NOME];
    int tropas;
    int dono; // 1 para Jogador 1, 2 para Jogador 2
} Territorio;

// --- 2. Alocação Dinâmica e Inicialização ---

/**
 * @brief Inicializa e aloca dinamicamente o vetor de territórios.
 * @return Ponteiro para o primeiro Territorio alocado.
 */
Territorio* inicializarTerritorios() {
    // Alocação dinâmica de memória usando calloc
    Territorio* mapa = (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));

    if (mapa == NULL) {
        perror("Erro na alocação de memória com calloc");
        exit(EXIT_FAILURE);
    }

    // Inicialização dos dados dos territórios
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        mapa[i].id = i + 1;
        mapa[i].tropas = 1 + (rand() % 3); // Tropas iniciais aleatórias (1 a 3)

        // Definindo o dono: Jogador 1 (primeiros 3) e Jogador 2 (últimos 2)
        if (i < 3) {
            mapa[i].dono = 1; // Jogador 1
            sprintf(mapa[i].nome, "T%d-J1", mapa[i].id);
        } else {
            mapa[i].dono = 2; // Jogador 2
            sprintf(mapa[i].nome, "T%d-J2", mapa[i].id);
        }
    }

    return mapa;
}

// --- 3. Funções de Apoio ---

/**
 * @brief Exibe o estado atual do mapa.
 * @param mapa Ponteiro para o vetor de territórios.
 */
void exibirMapa(const Territorio* mapa) {
    printf("\n--- Mapa Atual ---\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("| %d. %s | Tropas: %d | Dono: Jogador %d |\n",
               mapa[i].id, mapa[i].nome, mapa[i].tropas, mapa[i].dono);
    }
    printf("------------------\n");
}

/**
 * @brief Simula o lançamento de dados de ataque/defesa.
 * @return Valor do dado (1 a 6).
 */
int lancarDado() {
    return (rand() % 6) + 1; // Gera número entre 1 e 6
}

// --- 4. Função de Batalha ---

/**
 * @brief Simula um ataque entre dois territórios.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void simularAtaque(Territorio* atacante, Territorio* defensor) {
    // Garantir que o atacante tenha pelo menos 2 tropas para atacar (1 fica no território)
    if (atacante->tropas < 2) {
        printf("\n🚫 %s tem poucas tropas (%d)! É necessário pelo menos 2 para atacar.\n",
               atacante->nome, atacante->tropas);
        return;
    }

    // 1. Lançamento de Dados
    int dadoAtk = lancarDado();
    int dadoDef = lancarDado();

    printf("\n⚔️ BATALHA INICIADA: %s (%d tropas) ataca %s (%d tropas)\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);
    printf("🎲 Dados Sorteados:\n");
    printf("   Atacante: %d\n", dadoAtk);
    printf("   Defensor: %d\n", dadoDef);

    // 2. Lógica de Batalha
    if (dadoAtk > dadoDef) {
        // Atacante Vence
        printf("✅ Atacante VENCE! O defensor perde 1 tropa.\n");
        defensor->tropas--;
        atacante->tropas--; // O atacante também perde 1 tropa (custo de ataque)
    } else if (dadoDef > dadoAtk) {
        // Defensor Vence
        printf("🛡️ Defensor VENCE! O atacante perde 1 tropa.\n");
        atacante->tropas--;
    } else {
        // Empate (Asceta, como sugerido - favorece o defensor)
        printf("🤝 Empate! O Asceta intervém. O atacante perde 1 tropa.\n");
        atacante->tropas--;
    }

    printf("   Novo estado: %s tem %d tropas | %s tem %d tropas\n",
           atacante->nome, atacante->tropas, defensor->nome, defensor->tropas);

    // 3. Verificação de Conquista
    if (defensor->tropas <= 0) {
        printf("\n🎉 CONQUISTA! %s perdeu todas as tropas.\n", defensor->nome);
        printf("   O território %s é agora do Jogador %d!\n", defensor->nome, atacante->dono);

        // O território é conquistado
        defensor->tropas = 1; // Fica com 1 tropa do atacante
        defensor->dono = atacante->dono;

        // Atualiza o nome do território para o novo dono
        sprintf(defensor->nome, "T%d-J%d", defensor->id, defensor->dono);
        
        // Remove a tropa que foi transferida para o defensor do total do atacante
        atacante->tropas--;
    }
}

// --- 5. Função Principal (Main) ---
int main() {
    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    // Aloca e inicializa os territórios
    Territorio* mapa = inicializarTerritorios();

    printf("🌟 Bem-vindo ao Jogo de Batalha de Territórios (Nível Intermediário) 🌟\n");
    printf("Detalhes:\n");
    printf("  - Vetor de territórios alocado dinamicamente com calloc.\n");
    printf("  - Batalhas decididas por dados aleatórios (rand()).\n");
    printf("  - Jogador 1 (Dono 1) vs Jogador 2 (Dono 2).\n\n");

    int atacante_id, defensor_id;

    // Laço Interativo
    while (1) {
        exibirMapa(mapa);
        
        // Simples verificação de vitória para encerrar o jogo
        int donos_distintos = 0;
        int dono_ref = mapa[0].dono;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (mapa[i].dono != dono_ref) {
                donos_distintos = 1;
                break;
            }
        }
        
        if (donos_distintos == 0) {
            printf("\n👑 FIM DE JOGO! O Jogador %d conquistou todos os territórios!\n", dono_ref);
            break;
        }

        printf("\nSelecione 0 para sair.\n");
        printf("➡️ Digite o ID do território atacante (1 a %d): ", NUM_TERRITORIOS);
        if (scanf("%d", &atacante_id) != 1 || atacante_id == 0) {
            printf("Saindo do jogo...\n");
            break;
        }
        
        printf("⬅️ Digite o ID do território defensor (1 a %d): ", NUM_TERRITORIOS);
        if (scanf("%d", &defensor_id) != 1 || defensor_id == 0) {
             printf("Saindo do jogo...\n");
            break;
        }

        // Validação básica de entrada
        if (atacante_id < 1 || atacante_id > NUM_TERRITORIOS ||
            defensor_id < 1 || defensor_id > NUM_TERRITORIOS ||
            atacante_id == defensor_id) {
            printf("\n❌ IDs de território inválidos ou iguais. Tente novamente.\n");
            continue;
        }

        Territorio* at = &mapa[atacante_id - 1];
        Territorio* def = &mapa[defensor_id - 1];

        // Regra: Não pode atacar o próprio território
        if (at->dono == def->dono) {
            printf("\n❌ Você não pode atacar seu próprio território (%s). Tente novamente.\n", def->nome);
            continue;
        }

        // Executa a batalha
        simularAtaque(at, def);
    }

    // Libera a memória alocada dinamicamente
    free(mapa);
    mapa = NULL;
    printf("\nMemória liberada. Até a próxima!\n");

    return 0;
}