//
//  main.c
//  Procesos_EJ2
//
//  Created by Abraham Esses on 2/4/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM 16

int main(int argc, const char * argv[]) {
    int * a = (int *)malloc(NUM*sizeof(int));
    int res,res1,resT;
    for(int i=0; i<NUM; i++){
        *(a+i)=rand()%10;
        printf("Num[%d]: %d\n",i,*(a+i));
    }
    pid_t pid = fork();
    
    if(pid < 0){printf("Error en Fork\n");}
    else if (pid == 0) {
        
        int res = 0;
        for (int i=0; i< NUM/2; i++) {
            res += *(a+i);
        }
        printf("Res en hijo 1: %d\n",res);
        free(a);
        exit(res);
        
    }
    else
    {
        //Padre
       
        //WIFEXITED Regresa el valor si salio bien el proceso
        //WEXITSTATUS Regresa el valor de regreso
        pid_t pid1 = fork();

        
        if(pid1 == 0) {
            int res1 = 0;
            for (int i = NUM/2; i < NUM; i++) {
                res1 += *(a+i);
            }
            printf("Res en hijo 2: %d\n",res1);
            free(a);
            exit(res1);
        }
        if (waitpid(pid, &res, 0) != -1) {
            printf("Terminando hijo 1 con PID: %d y PPID: %d\n",getpid(),getppid());
            if (WIFEXITED(res)) {
                resT += WEXITSTATUS(res);
            }
        }
        if (waitpid(pid1, &res1, 0) != -1) {
            printf("Terminando hijo 2 con PID: %d y PPID: %d\n",getpid(),getppid());
            if (WIFEXITED(res1)) {
                resT += WEXITSTATUS(res1);
            }
        }
        printf("El resultado final es: %d\n",resT);
        free(a);
    }
    return 0;
}
