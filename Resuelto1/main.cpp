#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;
void* procesoHilo(void *data) {
    struct timespec tm = {1, 0};

    while (1) {
        cout << "proceso\n";
        nanosleep(&tm, NULL);
    }
    return NULL;
}

int main() {
    pthread_t proceso1, proceso2;

    // Create threads
    pthread_create(&proceso1, NULL, &procesoHilo, NULL);
    pthread_create(&proceso2, NULL, &procesoHilo, NULL);

    // Wait for threads to complete
    pthread_join(proceso1, NULL);
    pthread_join(proceso2, NULL);

    return 0;
}
