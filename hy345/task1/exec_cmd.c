/*SINANIS ANDREAS CSD5150*/

#include "func.h"

void exec_cmd(char *args[]) {
    int child_status, pipec = 0, i = 0,index=0;
    int pipe_idx[64];
    while(args[i] != NULL){
        if(strcmp(args[i],"|") == 0){
            pipe_idx[pipec] = i;
            args[i] = NULL;
            pipec++;
        }
        i++;
    }
    int pfd[pipec][2];
    for(i = 0; i <pipec;i++){
        if(pipe(pfd[i]) == -1){
            fprintf(stderr,"error in pipe");
            exit(1);
        }
    }
    for(i= 0; i<= pipec;i++){
        int pid = fork();
        if (pid == 0){
            int k = 0;
            if(i>0){
                dup2(pfd[i-1][0], STDIN_FILENO);
            }
            if(i<pipec){
                dup2(pfd[i][1], STDOUT_FILENO);
            }
            for (int j = 0;j<pipec; j++){
                close(pfd[j][0]);
                close(pfd[j][1]);
            }
            if(i!=0){
                k = pipe_idx[i-1]+1;
            }
            while(args[k] != NULL){
                if(strcmp(args[k], "<") == 0){
                    int fd = open(args[k + 1], O_RDONLY);
                    if (fd < 0) {
                        fprintf(stderr,"error in opening input file");
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    args[k] = NULL;
                    break;
                }else if (strcmp(args[k], ">>") == 0){
                    int fd = open(args[k+1],  O_CREAT|O_WRONLY|O_APPEND, 0777);
                    if (fd < 0){
                        fprintf(stderr,"error in opening output file");
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    args[k] = NULL;
                    break;
                }else if (strcmp(args[k], ">") == 0){
                    int fd = open(args[k + 1], O_CREAT|O_TRUNC|O_WRONLY, 0777);
                    if (fd < 0){
                        fprintf(stderr,"error in opening output file");
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    args[k] = NULL;
                    break;
                }
                k++;
            }
            if(i!=0){
                index = 1 + pipe_idx[i-1];
            }
            if(execvp(args[index], &args[index])==-1){
                fprintf(stderr, "error in execvp");
                exit(1);
            }
        }else if(pid < 0){
            fprintf(stderr,"error in fork");
            exit(1);
        }
    } for (i = 0; i < pipec; i++){
        close(pfd[i][0]);
        close(pfd[i][1]);
        //pipec+1
    } for (i = 0; i <pipec+1; i++){
        wait(&child_status);
    }
}