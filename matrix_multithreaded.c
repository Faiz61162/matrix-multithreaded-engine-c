/*
 * Multithreaded Matrix Multiplication Engine in C
 * Author: Faiz Ansari
 * Description: Demonstrates high-performance matrix computation using POSIX threads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 1024

typedef struct
{
    int row;
    int col;
    int (*A)[MAX];
    int (*B)[MAX];
    int (*C)[MAX];
    int N;
} thread_data_t;

void *multiply_row(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    int r = data->row;
    for (int j = 0; j < data->N; ++j)
    {
        int sum = 0;
        for (int k = 0; k < data->N; ++k)
        {
            sum += data->A[r][k] * data->B[k][j];
        }
        data->C[r][j] = sum;
    }
    pthread_exit(NULL);
}

void fill_matrix(int matrix[MAX][MAX], int N)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            matrix[i][j] = rand() % 10;
}

void print_matrix(int matrix[MAX][MAX], int N, const char *label)
{
    printf("\n%s:\n", label);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%4d ", matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    int N;
    printf("Enter matrix dimension (max 1024): ");
    scanf("%d", &N);
    if (N > MAX || N < 1)
    {
        fprintf(stderr, "Invalid matrix size.\n");
        return EXIT_FAILURE;
    }

    int (*A)[MAX] = malloc(sizeof(int[MAX][MAX]));
    int (*B)[MAX] = malloc(sizeof(int[MAX][MAX]));
    int (*C)[MAX] = malloc(sizeof(int[MAX][MAX]));
    pthread_t *threads = malloc(sizeof(pthread_t) * N);
    thread_data_t *thread_data = malloc(sizeof(thread_data_t) * N);

    if (!A || !B || !C || !threads || !thread_data)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));
    fill_matrix(A, N);
    fill_matrix(B, N);

    clock_t start = clock();

    for (int i = 0; i < N; ++i)
    {
        thread_data[i] = (thread_data_t){i, 0, A, B, C, N};
        pthread_create(&threads[i], NULL, multiply_row, &thread_data[i]);
    }

    for (int i = 0; i < N; ++i)
        pthread_join(threads[i], NULL);

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    print_matrix(A, N, "Matrix A");
    print_matrix(B, N, "Matrix B");
    print_matrix(C, N, "Resultant Matrix C");

    printf("\nTime Taken: %.6f seconds\n", time_taken);

    free(A);
    free(B);
    free(C);
    free(threads);
    free(thread_data);
    return 0;
}
