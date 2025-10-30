/*SINANIS ANDREAS CSD5150*/
#include "func.h"

char *trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
    return str;
}

void quotes(char *str) {
    int i=0,j=0;
    for (i =0;str[i]!= '\0';i++){
        if (str[i]!='"'){
            if(str[i] != '\'') str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int is_whitespace(char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) return 0;
        str++;
    }
    return 1;
}

void rearrange_cmd(char *args[], int *n){
    int write_index = 0;
    int length, j;
    for(int i=0; i<*n; i++){
        char *current_arg = args[i];
        length = strlen(current_arg);
        j = 0;
        while (j < length) {
            if (j < length - 1&&current_arg[j] == '>' && current_arg[j+1] == '>'){
                if(j>0){
                    char buff[SIZE];
                    strncpy(buff, current_arg, j);
                    buff[j] = '\0';
                    if (!is_whitespace(buff)){
                        args[write_index++] = strdup(buff);
                    }
                }
                args[write_index++] = strdup(">>");
                current_arg = current_arg+j+2;
                length = length- j + 2;
                j = 0;
                //ok
            }
            else if (current_arg[j] == '>' || current_arg[j] == '<' || current_arg[j] == '|') {
                if (j > 0) {
                    char part1[100];
                    strncpy(part1, current_arg, j);
                    part1[j] = '\0';
                    if (!is_whitespace(part1)) {
                        args[write_index++] = strdup(part1);
                    }
                }
                char operator[2] = {current_arg[j], '\0'};
                args[write_index++] = strdup(operator);
                current_arg = current_arg+j+1;
                length = length- j+1;
                j = 0;
            }
            else {
                j++;
            }
        }
        if (!is_whitespace(current_arg)) {
            args[write_index++] = strdup(current_arg);
        }
    }
    *n = write_index;
    // for(int j = 0;j<*n;j++){
    //     printf("\t\targ:%s\n",args[j]);
    // }
}