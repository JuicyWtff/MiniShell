#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>

#define maxChar 100
#define maxArg 10


void userinput(char *input, char **args);

int main() {
    char input[maxChar];  
    char *args[maxArg];   
    int status;           
    
    while (true) {
        printf("[Hugo_prompt]$ ");         
        userinput(input, args);  
        
        if (strcmp(input, "exit") == 0) { //strcmp devuelve 0 si son iguales
            exit(0);
        }

        
        pid_t p = fork();

        if (p < 0) {
            perror("Error en fork");
        } else if (p == 0) {
            if (execvp(args[0], args) <= 0 ) {
                perror("Error al ejecutar el comando");
                exit(-1);
            } 
        } else {
            wait(&status);
        }
    }

    return 0;
}


void userinput(char *input, char **args) {
    char *token;
    int i = 0;

    fgets(input, maxChar, stdin); 
    //eliminar el salto de linea
    int size=strlen(input);
    if(size > 0 && input[size-1]=='\n'){
      input[size-1]='\0';
    }

    token = strtok(input, " ");
    while (token != NULL && i < maxArg - 1) {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL; 
    
}

