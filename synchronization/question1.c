#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t intersection; // Semaphore for controlling access to the intersection

void* LEFT(void* arg) {
    char* road = (char*)arg;
    sem_wait(&intersection); // Request access to the intersection

    printf("Car from road %s is taking a LEFT turn.\n", road);
    sleep(1); // Simulate time taken to cross
    printf("Car from road %s has completed LEFT turn.\n", road);

    sem_post(&intersection); // Release the intersection
    return NULL;
}

void* RIGHT(void* arg) {
    char* road = (char*)arg;
    sem_wait(&intersection); // Request access to the intersection

    printf("Car from road %s is taking a RIGHT turn.\n", road);
    sleep(1); // Simulate time taken to cross
    printf("Car from road %s has completed RIGHT turn.\n", road);

    sem_post(&intersection); // Release the intersection
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;

    sem_init(&intersection, 0, 1); // Initialize semaphore with 1 permit

    // Simulating multiple cars from different roads
    pthread_create(&t1, NULL, LEFT, "A");
    pthread_create(&t2, NULL, RIGHT, "B");
    pthread_create(&t3, NULL, LEFT, "C");
    pthread_create(&t4, NULL, RIGHT, "A");

    // Wait for all cars to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    sem_destroy(&intersection); // Clean up semaphore
    return 0;
}
