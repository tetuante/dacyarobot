/*codigo copia de internet una verguenza pero es lo que hay*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main()
{
    /*Spawn a child to run the program.*/
    pid_t pid=fork();
    if (pid==0) { /* child process */
    	/*robot no espera argumentos de entrada, por eso le paso a*/ 
    	/*execv un puntero NULL, aunque no se si hace falta,la verdad*/
        static char *argv[]={NULL};
        execv("/home/pi/Robotito/FirstDraft/robot",argv);
        exit(127); /* only if execv fails */
    }
    else { /* pid!=0; parent process */
        waitpid(pid,0,0); /* wait for child to exit */
    }
    return 0;
}