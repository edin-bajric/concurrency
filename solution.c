#include "common_threads.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

int N;
int guest_count = 0;
pthread_mutex_t p = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_host = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_guest = PTHREAD_COND_INITIALIZER;

void openDoor(){
    printf("The host has opened the door!\n");
}

void *host(){
    Pthread_mutex_lock(&p);
    while(guest_count < N){
        Pthread_cond_wait(&cv_host, &p)
    }
    openDoor();
    Pthread_cond_signal(&cv_guest);
    Pthread_mutex_unlock(&p);

}

void enterHouse(){
    printf("I have entered the house!\n");
}

void *guest(){
    
    Pthread_mutex_lock(&p);
    printf("Guest Number [ %d ] arrived\n", guest_count + 1);
    guest_count++;
    
    if(guest_count == N){
        Pthread_cond_signal(&cv_host);
    }
    Pthread_cond_wait(&cv_guest, &p);
    Pthread_cond_signal(&cv_guest);
    
    Pthread_mutex_unlock(&p);
    enterHouse();

}
int main(){
    pthread_t host_thread;
    pthread_t guest_threads[100];

    scanf("%d", &N);

    Pthread_create(&host_thread, NULL, &host, NULL);


    for( int i = 0;i < N;i++){
        Pthread_create(&guest_threads[i], NULL, &guest, NULL);   
    }    
    
    for( int i = 0;i < N;i++){
        Pthread_join(guest_threads[i], NULL);
    }
    
    Pthread_join(host_thread, NULL);
    
    printf("Finished\n");

    return 0;
}
