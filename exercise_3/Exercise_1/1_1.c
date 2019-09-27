#include <pthread.h>
#include <stdio.h>
#include <string.h>

static void *threadHello(void *arg){
    char *s = (char *) arg;
    printf("%s", s);
    return (void *) strlen(s);
}

int main(){
    pthread_t h1;
    void *res;
    int status;

    status = pthread_create(&h1, NULL, threadHello, "Hello world\n");
    if (status != 0){
        printf("Error creating thread");
    }

    pthread_exit(&res);

    return 0;
}
