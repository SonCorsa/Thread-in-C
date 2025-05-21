#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 3 // Numero di processi figli da creare

int main() {
    int pid;

    printf("Processo padre (PID: %d) in esecuzione.\n", getpid());

    for (int i = 0; i < N; i++) {
        pid = fork(); // Creazione del processo figlio
        if (pid < 0) {
            printf("Errore nella fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Codice eseguito solo dal processo figlio
            printf("Processo figlio %d (PID: %d) creato dal padre (PID: %d).\n", i + 1, getpid(), getppid());

            // Simulazione di un'attività del processo figlio
            sleep(2); // Ad esempio, un'attività che richiede 2 secondi

            printf("Processo figlio %d (PID: %d) termina.\n", i + 1, getpid());
            exit(0); // Terminazione del processo figlio
        }
    }

    // Codice eseguito solo dal processo padre
    for (int i = 0; i < N; i++) {
        int status;
        int child_pid = wait(&status); // Attesa della terminazione di un figlio
        if (child_pid > 0) {
            printf("Processo padre: Figlio con PID %d terminato con stato %d.\n", child_pid, WEXITSTATUS(status));
        } else {
            perror("Errore nella wait");
        }
    }

    printf("Processo padre (PID: %d) termina.\n", getpid());
    return 0;
}
