//
//  main.c
//  Procesos_EJ3
//
//  Created by Abraham Esses on 2/10/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void creaProcesos(int);
void creaProcesos(int num){
    pid_t pid_init;//pid_init2;
    int estatus,tiempoAl;
    for(int i = 0; i < num;i ++ ){
        pid_init = fork();
    
        if (pid_init < 0) {
            perror("Fork");
        }
        if  (pid_init == 0){
            printf("Creando hijo con PID: %d\n",getpid());
            tiempoAl = rand()%10;
            printf("Esperando %d segundos... \n",tiempoAl);
            sleep(tiempoAl);
            exit(0);
        }
        else
        {
            if (waitpid(pid_init, &estatus, 0) < 0) {
                if (WIFEXITED(estatus))
                    printf("El hijo con PID %d, terminó su ejecución\n",pid_init);
            }
            wait(NULL);
            printf("El proceso padre: %d ha terminado\n",getpid());
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //printf("Hello, World!\n");
    creaProcesos(15);
    return 0;
}
