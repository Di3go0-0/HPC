#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Xorshift32 
static inline uint32_t xorshift32(uint32_t *state) {
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

static inline void fill_random(uint32_t *M, int n, uint32_t *state) {
    const uint32_t MOD = 1000; // 0..999
    for (long long i = 0; i < (long long)n * n; i++) {
        M[i] = xorshift32(state) % MOD;
    }
}

static inline void matrix_multiply(const uint32_t *A, const uint32_t *B, uint32_t *C, int n) {
    // Sequential matrix multiplication with cache optimization (i-k-j order)
    for (int i = 0; i < n; i++) {
        long long base_i = (long long)i * n;
        for (int k = 0; k < n; k++) {
            uint32_t aik = A[base_i + k];
            long long base_k = (long long)k * n;
            for (int j = 0; j < n; j++) {
                C[base_i + j] += aik * B[base_k + j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        return 1;
    }

    // Memory allocation (1D for better cache locality)
    uint32_t *A = (uint32_t*) malloc((size_t)n * n * sizeof(uint32_t));
    uint32_t *B = (uint32_t*) malloc((size_t)n * n * sizeof(uint32_t));
    uint32_t *C = (uint32_t*) calloc((size_t)n * n, sizeof(uint32_t));

    if (!A || !B || !C) {
        free(A); free(B); free(C);
        return 1;
    }

    uint32_t state = (uint32_t)time(NULL);

    // Initialize matrices
    fill_random(A, n, &state);
    fill_random(B, n, &state);

    // Perform matrix multiplication
    matrix_multiply(A, B, C, n);

    // Cleanup
    free(A); free(B); free(C);
    return 0;
}

