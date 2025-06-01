#include <stdio.h>

#define TAM 10
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

// Exibe o tabuleiro com valores visuais diferenciados
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf(". ");      // Água
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");      // Navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");      // Área de efeito
            else
                printf("? ");      // Valor inesperado
        }
        printf("\n");
    }
    printf("\n");
}

// Posiciona um navio horizontal simples (3 células)
void posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        if (coluna + i < TAM)
            tabuleiro[linha][coluna + i] = NAVIO;
    }
}

// Posiciona uma matriz de habilidade no tabuleiro com valor 5 nas posições 1
void aplicarHabilidadeAoTabuleiro(int tabuleiro[TAM][TAM], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linha = origemLinha - offset + i;
            int coluna = origemColuna - offset + j;

            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] == AGUA)
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }
}

// Cria a matriz de habilidade em forma de cone
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (j >= (TAM_HABILIDADE - 1) / 2 - i &&
                            j <= (TAM_HABILIDADE - 1) / 2 + i) ? 1 : 0;
        }
    }
}

// Cria a matriz de habilidade em forma de cruz
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

// Cria a matriz de habilidade em forma de octaedro (losango)
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int distancia = abs(i - TAM_HABILIDADE / 2) + abs(j - TAM_HABILIDADE / 2);
            matriz[i][j] = (distancia <= TAM_HABILIDADE / 2) ? 1 : 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // 1. Inicializa tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // 2. Posiciona alguns navios
    posicionarNavioHorizontal(tabuleiro, 2, 2); // exemplo de navio
    posicionarNavioHorizontal(tabuleiro, 7, 4);

    // 3. Cria as áreas de efeito
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // 4. Aplica as habilidades no tabuleiro com ponto de origem definido
    aplicarHabilidadeAoTabuleiro(tabuleiro, cone, 1, 5);       // Cone no topo central
    aplicarHabilidadeAoTabuleiro(tabuleiro, cruz, 5, 5);       // Cruz no meio
    aplicarHabilidadeAoTabuleiro(tabuleiro, octaedro, 8, 2);   // Octaedro na base esquerda

    // 5. Exibe resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
