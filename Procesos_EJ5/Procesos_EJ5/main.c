//
//  main.c
//  Procesos_EJ5
//
//  Created by Abraham Esses on 2/10/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
void creaProcesos(int,char*);
void creaProcesos(int num, char * p){
    pid_t pid_init;
    int estatus;
    for(int i = 0; i < num;i ++ ){
        pid_init = fork();
        
        if (pid_init < 0) {
            perror("Fork");
        }
        if  (pid_init == 0){
            char *comando[] = {p, 0};
            printf("Creando hijo con PID: %d\n",getpid());
            //sleep(3);
            execvp(comando[0], comando);
            exit(0);
        }
        else
        {
            wait(NULL);
            if (waitpid(pid_init, &estatus, 0) < 0) {
                if (WIFEXITED(estatus))
                    printf("El hijo con PID %d, terminó su ejecución\n",pid_init);
            }
            //printf("El proceso padre: %d ha terminado\n",getpid());
        }
    }
}

int main(int argc, const char * argv[]) {
    
    int num_procesos = 0;
    int c,index;
    char * programa = NULL;
    while ((c = getopt (argc, argv, "n: p:")) != -1)
        switch (c)
    {
        case 'n':
            num_procesos = atoi(optarg);
            break;
        case 'p':
            programa = optarg;
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
    
    printf ("numero = %d, programa = %s, \n",
            num_procesos,programa);
    creaProcesos(num_procesos,programa);
    
    return 0;
}
