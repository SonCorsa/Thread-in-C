#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define DIMENSIONE 10

int array[DIMENSIONE];
int conteggio_dispari = 0;
pthread_mutex_t lock;

void* genera_numeri(void* arg) {
    srand(time(NULL));
    conteggio_dispari = 0;

    for (int i = 0; i < DIMENSIONE; i++) {
        array[i] = rand() % 100;
        if ((array[i] % 2 != 0) {
            conteggio_dispari++;
        }
    }

    printf("Numeri generati: ");
    for (int i = 0; i < DIMENSIONE; i++) {
        printf("%d ", array[i]);
    }
    printf("\nConteggio numeri dispari: %d\n", conteggio_dispari);

    pthread_exit(NULL);
}

void ordina_bubble(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void* ordina_e_stampa(void* arg) {
    ordina_bubble(array, DIMENSIONE);

    printf("\nPrimi 5 numeri: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, genera_numeri, NULL);
    pthread_join(thread1, NULL);

    pthread_create(&thread2, NULL, ordina_e_stampa, NULL);
    pthread_join(thread2, NULL);

    return 0;
}