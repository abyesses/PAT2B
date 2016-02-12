//
//  main.c
//  Procesos_EJ1
//
//  Created by Abraham Esses on 2/3/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

double factorial(int num){
    double res=1;
    for (int i=1; i <= num; i++) {
        res *= i;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    int pid;
    //int estado;
    int a;
    double b;
    int salir = 1 ;
    
    while(salir != 0){
        
        pid = fork();
        if (pid < 0) {printf("Error en Fork\n");}
        if(pid == 0){
            printf("Inserta un número para calcular factorial\n");
            scanf("%d",&a);
            if (a != 0) {
                b = factorial(a);
                printf("Factorial de %d: %f\n",a,b);
            }
            else{
                break;
            }
            //exit(0);
        }
        else{
            
            wait(NULL);
        }
    }
    return 0;
}
