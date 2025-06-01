#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define MAR 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = MAR;
        }
    }
}

// Função para verificar se um navio pode ser posicionado sem ultrapassar limites ou sobrepor
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != MAR) return 0;
        }
    } else if (orientacao == 'V') {
        if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != MAR) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    if (podePosicionarNavio(tabuleiro, linha, coluna, orientacao)) {
        if (orientacao == 'H') {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha][coluna + i] = NAVIO;
            }
        } else if (orientacao == 'V') {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha + i][coluna] = NAVIO;
            }
        }
    } else {
        printf("Erro: Não foi possível posicionar o navio em (%d, %d) com orientação %c\n", linha, coluna, orientacao);
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com 0 (água)
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios fixadas (podem ser alteradas se quiser testar)
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 4;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 1;

    // Posiciona navios garantindo que não se sobreponham
    if (podePosicionarNavio(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal, 'H')) {
        posicionarNavio(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal, 'H');
    }

    if (podePosicionarNavio(tabuleiro, linhaNavioVertical, colunaNavioVertical, 'V')) {
        posicionarNavio(tabuleiro, linhaNavioVertical, colunaNavioVertical, 'V');
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
