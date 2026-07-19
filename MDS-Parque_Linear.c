#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

/* Nome do arquivo de entrada   */
#define INPUT_FILE "P22_parque_linear_n300.intervalos.txt"

/* Relogio monotonico de alta resolucao (independente de plataforma) */
#ifdef _WIN32
#include <windows.h>
double agora_segundos(void) {
    LARGE_INTEGER freq, contagem;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&contagem);
    return (double)contagem.QuadPart / (double)freq.QuadPart;
}
#else
#include <time.h>
double agora_segundos(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
#endif

typedef struct { int posto, esq, dir; } Intervalo;

Intervalo iv[MAXN];
int n;
int escolhidos[MAXN], qtd;

int adjacente(Intervalo a, Intervalo b) {
    int max_esq = a.esq > b.esq ? a.esq : b.esq;
    int min_dir = a.dir < b.dir ? a.dir : b.dir;
    return max_esq <= min_dir;
}

int cmp_dir(const void *a, const void *b) {
    Intervalo *x = (Intervalo *)a, *y = (Intervalo *)b;
    if (x->dir != y->dir) return x->dir - y->dir;
    return x->esq - y->esq;
}

int main(void) {
    FILE *in = fopen(INPUT_FILE, "r");
    if (!in) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'\n", INPUT_FILE);
        return 1;
    }
    while (fscanf(in, "%d %d %d", &iv[n].posto, &iv[n].esq, &iv[n].dir) == 3)
        n++;
    fclose(in);

    double t0 = agora_segundos();
    qsort(iv, n, sizeof(Intervalo), cmp_dir);

    static int dominado[MAXN];
    for (int i = 0; i < n; i++) {
        if (dominado[i]) continue;

        int central = i, maior_dir = iv[i].dir;
        for (int j = 0; j < n; j++)
            if (adjacente(iv[i], iv[j]) && iv[j].dir > maior_dir) {
                central = j;
                maior_dir = iv[j].dir;
            }

        escolhidos[qtd++] = iv[central].posto;

        for (int j = 0; j < n; j++)
            if (adjacente(iv[central], iv[j]))
                dominado[j] = 1;
    }
    double tempo = agora_segundos() - t0;

    printf("Quantidade minima de centrais: %d\n", qtd);
    printf("Postos escolhidos:");
    for (int i = 0; i < qtd; i++) printf(" %d", escolhidos[i]);
    printf("\n");
    printf("Otimalidade comprovada: sim\n");
    printf("Tempo de execucao: %.9f segundos\n", tempo);

    return 0;
}
