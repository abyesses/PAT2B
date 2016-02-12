//
//  main.c
//  Procesos_EJ4
//
//  Created by Abraham Esses on 2/10/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void creaNivel(int,int,int);
void creaNivel(int  n,int p,int curr){
    char * a = (char *)malloc(sizeof(char)*n);
    
    for(int i = 0; i< curr; i++){
        *(a+i) = '--';
    }
    for(int i = 0; i< curr; i++){
        printf("%c",*(a+i));
    }
    printf("%d \n",getpid());
    pid_t pid;
    for (int i=0;i<n;i++) {
        pid = fork();
        if(pid < 0){
            perror("Fork");
        }
        if (pid == 0) {
            if(curr < n){
                creaNivel(n,p,curr+1);
            }
            //printf("-PID: %d, PPID: %d\n",getpid(),getppid());
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
}
int main(int argc, const char * argv[]) {
    int num_procesos = 0;
    int niv_procesos = 0;
    int c,index;
    //pid_t * pid, *pid_p;
    //pid_t main_pid,main_pid2,main_pid3;
    while ((c = getopt (argc, argv, "n: p:")) != -1)
        switch (c)
    {
        case 'n':
            niv_procesos = atoi(optarg);
            break;
        case 'p':
            num_procesos = atoi(optarg);
            break;
        case '?':
            if ( optopt == 'n')
                fprintf (stderr, "Opción -%c requiere un argumento.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Opción desconocida '-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Opción desconocida '\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
    }
    
    for (index = optind; index < argc; index++)
        printf ("El argumento no es una opción válida %s\n", argv[index]);
    printf ("niveles = %d, procesos = %d, \n",
           niv_procesos,num_procesos);

    creaNivel(num_procesos,niv_procesos,0);
    return 0;
}
