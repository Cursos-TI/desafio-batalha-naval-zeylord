#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define MAR 0
#define NAVIO 3

// Tipos de orientação possíveis
typedef enum { HORIZONTAL, VERTICAL, DIAGONAL_PRINCIPAL, DIAGONAL_SECUNDARIA } Orientacao;

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = MAR;
        }
    }
}

// Verifica se o navio cabe no tabuleiro e não sobrepõe outros navios
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, Orientacao orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        switch (orientacao) {
            case HORIZONTAL: c += i; break;
            case VERTICAL: l += i; break;
            case DIAGONAL_PRINCIPAL: l += i; c += i; break;
            case DIAGONAL_SECUNDARIA: l += i; c -= i; break;
        }

        // Verifica se está dentro dos limites
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO) return 0;

        // Verifica se já tem outro navio
        if (tabuleiro[l][c] != MAR) return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, Orientacao orientacao) {
    if (!podePosicionarNavio(tabuleiro, linha, coluna, orientacao)) {
        printf("Erro: não foi possível posicionar o navio em (%d, %d) com orientação %d\n", linha, coluna, orientacao);
        return;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        switch (orientacao) {
            case HORIZONTAL: c += i; break;
            case VERTICAL: l += i; break;
            case DIAGONAL_PRINCIPAL: l += i; c += i; break;
            case DIAGONAL_SECUNDARIA: l += i; c -= i; break;
        }

        tabuleiro[l][c] = NAVIO;
    }
}

// Exibe o tabuleiro no console
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

    // Inicializa com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona dois navios tradicionais (horizontal e vertical)
    posicionarNavio(tabuleiro, 0, 0, HORIZONTAL);         // Navio 1
    posicionarNavio(tabuleiro, 4, 2, VERTICAL);           // Navio 2

    // Posiciona dois navios diagonais
    posicionarNavio(tabuleiro, 6, 6, DIAGONAL_PRINCIPAL); // Navio 3
    posicionarNavio(tabuleiro, 2, 7, DIAGONAL_SECUNDARIA); // Navio 4

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
