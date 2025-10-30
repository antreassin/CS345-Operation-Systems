/*SINANIS ANDREAS CSD5150*/

#include "func.h"

int main(void) {
    char input[SIZE] = "";
    char *commands[SIZE], *user;
    char pathing[SIZE];
    int cmd_c = 0;
    getcwd(pathing,sizeof(pathing));
    user = getenv("USER");
    while(1){
        printf("csd5150-cs345sh@%s:%s > ",user,pathing);
        if(scanf(" %[^\n]", input) != 1) {
            exit(1);
        }
        char *cmd = strtok(input, ";");
        while(cmd!=NULL){
            commands[cmd_c++] = strdup(cmd);
            cmd = strtok(NULL, ";");
        }
        for(int i = 0; i < cmd_c; i++) {
            cmd = trim_whitespace(commands[i]);
            char *equal_sign = strchr(cmd, '=');
            if(equal_sign){
                *equal_sign = '\0';
                char *var_name = cmd;
                char *var_value = equal_sign+1;
                quotes(var_value);
                setenv(var_name, var_value, 1);
            }else{
                char *tok = strtok(cmd, " ");
                char *args[64];
                for(int j=0;j<64;j++){
                    args[j]=NULL;
                }
                int args_idx =0;
                while(tok!=NULL){
                    char buffer[SIZE];
                    buffer[0]= '\0';
                    char *ptr = tok;
                    while (*ptr) {
                        if (*ptr == '$') {
                            ptr++;
                            char var_name[SIZE];
                            var_name[0]= '\0';
                            int var_idx = 0;
                            while(*ptr && (isalnum(*ptr) || *ptr == '_')){
                                var_name[var_idx] = *ptr;
                                var_idx++;
                                ptr++;
                            }
                            var_name[var_idx] = '\0';
                            char *env_value = getenv(var_name);
                            if (env_value){
                                strcat(buffer, env_value);
                            }
                        }else{
                            strncat(buffer, ptr, 1);
                            ptr++;
                        }
                    }
                    args[args_idx] = strdup(buffer);
                    args_idx++;
                    tok = strtok(NULL, " ");
                }
                args[args_idx] = NULL;
                rearrange_cmd(args, &args_idx);
                //for (int j = 0; j < args_idx; j++) {
                //     printf("\t\t%s\n",args[j]);
                //}
                if (args[0]) {
                    exec_cmd(args);
                }
                for (int j = 0; j < args_idx; j++) {
                    free(args[j]);
                }
            }
        }
        for (int i = 0; i < cmd_c; i++) {
            free(commands[i]);
        }
        cmd_c = 0;
    }
    return 0;
}
